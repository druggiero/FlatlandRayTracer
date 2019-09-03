//Octagon.h

#ifndef OCTAGON_H
#define OCTAGON_H

#include <vector>
#include <tuple>
#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;

class Octagon : public Polygon {
	
public:

	Octagon(float xIn = 0, float yIn = 0, float sizeIn = 75);
	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);


};

#endif