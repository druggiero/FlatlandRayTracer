//Heptagon.h

#ifndef HEPTAGON_H
#define HEPTAGON_H

#include <vector>
#include <tuple>
#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;
using std::shared_ptr;

class Heptagon : public Polygon {
	
public:

	Heptagon(float xIn = 0, float yIn = 0, float sizeIn = 75);
	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);



};

#endif