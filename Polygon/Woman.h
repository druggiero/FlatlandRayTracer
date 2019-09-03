//Woman.h

#ifndef WOMAN_H
#define WOMAN_H

#include <vector>
#include <tuple>
#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;

class Woman : public Polygon {
public:
	Woman(float xIn = 0, float yIn = 0, float sizeIn = 100);
	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);
};
#endif