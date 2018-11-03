//
// Created by lehoej on 9/16/2018.
//

#ifndef CPPASSIGNMENTTWO_RECERSIVEBACKTRACK_H
#define CPPASSIGNMENTTWO_RECERSIVEBACKTRACK_H

#include<stack>
#include "GrowingTree.h"

class RecursiveBacktrack : public GrowingTree {
private:
	std::stack<coords> mapStack;
public:
	// constructor
	RecursiveBacktrack(int* x, int* y, std::string* binFileName, std::string* solution);

	// growing tree loop
	void buildLoop()override;

	// select newest piece from the map
	inline void selectPiece()override;

	// adding location to the top of the map
	void addLocation()override;

	// pop one location off the top of the stack
	void backTrack()override;

	// carve path
	void carvePath()override;
};


#endif // CPPASSIGNMENTTWO_RECERSIVEBACKTRACK_H
