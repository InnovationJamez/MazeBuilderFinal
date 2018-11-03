//
// Created by lehoej on 9/14/2018.
//

#include "PrimAlgorithm.h"

// constructor
PrimAlgorithm::PrimAlgorithm(int* x, int* y, std::string* binFileName, std::string* solution) :
	GrowingTree(x, y, binFileName, solution)
{
	addLocation();
	buildLoop();
}

// select a random piece from the map
void PrimAlgorithm::selectPiece() {
	generateRandom(mapTree->size());
	this->index = randNum;
	this->position = (*mapTree)[index];
}


// delete the current location from map
void PrimAlgorithm::backTrack() {
	(*mapTree).erase((*mapTree).begin() + index);
}

// growing tree loop
void PrimAlgorithm::buildLoop() {
	while (!mapTree->empty()) {
		selectPiece();
		carvePath();
	}
}

// carve path
void PrimAlgorithm::carvePath() {
	DIRECTION choice = neighborChk();
	switch (choice) {
	case NORTH:
		moveNorth();
		addLocation();
		setVisited();
		break;
	case SOUTH:
		moveSouth();
		addLocation();
		setVisited();
		break;
	case EAST:
		moveEast();
		addLocation();
		setVisited();
		break;
	case WEST:
		moveWest();
		addLocation();
		setVisited();
		break;
	case EMPTY:
		backTrack();
		break;
	default:
		std::cout << "there has been an error" << std::endl;
		break;
	}
}
