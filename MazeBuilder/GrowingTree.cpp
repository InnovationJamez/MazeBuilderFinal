//
// Created by lehoej on 9/14/2018.
//

#include "GrowingTree.h"

// fill board generate & start point
// the first location is randomly generated 
// and this location is set as visited
GrowingTree::GrowingTree(int* x, int* y, std::string* binFileName, std::string* solution)
	:width(*x), height(*y), binFileName(*binFileName), solutionFileName(*solution) {
	fillBoard();
	setLocation();
	setVisited();
}

// de-constructor deallocate the memory taken up by the object
GrowingTree::~GrowingTree() {
	delete mapTree;
	delete board;
}

// growing tree loop
void GrowingTree::buildLoop() {
	while (mapTree->size() > 0) {
		selectPiece();
		carvePath();
		setVisited();
	}
}

// generate random number
void GrowingTree::generateRandom(int max) {
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<> dis(0, (max - 1));
	this->randNum = dis(gen);
}

// set location
void GrowingTree::setLocation() {
	generateRandom(this->height);
	position.yPos = this->randNum;
	generateRandom(this->width);
	position.xPos = this->randNum;
}

// createBoard
// fills in the board and sets all of the initial bit values to zero
void GrowingTree::fillBoard() {
	for (int row = 0; row < width; row++) {
		std::vector<disposition>tempVec;
		for (int col = 0; col < height; col++) {
			disposition state;
			tempVec.push_back(state);
		}
		board->push_back(tempVec);
	}
}



// check surounding cells
// calls all of the check wall functions and then 
// adds their direction to a list if they return true
DIRECTION GrowingTree::neighborChk() {
	std::vector<DIRECTION> choice;
	if (checkNorth()) {
		choice.push_back(NORTH);
	}if (checkSouth()) {
		choice.push_back(SOUTH);
	}if (checkEast()) {
		choice.push_back(EAST);
	}if (checkWest()) {
		choice.push_back(WEST);
	}
	if (choice.empty()) {
		return EMPTY;
	}
	else {
		generateRandom(choice.size());
		return choice[this->randNum];
	}
}

// carve path
// uses the direction selected by the neighbor check and 
// moves in that direction
// while doing so the path is set in both cells 
// and the new cell is set as visited
void GrowingTree::carvePath() {
	DIRECTION choice = neighborChk();
	switch (choice) {
	case NORTH:
		moveNorth();
		addLocation();
		break;
	case SOUTH:
		moveSouth();
		addLocation();
		break;
	case EAST:
		moveEast();
		addLocation();
		break;
	case WEST:
		moveWest();
		addLocation();
		break;
	case EMPTY:
		backTrack();
		break;
	default:
		std::cout << "there has been an error" << std::endl;
		break;
	}
}

// select the newest piece from the map
void GrowingTree::selectPiece() {
	int val = mapTree->size() - 1;
	this->position = (*mapTree)[val];
}

// add location to the map
void GrowingTree::addLocation() {
	(*mapTree).push_back(this->position);
}

// pop one location off the top of the stack
void GrowingTree::backTrack() {
	(*mapTree).pop_back();
}

// make soluction to maze // SOLUTION // SOLUTION

/*
the mark functions check if there is a connection in that direction
then it checks to see if that position has allready been visited by the
solver. this makes it so the solver will not retread any ground and will
 allways be looking in areas it has not visited yet.
*/

// mark east
bool GrowingTree::markEast() {
	bool result = false;
	if ((*board)[this->position.xPos][this->position.yPos].binVal & 0b000010 && this->position.xPos != this->width - 1) {
		result = ((*board)[this->position.xPos + 1][this->position.yPos].binVal & 0b100000) ? false : true;
	}
	return result;
}

// mark south
bool GrowingTree::markSouth() {
	bool result = false;
	if ((*board)[this->position.xPos][this->position.yPos].binVal & 0b001000 && this->position.yPos != this->height - 1) {
		result = ((*board)[this->position.xPos][this->position.yPos + 1].binVal & 0b100000) ? false : true;
	}
	return result;
}

// mark west
bool GrowingTree::markWest() {
	bool result = false;
	if ((*board)[this->position.xPos][this->position.yPos].binVal & 0b000100 && this->position.xPos != 0) {
		result = ((*board)[this->position.xPos - 1][this->position.yPos].binVal & 0b100000) ? false : true;
	}
	return result;
}

// mark north
bool GrowingTree::markNorth() {
	bool result = false;
	if ((*board)[this->position.xPos][this->position.yPos].binVal & 0b010000 && this->position.yPos != 0) {
		result = ((*board)[this->position.xPos][this->position.yPos - 1].binVal & 0b100000) ? false : true;
	}
	return result;
}

