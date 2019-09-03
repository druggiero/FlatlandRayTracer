//Triangle.h

#ifndef TRIANGLE_H
#define Triangle_H

#include <vector>
#include <tuple>

#include "Polygon.h"
using std::vector;
using std::tuple;
using std::pair;


class Triangle : public Polygon {
	
public:

	float topAngle; 

	Triangle(float xIn = 0, float yIn = 0, float sizeIn = 75, float topAngleIn = 60);

	tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength);

	

protected:

	vector <vector<double> > sideCountToSideCoeffs(int sideCount, float topAngle); 

};

#endif