//Circle.h

#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include <tuple>
using std::vector;
using std::tuple;
using std::pair;

class Circle {
	
public:

	double xPos, yPos;
	double radius;

	Circle(double xIn = 0, double yIn = 0, double sizeIn = 100);
	tuple<int,int,int> getColor(float distance, int fogHue, int fogStrength);

	void translate(float x, float y);
	float rotate(float angle);

	vector< vector<double> > rotationMatrix; //rotation matrix
	vector< vector<double> > translationMatrix; //translation matrix

	float rotationValue;
		
	double checkIntersection(vector<double> filmLinePoint, vector<double> directionVector);

protected:

	bool initMatrices();

};

#endif