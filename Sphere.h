//Sphere.h

#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <tuple>
using std::vector;
using std::tuple;
using std::pair;

class Sphere {
	
public:

	double xPos, yPos, zPos;
	double radius;
	Sphere(double xIn = 0, double yIn = 0, double zIn= 0, double sizeIn = 100);
	tuple<int,int,int> getColor(float distance, int fogHue, int fogStrength);
	void translate(float x, float y, float z);
	double checkIntersection(vector<double> filmLinePoint, vector<double> directionVector);

};

#endif