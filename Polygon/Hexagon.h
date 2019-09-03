//Hexagon.h

#ifndef HEXAGON_H
#define HEXAGON_H

#include <vector>
#include <tuple>
#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;
using std::shared_ptr;

class Hexagon : public Polygon {
	
public:

	Hexagon(float xIn = 0, float yIn = 0, float sizeIn = 75);
	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);


};

#endif