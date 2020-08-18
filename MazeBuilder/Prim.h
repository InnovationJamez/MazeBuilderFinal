#pragma once
#include "GrowingTree.h"

class Prim : public GrowingTree
{
private:

public:
	// constructor
	Prim(std::vector<int>* maze_Pointer, int w, int h);
	// override the walk function
	 void walkMaze()override;
};

