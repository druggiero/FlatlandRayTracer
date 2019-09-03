//Square.h

#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <tuple>

#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;

class Square : public Polygon {
	
public:
	Square(float xIn = 0, float yIn = 0, float sizeIn = 75);
	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);
	bool narr;
	bool book;
};

#endif