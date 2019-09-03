//Priest.h

#ifndef PRIEST_H
#define PRIEST_H

#include <vector>
#include <tuple>
#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;

class Priest : public Polygon {
	
public:

	Priest(float xIn = 0, float yIn = 0, float sizeIn = 75);
	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);


};

#endif