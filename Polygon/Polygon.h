//Polygon.h

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <tuple>
#include <memory>
#include "../Circle.h"
using std::vector;
using std::tuple;
using std::pair;
using std::shared_ptr;


//Base class for 2D shapes
class Polygon {
	
public:

	int sideCount;
	double size;
	double xPos, yPos;

	shared_ptr<Circle> boundingCircle;


	vector <vector<double> > sidesEquations;

	vector< vector<double> > sidesCoeffs;  //holds default coefficient matrix
	vector< vector<double> > homoSidesCoeffs; //hold coeffcieicent matrix with extra homogenous coors
	vector< vector<double> > rotatedSidesCoeffs; //holds rotated coeffcient matrix
	vector< vector<double> > translatedSidesCoeffs; //holds translated coefficient
	vector< vector<double> > transformedSidesCoeffs; //holds transformed coefficient matrix.


	vector<double> sidesConsts;	//holds vector of constants

	vector< vector<double> > sides; //puts coeffcients and constants together [A b], is changed by rotate function

	vector< vector<double> > rotationMatrix; //rotation matrix

	vector< vector<double> > invSShearTransformMatrix;//inverted simul-shear matrix
	vector< vector<double> > invRotationMatrix;//inverted simul-shear matrix
	vector< vector<double> > invTranslationMatrix; //inverted translation matrix
	vector< vector<double> > invLinearTransformMatrix; //full inverted transform matrix.

	vector< vector<double> > composeMatrix; //to use when composing

	float rotationValue;
	float h;
	float v;

	bool book;
	
		
	pair<int, double> checkIntersection(vector<double> filmLinePoint, vector<double> directionVector);
	float rotate(float angle);
	void translate(float x, float y);
 	void shear(float horz, float vert);
	virtual tuple<int,int,int> getColor(int side, float distance, int fogHue, int fogStrength) = 0;


protected:
	float checkSideIntersection(vector<double> side, vector<double> filmLinePoint, vector<double> directionVector);
	bool initMatrices();
	vector <vector<double> > sideCountToSideCoeffs(int sideCount); 
	Polygon();

};

#endif