#include "Main.h"

int main() {

	// the width and height of the maze
	int w = 10, h = 10;

	// other info from user
	std::string buildMethod = "potato", svgName = "newSvg";

	// get input from the user
	std::cout << "enter the info in the format" << std::endl;
	std::cout << "(build method) (svg file name) (width) (height)" << std::endl;
	//std::cin >> buildMethod >> svgName >> w >> h;
	std::cout << "\n";
	std::cout << w << " " << h << " " << buildMethod << " " << svgName << std::endl;

	// create the maze array
	std::vector<int> maze(w * h);

	// begin traversing the maze
	GrowingTree tree = GrowingTree(&maze, w, h);

	// create the svg
	drawSVG(&maze, w, h, svgName);

	return 0;
}
	

/*
	get refrence to maze array and get dimensions
	get the svg to write to
	iterate through maze and draw to canvas
*/

void drawSVG(std::vector<int>* maze, int w, int h, std::string svgFileName) {

	// open svg file
	std::fstream svgFile("Maze_SVG/" + svgFileName + ".svg", std::fstream::out | std::fstream::trunc);

	// the string of the start of the file
	std::string start = "<svg viewBox='0 0 1 1' width='500' height='500' xmlns='http://www.w3.org/2000/svg'><rect width='1' height='1' style='fill: black' />\n";
	// the string of the file
	std::string end = "</svg>\n";
	// get the width of each line
	float rowWidth = 1 / (float)(2 * w);
	// get the height of each line
	float colWidth = 1 / (float)(2 * h);
	// the horizontal len of a line
	float horStep = 1 / (float)w;
	// the vertical step of each line
	float verStep = 1 / (float)h;

	// check if file is open and then add text
	if (svgFile.is_open()){
		// add the start of the file
		svgFile << start;
		// loop through the maze vector
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				// check for a right connection
				if (((*maze)[j * w + i] & RIGHT) == RIGHT) {
					svgFile << "<line stroke='white' stroke-width='" << rowWidth;
					svgFile  <<  "' x1='" << (i + 0.5) * horStep << "' y1='" << (j + 0.5) * verStep;
					svgFile << "' x2='" << (i + 1.5) * horStep << "' y2='" << (j + 0.5) * verStep << "' />\n";
				}
				// check for a down connection
				if (((*maze)[j * w + i] & DOWN) == DOWN) {
					svgFile << "<line stroke='white' stroke-width='" << colWidth;
					svgFile << "' x1='" << (i + 0.5) * horStep << "' y1='" << (j + 0.5) * verStep;
					svgFile << "' x2='" << (i + 0.5) * horStep << "' y2='" << (j - 0.5) * verStep << "' />\n";
				}
			}
		}
		// end the svg file
		svgFile << end;
		// close the file
		svgFile.close();
	}
	else{
		std::cout << "file is not open" << std::endl;
	}
}