//
// Created by lehoej on 9/14/2018.
//

#ifndef CPPASSIGNMENTTWO_PRIMALGORITHM_H
#define CPPASSIGNMENTTWO_PRIMALGORITHM_H

#include "GrowingTree.h"

class PrimAlgorithm : public GrowingTree {
private:
	int index;
public:
	// constructor
	PrimAlgorithm(int* x, int* y, std::string* binFileName, std::string* solution);

	// select newest piece from the map
	inline void selectPiece()override;

	// pop one location off the top of the list
	void backTrack()override;

	// growing tree loop
	void buildLoop()override;

	// carve path
	void carvePath()override;

};


#endif // CPPASSIGNMENTTWO_PRIMALGORITHM_H
