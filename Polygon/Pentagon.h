//Pentagon.h

#ifndef PENTAGON_H
#define PENTAGON_H

#include <vector>
#include <tuple>
#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;
using std::shared_ptr;

class Pentagon : public Polygon {
	
public:


	Pentagon(float xIn = 0, float yIn = 0, float sizeIn = 75);

	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);

	bool chroma;


};

#endif