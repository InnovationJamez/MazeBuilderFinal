#include <iostream>
#include <string>
#include <vector>


int main() {

	// the width and height of the maze
	int w, h;

	// get input from the user
	std::cout << "enter the width and height of the maze seporated by a space w h" << std::endl;
	std::cin >> w >> h;
	std::cout << "\n";
	std::cout << w << " " << h << std::endl;

	// create the maze array
	std::vector<int> maze(w * h);


	return 0;
}