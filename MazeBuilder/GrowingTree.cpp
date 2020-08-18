#include "GrowingTree.h"

GrowingTree::GrowingTree(std::vector<int>* maze_Pointer, int w, int h) 
	: maze(maze_Pointer), width(w), height(h)
{
	// set the initial location of the search
	curr.xPos = rand() % width;
	curr.yPos = rand() % height;

	// add first position to list
	posList.push_back(curr);

	// set start position as visited
	(*maze)[curr.yPos * width + curr.xPos] |= VISITED;

	// begin walking through maze
	walkMaze();
}

/*
	check the spaces up, down, left, right if they are visited
	if not visited add it to move list
	return list
*/
std::vector<int> GrowingTree::checkBounds()
{
	// list to store the unvisited border cells
	std::vector<int> openSpace;
	// check up
	if (curr.yPos >= height - 1) {
		// pass
	}
	else if (((*maze)[(curr.yPos + 1) * width + curr.xPos] & VISITED) == 0) {
		// add up to open directions
		openSpace.push_back(UP);
	}
	// check down
	if (curr.yPos == 0) {
		// pass
	}
	else if (((*maze)[(curr.yPos - 1) * width + curr.xPos] & VISITED) == 0) {
		// add down to open directions
		openSpace.push_back(DOWN);
	}
	// check right
	if (curr.xPos >= width - 1) {
		// pass
	}
	else if (((*maze)[curr.yPos * width + (curr.xPos + 1)] & VISITED) == 0) {
		// add right to the open directions
		openSpace.push_back(RIGHT);
	}
	// check left
	if (curr.xPos == 0) {
		// pass
	}
	else if (((*maze)[curr.yPos * width + (curr.xPos - 1)] & VISITED) == 0) {
		// add left of open directions
		openSpace.push_back(LEFT);
	}
	// return the list of open directions
	return openSpace;
}

/*
	get the direction and move the position
	set the connections
	set the new location as visited
*/
void GrowingTree::carvePath(int dir)
{
	// based on the direction move and set the maze
	switch (dir) {
	case UP:
		// set an up connection
		(*maze)[curr.yPos * width + curr.xPos] |= UP;
		// move up
		curr.yPos += 1;
		// set down connection
		(*maze)[curr.yPos * width + curr.xPos] |= DOWN;
		// set new position as visited
		(*maze)[curr.yPos * width + curr.xPos] |= VISITED;
		break;
	case DOWN:
		// set down connection
		(*maze)[curr.yPos * width + curr.xPos] |= DOWN;
		// move down
		curr.yPos -= 1;
		// set up connection
		(*maze)[curr.yPos * width + curr.xPos] |= UP;
		// set new position as visited
		(*maze)[curr.yPos * width + curr.xPos] |= VISITED;
		break;
	case LEFT:
		// set left connection
		(*maze)[curr.yPos * width + curr.xPos] |= LEFT;
		// move down
		curr.xPos -= 1;
		// set right connection
		(*maze)[curr.yPos * width + curr.xPos] |= RIGHT;
		// set new position as visited
		(*maze)[curr.yPos * width + curr.xPos] |= VISITED;
		break;
	case RIGHT:
		// set right connection
		(*maze)[curr.yPos * width + curr.xPos] |= RIGHT;
		// move down
		curr.xPos += 1;
		// set left connection
		(*maze)[curr.yPos * width + curr.xPos] |= LEFT;
		// set new position as visited
		(*maze)[curr.yPos * width + curr.xPos] |= VISITED;
		break;
	}
}

/*
	walk through funciton
	traverse the maze until all cells checked
*/

void GrowingTree::walkMaze()
{
	// while position list length is greater than zero
	while (posList.size() > 0) {
		// check boundary cells
		std::vector<int> open = checkBounds();
		// check length
		if (open.size() > 0) {
			// select on of the directions
			int dir = open[rand() % open.size()];
			// move 
			carvePath(dir);
			// add new location to position list
			posList.push_back(curr);
		}
		else {
			// pop the last element of pos list
			posList.pop_back();
			// set current postion to last pos list
			curr = (posList.size() > 0) ? posList.back() : Pos(0, 0);
		}
	}
}
