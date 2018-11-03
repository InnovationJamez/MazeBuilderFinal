//
// Created by lehoej on 9/21/2018.
//

#ifndef CPPASSIGNMENTTWO_MAZELOADER_H
#define CPPASSIGNMENTTWO_MAZELOADER_H
#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<string>

struct position {
	int xPos, yPos;
};

class MazeLoader {
private:
	int mazeWidth, mazeHeight, noOfWalls, result, fileSize;
	float bufferWidth, bufferHeight;
	position a, b;
	std::string binFileName, SVGFileName, solutionFileName;
	std::vector<int>* connections = new std::vector<int>;
	std::vector<int> solutionList;
	std::fstream* binFile = new std::fstream;
	std::fstream* svgFile = new std::fstream;
public:
	MazeLoader(std::string* bin, std::string* svg, std::string* sol);
	~MazeLoader();
	void readBinFile();
	void closeBinFile();
	void openSVG();
	void readConnections();
	void drawConnection();
	void drawRedConnection();
	void closeSVG();
	void binToInt(std::string binVal);
	void addSolution();
};

#endif //CPPASSIGNMENTTWO_MAZELOADER_H
