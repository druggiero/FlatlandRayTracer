//Viewer.h

#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <tuple>
using std::vector;
using std::tuple;
using std::pair;

class Viewer {
	
public:

	double xPos, yPos;

	Viewer(double xIn = 0, double yIn = -200);

	void translate(float x, float y);
	float rotate(float angle);

	void forward(float dist);

	vector< vector<double> > transformMatrix;

	float rotationValue;
	vector<double> heading;
		

protected:

	bool initMatrices();

};

#endif