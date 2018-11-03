#include "GrowingTree.h"
#include "MazeLoader.h"
#include "PrimAlgorithm.h"
#include "RecersiveBacktrack.h"

void BuildGrowingTree(int* width, int* height, std::string* binFileName, std::string* solutionName);
void BuildPrim(int* width, int* height, std::string* binFileName, std::string* solutionName);
void BuildRecersive(int* width, int* height, std::string* binFileName, std::string* solutionName);

int main() {
	int height = 10, width = 10;
	std::string buildMethod;
	std::string binFileName = "maze.maze";
	std::string SVGFileName = "svg.svg";
	std::string solutionName = "solution.txt";

	std::cout << "Build Options\ng: growing tree\np: prim algorithm\nr:recersive" << std::endl;
	std::cout << "buildMethod width height svgName.svg\nENTER HERE: ";
	std::cin >> buildMethod >> width >> height >> SVGFileName;

	if (buildMethod == "g") {
		BuildGrowingTree(&width, &height, &binFileName, &solutionName);
		MazeLoader(&binFileName, &SVGFileName, &solutionName);
	}if (buildMethod == "p") {
		BuildPrim(&width, &height, &binFileName, &solutionName);
		MazeLoader(&binFileName, &SVGFileName, &solutionName);
	}if (buildMethod == "r") {
		BuildRecersive(&width, &height, &binFileName, &solutionName);
		MazeLoader(&binFileName, &SVGFileName, &solutionName);
	}
}

void BuildGrowingTree(int* width, int* height, std::string* binFileName, std::string* solutionName) {
	GrowingTree treeObj(width, height, binFileName, solutionName);
	treeObj.addLocation();
	treeObj.buildLoop();
	treeObj.binaryMain();
	treeObj.solverMain();
}

void BuildPrim(int* width, int* height, std::string* binFileName, std::string* solutionName) {
	PrimAlgorithm primObj(width, height, binFileName, solutionName);
	primObj.binaryMain();
	primObj.solverMain();
}

void BuildRecersive(int* width, int* height, std::string* binFileName, std::string* solutionName) {
	RecursiveBacktrack recObj(width, height, binFileName, solutionName);
	recObj.binaryMain();
	recObj.solverMain();
}