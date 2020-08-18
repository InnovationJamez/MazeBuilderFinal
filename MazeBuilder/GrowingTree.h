#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

// for storing maze data
constexpr int UP = 1;
constexpr int DOWN = 2;
constexpr int RIGHT = 4;
constexpr int LEFT = 8;
constexpr int VISITED = 16;
constexpr int EXP = 32;

// custom data store x and y values
struct Pos {
	// x pos
	int xPos;
	// y pos
	int yPos;
	// condtructor
	Pos(int x, int y) {
		// set the values
		xPos = x;
		yPos = y;
	}
};

/*
	get refrence to maze
	traverse the maze and fill in the values
*/


class GrowingTree
{
protected:
	// the vector to store the maze
	std::vector<int>* maze;
	// the width of the maze
	int width;
	// the height of the maze
	int height;
	// x position of the search
	Pos curr = Pos(0, 0);
	// list of positions 
	std::vector<Pos> posList;
public:
	// constructor
	GrowingTree(std::vector<int>* maze_Pointer, int w, int h);
	// check if all four firections & return open spaces
	std::vector<int> checkBounds();
	// carve a path in the maze
	void carvePath(int dir);
	// walk through the maze
	virtual void walkMaze();
};

