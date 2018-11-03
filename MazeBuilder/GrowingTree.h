//
// Created by lehoej on 9/14/2018.
//

#ifndef CPPASSIGNMENTTWO_GROWINGTREE_H
#define CPPASSIGNMENTTWO_GROWINGTREE_H

#include <iostream>
#include <random>
#include <map>
#include <fstream>
#include <vector>
#include <time.h>
#include<chrono>
#include<random>
#include <algorithm>
#include <deque>


enum DIRECTION {
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4,
	EMPTY = 5
};
// the positions are stored on the board as a binary number
// the bits are allocated as M N S E W V
// N:North S:South W:West E:East V:Visted
// M is simular to V but is used when the solver runs

struct disposition {
	int binVal;
	disposition() :binVal(0b000000) {}
};


struct coords {
	int xPos, yPos;
};

class GrowingTree {
private:
	std::vector< std::vector<disposition> > * board = new std::vector< std::vector<disposition> >;
	int num, edgeNo, width, height;
	// solution creation
	std::vector<coords> locationList;
	std::fstream solutionFile;
	// binary creation
	std::deque<int>* numberList = new std::deque<int>;
	std::fstream* binFile = new std::fstream;
	std::string binNum, binFileName, solutionFileName;
protected:
	coords position;
	int randNum;
	std::vector<coords>* mapTree = new std::vector<coords>;
public:
	// generate random number
	void generateRandom(int max);

	// set location
	void setLocation();

	// createBoard
	void fillBoard();

	// set path functions set the direction of the path
	inline void storeNorth();
	inline void storeSouth();
	inline void storeEast();
	inline void storeWest();

	// move functions move in specified direction
	inline void moveNorth();
	inline void moveSouth();
	inline void moveEast();
	inline void moveWest();

	// check functions check the neighbors return result
	inline bool checkNorth();
	inline bool checkSouth();
	inline bool checkEast();
	inline bool checkWest();

	// check surounding cells
	DIRECTION neighborChk();

	// set visited
	inline void setVisited();

	// fill board generate & start point
	GrowingTree(int* x, int* y, std::string* binFileName, std::string* solution);

	// de-constructor deallocate the memory taken up by the object
	~GrowingTree();

	// growing tree loop
	virtual void buildLoop();

	// move in direction and carve path
	virtual void carvePath();

	// select newest piece from the map
	inline virtual void selectPiece();

	// adding location to the top of the map
	virtual void addLocation();

	// pop one location off the top of the stack
	virtual void backTrack();

	// make soluction to maze
	void solverMain();
	// set the fifth bit to zero as the solver visites the cell 
	void markVisited();
	// addlocation to the list of locations
	void addPiece();
	// remove location from the list of locations
	void removePiece();
	// mark north
	bool markNorth();
	// mark south
	bool markSouth();
	// mark east 
	bool markEast();
	// mark west
	bool markWest();

	// creat binary

	// give the file object a file
	void openBinFile();

	// iterate through the vector<vector<cell>> and find where the walls are
	void connectionChecker();

	// store binary number in bin file
	void addToBinFile();

	// add number of edges to third spot in wallList
	void addEdgeNum();

	// add values for edges
	void addEdges();

	// deallocate memory taken up by the binFile fstream object
	void deleteBinFile();

	// add numbers to wall container
	void addToWallList();

	// GrowingTree::south edge
	void southWall();

	// east edge
	void eastWall();

	// convert from integer to binary
	void intToBin();

	// where everything happens
	void binaryMain();

};

// set the path of the of maze
inline void GrowingTree::storeNorth() {
	(*board)[this->position.xPos][this->position.yPos].binVal |= 0b10000;
}
inline void GrowingTree::storeSouth() {
	(*board)[this->position.xPos][this->position.yPos].binVal |= 0b01000;
}
inline void GrowingTree::storeEast() {
	(*board)[this->position.xPos][this->position.yPos].binVal |= 0b00010;
}
inline void GrowingTree::storeWest() {
	(*board)[this->position.xPos][this->position.yPos].binVal |= 0b00100;
}

// move functions: move in specified direction
inline void GrowingTree::moveNorth() {
	storeNorth();
	this->position.yPos--;
	storeSouth();
}
inline void GrowingTree::moveSouth() {
	storeSouth();
	this->position.yPos++;
	storeNorth();
}
inline void GrowingTree::moveEast() {
	storeEast();
	this->position.xPos++;
	storeWest();
}
inline void GrowingTree::moveWest() {
	storeWest();
	this->position.xPos--;
	storeEast();
}

// check functions check the neighbors return result
inline bool GrowingTree::checkNorth() {
	if (this->position.yPos != 0) {
		return ((*board)[this->position.xPos][this->position.yPos - 1].binVal & 1) ? false : true;
	}
	else {
		return false;
	}
}
inline bool GrowingTree::checkSouth() {
	if (this->position.yPos != this->height - 1) {
		return ((*board)[this->position.xPos][this->position.yPos + 1].binVal & 1) ? false : true;
	}
	else {
		return false;
	}
}
inline bool GrowingTree::checkEast() {
	if (this->position.xPos != this->width - 1) {
		return ((*board)[this->position.xPos + 1][this->position.yPos].binVal & 1) ? false : true;
	}
	else {
		return false;
	}
}
inline bool GrowingTree::checkWest() {
	if (this->position.xPos != 0) {
		return ((*board)[this->position.xPos - 1][this->position.yPos].binVal & 1) ? false : true;
	}
	else {
		return false;
	}
}

// set visited
inline void GrowingTree::setVisited() {
	(*board)[this->position.xPos][this->position.yPos].binVal |= 0b00001;
}
#endif // CPPASSIGNMENTTWO_GROWINGTREE_H
