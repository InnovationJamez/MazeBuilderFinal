#pragma once

#include "GrowingTree.h"

/*
	get refrence to maze array and get dimensions
	get the svg to write to 
	iterate through maze and draw to canvas
*/

void drawSVG(std::vector<int>* maze, int w, int h, std::string svgFileName);