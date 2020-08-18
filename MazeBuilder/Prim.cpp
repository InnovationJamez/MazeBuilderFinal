#include "Prim.h"

Prim::Prim(std::vector<int>* maze_Pointer, int w, int h) : GrowingTree(maze_Pointer, w, h)
{}

void Prim::walkMaze()
{
	std::cout << "" << std::endl;
	// while pos list > 0 loop
	while (posList.size() > 0) {
		// select random element from pos list
		int index = rand() % posList.size();
		// and set position to it
		curr = posList[index];
		// check the surrounding cells get list of unvisited cells
		std::vector<int> openList = checkBounds();
		// if open space move to it and add location to list of open cells
		if (openList.size() > 0) {
			// select on of the directions
			int dir = openList[rand() % openList.size()];
			// move 
			carvePath(dir);
			// add new location to position list
			posList.push_back(curr);
		}
		// if all surrounding spaces taken 
		// reomve that space from the list
		else {
			// remove that position from the list
			posList.erase(posList.begin() + index);
		}

	}
}
