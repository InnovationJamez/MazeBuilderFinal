#include "Main.h"

int main() {

	// the width and height of the maze
	int w = 10, h = 10;

	// other info from user
	std::string buildMethod = "p", svgName = "newSvg";

	// get input from the user
	std::cout << "enter the info in the format" << std::endl;
	std::cout << "g : growing tree\np: prim" << std::endl;
	std::cout << "(build method) (svg file name) (width) (height)" << std::endl;
	std::cin >> buildMethod >> svgName >> w >> h;
	std::cout << "\n";
	std::cout << w << " " << h << " " << buildMethod << " " << svgName << std::endl;

	// create the maze array
	std::vector<int> maze(w * h);

	// begin traversing the maze
	if (buildMethod == "g") {
		// create growing tree class
		GrowingTree tree = GrowingTree(&maze, w, h);
		// begin walking through maze
		tree.walkMaze();
	}
	else if (buildMethod == "p") {
		// create prim object
		Prim prim = Prim(&maze, w, h);
		// begin walling through maze
		prim.walkMaze();
	}
	else {
		std::cout << "invalid build method. closing program" << std::endl;
		return 0;
	}

	std::vector<Pos> solution;

	// create the svg file
	std::fstream svgFile("Maze_SVG/" + svgName + ".svg", std::fstream::out | std::fstream::trunc);

	// find the solution to the maze
	findSolution(&maze, &solution, w, h);
	
	// create the svg
	drawSVG(&maze, w, h, &svgFile, &solution);

	return 0;
}
	

/*
	get refrence to maze array and get dimensions
	get the svg to write to
	iterate through maze and draw to canvas
*/

void drawSVG(std::vector<int>* maze, int w, int h, std::fstream* svgFile, std::vector<Pos>* solution) {
	// the string of the start of the file
	std::string start = "<svg viewBox='0 0 1 1' width='500' height='500' xmlns='http://www.w3.org/2000/svg'><rect width='1' height='1' style='fill: black' />\n";
	// the string of the file
	std::string end = "</svg>\n";
	// get the width of each line
	float rowWidth = 1 / (float)(2 * w);
	// get the height of each line
	float colWidth = 1 / (float)(2 * h);
	// the horizontal len of a line
	float horStep = 1 / (float)w;
	// the vertical step of each line
	float verStep = 1 / (float)h;

	// check if file is open and then add text
	if ((*svgFile).is_open()){
		// add the start of the file
		(*svgFile) << start;
		// loop through the maze vector
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				// check for a right connection
				if (((*maze)[j * w + i] & RIGHT) == RIGHT) {
					(*svgFile) << "<line stroke='white' stroke-width='" << rowWidth;
					(*svgFile) <<  "' x1='" << (i + 0.5) * horStep << "' y1='" << (j + 0.5) * verStep;
					(*svgFile) << "' x2='" << (i + 1.5) * horStep << "' y2='" << (j + 0.5) * verStep << "' />\n";
				}
				// check for a down connection
				if (((*maze)[j * w + i] & DOWN) == DOWN) {
					(*svgFile) << "<line stroke='white' stroke-width='" << colWidth;
					(*svgFile) << "' x1='" << (i + 0.5) * horStep << "' y1='" << (j + 0.5) * verStep;
					(*svgFile) << "' x2='" << (i + 0.5) * horStep << "' y2='" << (j - 0.5) * verStep << "' />\n";
				}
			}
		}
		// draw the solution
		drawSolution(svgFile, solution, rowWidth, colWidth, horStep, verStep);
		// end the svg file
		(*svgFile) << end;
		// close the file
		(*svgFile).close();
	}
	else{
		std::cout << "file is not open" << std::endl;
	}
}


/*
	find solution to the maze start at 0,0 and at other corner
*/
void findSolution(std::vector<int>* maze, std::vector<Pos>* solution, int  w, int h) {
	// start at position 0, 0
	Pos curr = Pos(0, 0);
	// set start positon as explored
	(*maze)[curr.yPos * w + curr.xPos] |= EXP;
	// add the initial location to list of positions
	(*solution).push_back(curr);
	// loop until maze is traversed
	while (curr.xPos != w - 1 || curr.yPos != h - 1) {
		// list of the open positions
		std::vector<int> open;
		// check right
		if (curr.xPos >= w - 1) {
			// cant move right
		}
		else if (((*maze)[curr.yPos * w + (curr.xPos + 1)] & EXP) > 0) {
			// right position already taken
		}
		else if (((*maze)[curr.yPos * w + curr.xPos] & RIGHT) > 0 ) {
			open.push_back(RIGHT);
		}
		// check left
		if (curr.xPos == 0) {
			// cant move left
		}
		else if (((*maze)[curr.yPos * w + (curr.xPos - 1)] & EXP) > 0) {
			// left space taken
		}
		else if (((*maze)[curr.yPos * w + curr.xPos] & LEFT) > 0) {
			open.push_back(LEFT);
		}
		// up
		if (curr.yPos >= h - 1) {
			// cant move up
		}
		else if (((*maze)[(curr.yPos + 1) * w + curr.xPos] & EXP) > 0) {
			// up block already explored
		}
		else if (((*maze)[curr.yPos * w + curr.xPos] & UP) > 0) {
			open.push_back(UP);
		}
		// down
		if (curr.yPos == 0) {
			// cant move down
		}
		else if (((*maze)[(curr.yPos - 1) * w + curr.xPos] & EXP) > 0) {
			// up position already taken
		}
		else if (((*maze)[curr.yPos * w + curr.xPos] & DOWN) > 0) {
			open.push_back(DOWN);
		}
		// check the number of free boundary cells
		if (open.size() > 0) {
			// select one random direction
			int dir = open[rand() % open.size()];
			// move in selected direciton
			switch (dir) {
			case RIGHT:
				// go right
				curr.xPos++;
				// set new positon as explored
				(*maze)[curr.yPos * w + curr.xPos] |= EXP;
				break;
			case LEFT:
				curr.xPos--;
				// set new positon as explored
				(*maze)[curr.yPos * w + curr.xPos] |= EXP;
				break;
			case UP:
				curr.yPos++;
				// set new positon as explored
				(*maze)[curr.yPos * w + curr.xPos] |= EXP;
				break;
			case DOWN:
				curr.yPos--;
				// set new positon as explored
				(*maze)[curr.yPos * w + curr.xPos] |= EXP;
				break;
			}
			// add new position to position list
			(*solution).push_back(curr);
		}
		else {
			// pop the last element of pos list
			(*solution).pop_back();
			// set current postion to last pos list
			curr = (*solution).back();
		}
	}
}

void drawSolution(std::fstream* svgFile, std::vector<Pos>* solution, float rowWidth, float colWidth, float horStep, float verStep)
{
	// get len of solution vector
	int len = (*solution).size() - 1;
	// iterate through the solution vector
	for (int i = 0; i < len; i++) {
		float stroke = ((*solution)[i + 1].yPos != (*solution)[i].yPos) ? rowWidth : colWidth;
		// draw line
		(*svgFile) << "<line stroke='red' stroke-width='" << stroke;
		(*svgFile) << "' x1='" << ((*solution)[i].xPos + 0.5) * horStep << 
			"' y1='" << ((*solution)[i].yPos + 0.5) * verStep;
		(*svgFile) << "' x2='" << ((*solution)[i + 1].xPos + 0.5) * horStep << 
			"' y2='" << ((*solution)[i + 1].yPos + 0.5) * verStep << "' />\n";
	}
	
}