/*
this is how the direction to move is facilited
this algorithm chack in the order right, down, west north
I want it to go from the top left to the bottom roght so these
directions are given priority as that is how I want it to move the most
this works like a recersive walk. it moves in a direction until it
gets to a dead end, and then it bactracks until it gets to a fork. and then
it traveres the new path.

*/

void GrowingTree::solverMain() {
	this->solutionFile.open("C:/Users/lehoej/Desktop/Visual Studio/MazeBuilder/SolutionFiles/" + solutionFileName, std::ofstream::out | std::ofstream::trunc);
	this->position = { 0,0 };
	markVisited();
	addPiece();
	int xGoal = width - 1;
	int yGoal = height - 1;
	std::string answer;

	while (this->position.xPos != xGoal || this->position.yPos != yGoal)
	{
		this->position = this->locationList[this->locationList.size() - 1];
		// check right/east
		if (markEast()) {
			this->position.xPos++;
			markVisited();
			addPiece();
		}
		// check south/down
		else if (markSouth())
		{
			this->position.yPos++;
			markVisited();
			addPiece();
		}
		// check left/west 
		else if (markWest()) {
			this->position.xPos--;
			markVisited();
			addPiece();
		}
		// check north/up
		else if (markNorth()) {
			this->position.yPos--;
			markVisited();
			addPiece();

		}
		else {
			removePiece();
			this->position = this->locationList[this->locationList.size() - 1];
		}
	} // while loop

	for (int i = 0; i < (int)this->locationList.size(); i++) {
		this->solutionFile << this->locationList[i].xPos;
		this->solutionFile << "\n";
		this->solutionFile << this->locationList[i].yPos;
		this->solutionFile << "\n";
	}

	this->solutionFile.close();
} // solver main

// M N S W E V
//
//      N
//   W     E
//      S

// set the fifth bit to zero as the solver visites the cell 
void GrowingTree::markVisited() {
	(*board)[this->position.xPos][this->position.yPos].binVal |= 0b100000;
}

// addlocation to the list of locations
void GrowingTree::addPiece() {
	this->locationList.push_back(position);
}

// remove location from the list of locations
void GrowingTree::removePiece() {
	this->locationList.pop_back();
}


// binary file stuff

// exactly like last time


void GrowingTree::openBinFile() {
	(*binFile).open("C:/Users/lehoej/Desktop/Visual Studio/MazeBuilder/MazeFiles/" + binFileName, std::ios::in | std::ios::out | std::ios::trunc);
}

// convert a base ten number to binary
void GrowingTree::intToBin() {
	binNum = "";
	while (num > 0)
	{
		binNum = binNum + (num % 2 == 1 ? '1' : '0');
		num = num / 2;
	}
	while (binNum.length() < 32)
	{
		binNum = binNum + '0';
	}
}

// iterate through the vector<vector<cell>> and find where the walls are
void GrowingTree::connectionChecker() {
	edgeNo = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < (height - 1); j++) {
			if ((*board)[i][j].binVal & 0b01000) {
				edgeNo++;
				position.yPos = j;
				position.xPos = i;
				southWall();
			}
		}
	}
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < (width - 1); i++) {
			if ((*board)[i][j].binVal & 0b0010) {
				edgeNo++;
				position.yPos = j;
				position.xPos = i;
				eastWall();
			}
		}
	}

}

// store binary number in bin file
void GrowingTree::addToBinFile() {
	for (int counter = 0; counter <= (int)binNum.size(); counter++) {
		binFile->put(binNum[counter]);
	}
}

// add number of edges to third spot in wallList
void GrowingTree::addEdgeNum() {
	num = width;
	intToBin();
	addToBinFile();
	num = height;
	intToBin();
	addToBinFile();
	num = edgeNo;
	intToBin();
	addToBinFile();
}

// add values for edges
void GrowingTree::addEdges() {
	for (int i : (*numberList)) {
		num = i;
		intToBin();
		addToBinFile();
	}
}

// deallocate memory taken up by the binFile fstream object
void GrowingTree::deleteBinFile() {
	binFile->close();
	delete binFile;
	delete numberList;
}

// add numbers to wall container
void GrowingTree::addToWallList() {
	(*numberList).push_back(num);
}

// GrowingTree::south edge
void GrowingTree::southWall() {
	num = position.xPos;
	addToWallList();
	num = position.yPos;
	addToWallList();
	num = position.xPos;
	addToWallList();
	num = position.yPos + 1;
	addToWallList();
}

// east edge
void GrowingTree::eastWall() {
	num = position.xPos;
	addToWallList();
	num = position.yPos;
	addToWallList();
	num = position.xPos + 1;
	addToWallList();
	num = position.yPos;
	addToWallList();
}

void GrowingTree::binaryMain() {
	openBinFile();
	connectionChecker();
	addEdgeNum();
	addEdges();
	deleteBinFile();
}
