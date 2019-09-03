//Decagon.h

#ifndef DECAGON_H
#define DECAGON_H

#include <vector>
#include <tuple>
#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;

class Decagon : public Polygon {
	
public:

	Decagon(float xIn = 0, float yIn = 0, float sizeIn = 75);
	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);


};

#endif