#pragma once

#include "Prim.h"
#include "GrowingTree.h"


/*
	get refrence to maze array and get dimensions
	get the svg to write to 
	iterate through maze and draw to canvas
*/

void drawSVG(std::vector<int>* maze, int w, int h, std::fstream* svgFile, std::vector<Pos>* solution);

/*
	find solution to the maze start at 0,0 and at other corner
*/
void findSolution(std::vector<int>* maze, std::vector<Pos>* solution, int  w, int h);

/*
	get solution vector and draw the solution
*/
void drawSolution(std::fstream* svgFile, std::vector<Pos>* solution, float rowWidth, float colWidth, float horStep, float verStep);