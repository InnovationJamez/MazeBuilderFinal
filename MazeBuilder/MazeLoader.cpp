//
// Created by lehoej on 9/21/2018.
//

#include "MazeLoader.h"

MazeLoader::MazeLoader(std::string* bin, std::string* svg, std::string* sol)
	:binFileName(*bin), SVGFileName(*svg), solutionFileName(*sol)
{

	binFile->open("C:/Users/lehoej/Desktop/Visual Studio/MazeBuilder/MazeFiles/" + binFileName, std::ios::in | std::ios::binary);
	if (binFile->is_open()) {
		readBinFile();
		closeBinFile();
	}

	svgFile->open("C:/Users/lehoej/Desktop/Visual Studio/MazeBuilder/SVGFiles/" + SVGFileName, std::ofstream::out | std::ofstream::trunc);
	if (svgFile->is_open()) {
		openSVG();
		readConnections();
		addSolution();
		closeSVG();
	}
}

MazeLoader::~MazeLoader() {
	delete connections;
}

void MazeLoader::readBinFile() {
	char ch;
	binFile->seekg(0, std::ios::end);
	int fileSize = (int)binFile->tellg();
	binFile->seekg(0, std::ios::beg);
	std::string tempString;
	while (binFile->tellg() < fileSize) {
		binFile->get(ch);
		tempString += ch;
		if (tempString.size() == 33)
		{
			binToInt(tempString);
			connections->push_back(result);
			tempString.clear();
		}
	}
}

void MazeLoader::closeBinFile() {
	binFile->close();
	delete binFile;
}

void MazeLoader::openSVG() {
	(*svgFile) << "<svg viewBox='0 0 1 1' ";
	(*svgFile) << "width='500' height='500' ";
	(*svgFile) << "xmlns='http://www.w3.org/2000/svg'>\n";
	(*svgFile) << "<rect width='1' height='1' ";
	(*svgFile) << "style='fill: black' />\n";
}

void MazeLoader::closeSVG() {
	(*svgFile) << "</svg>\n";
	svgFile->close();
	delete svgFile;
}

void MazeLoader::readConnections() {
	mazeWidth = (*connections)[0];
	mazeHeight = (*connections)[1];
	noOfWalls = (*connections)[2];
	bufferWidth = 1 / (float)mazeWidth;
	bufferHeight = 1 / (float)mazeHeight;
	for (int i = 3; i < (int)(*connections).size(); ++i) {
		if (i % 4 == 3)
		{
			a.xPos = (*connections)[i];

		}if (i % 4 == 0)

			a.yPos = (*connections)[i];
		{
		}if (i % 4 == 1)
		{
			b.xPos = (*connections)[i];

		}if (i % 4 == 2)
		{
			b.yPos = (*connections)[i];
			drawConnection();
		}
	}
}

void MazeLoader::drawConnection() {
	(*svgFile) << "<line stroke='white' stroke-width='";
	(*svgFile) << bufferWidth / 2;
	(*svgFile) << "' x1='";
	(*svgFile) << (1 + a.xPos)*bufferWidth - (bufferWidth / 2);
	(*svgFile) << "' y1='";
	(*svgFile) << (1 + a.yPos)*bufferHeight - (bufferHeight / 2);
	(*svgFile) << "' x2='";
	(*svgFile) << (1 + b.xPos)*bufferWidth - (bufferWidth / 2);
	(*svgFile) << "' y2='";
	(*svgFile) << (1 + b.yPos)*bufferHeight - (bufferHeight / 2);
	(*svgFile) << "'/>\n";
}

void MazeLoader::drawRedConnection() {
	(*svgFile) << "<line stroke='red' stroke-width='";
	(*svgFile) << bufferWidth / 2;
	(*svgFile) << "' x1='";
	(*svgFile) << (1 + a.xPos)*bufferWidth - (bufferWidth / 2);
	(*svgFile) << "' y1='";
	(*svgFile) << (1 + a.yPos)*bufferHeight - (bufferHeight / 2);
	(*svgFile) << "' x2='";
	(*svgFile) << (1 + b.xPos)*bufferWidth - (bufferWidth / 2);
	(*svgFile) << "' y2='";
	(*svgFile) << (1 + b.yPos)*bufferHeight - (bufferHeight / 2);
	(*svgFile) << "'/>\n";
}

// (num+1)*buffer-(buffer/2)
void MazeLoader::binToInt(std::string binVal) {
	result = 0;
	for (int i = 0; i < (int)binVal.size(); ++i)
	{
		if (binVal[i] == '1')
		{
			result += (int)pow(2, i);
		}
	}
}

void MazeLoader::addSolution() {
	std::ifstream solution("C:/Users/lehoej/Desktop/Visual Studio/MazeBuilder/SolutionFiles/" + solutionFileName, std::ofstream::in);
	std::string line;
	while (std::getline(solution, line)) {
		this->solutionList.push_back(std::stoi(line));
	}
	a.xPos = solutionList[0];
	a.yPos = solutionList[1];
	for (int i = 2; i < (int)solutionList.size(); i++) {
		if (i % 2 == 0) {
			b.xPos = solutionList[i];
		}if (i % 2 == 1) {
			b.yPos = solutionList[i];
			drawRedConnection();
			a.xPos = b.xPos;
			a.yPos = b.yPos;
		}
	} // for loop
}
