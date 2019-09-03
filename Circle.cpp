//Circle.cpp
#include "Circle.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <math.h>

Circle::Circle(double xIn, double yIn, double sizeIn){

	xPos = 0;
	yPos = 0;


	//printf("Inside Circle1...xpos, ypos: %f, %f \n", xPos, yPos);

	radius = sizeIn;
	initMatrices();

	translate(xIn, yIn);

	//printf("InsideCircle...xIn, yIn:%f, %f \n", xIn, yIn );
	//printf("Inside Circle2...xpos, ypos: %f, %f \n \n", xPos, yPos);

}


tuple<int,int,int> Circle::getColor(float distance, int fogHue, int fogStrength){
	tuple<int,int,int> color = std::make_tuple(100,100,100);
	
	int red, green, blue;

	//A *lower* fogStrength is stronger fog

	red = 255;
	green = 150;
	blue = 0;

	red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
	green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
	blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

	
	if(distance>fogStrength){
		red = fogHue;
		green = fogHue;
		blue = fogHue;
	}

	
	std::get<0>(color) = red;
	std::get<1>(color) = green;
	std::get<2>(color) = blue;

	return  color;

}



bool Circle::initMatrices(){

	//counterclockwise rotation matrix initialization
	
	vector<double> row0;
	vector<double> row1;
	vector<double> row2;


	double row0Vals[] = {cos(0), sin(0), 0};
	double row1Vals[] = {-sin(0),  cos(0), 0};
	double row2Vals[] = {0, 0, 1};

	row0.assign(row0Vals, row0Vals+3);
	row1.assign(row1Vals, row1Vals+3);
	row2.assign(row2Vals, row2Vals+3);

	rotationMatrix.push_back(row0);
	rotationMatrix.push_back(row1);
	rotationMatrix.push_back(row2);



	//translation matrix initi
	vector<double> t_row0;
	vector<double> t_row1;
	vector<double> t_row2;

	double t_row0Vals[] = {1, 0, 0};
	double t_row1Vals[] = {0, 1, 0};
	double t_row2Vals[] = {0, 0, 1};

	t_row0.assign(t_row0Vals, t_row0Vals+3);
	t_row1.assign(t_row1Vals, t_row1Vals+3);
	t_row2.assign(t_row2Vals, t_row2Vals+3);

	translationMatrix.push_back(t_row0);
	translationMatrix.push_back(t_row1);
	translationMatrix.push_back(t_row2);


}


double Circle::checkIntersection(vector<double> filmLinePoint, vector<double> directionVector){
	vector< vector<double>> transMatrix = multMatbyMat(rotationMatrix,  translationMatrix);

	//no Matrix multiplication happening. Just adding the coordinates to get the position correct.
	//if you don't care about other transformations, you could probaby do the same with the sphere?


	filmLinePoint[0] = filmLinePoint[0] - xPos; //it's positive because the polygons are backwards
	filmLinePoint[1] = filmLinePoint[1] - yPos; //position becaue polygons are abckwards

	//using discriminant: b^2 - 4ac. Tells you # of roots.
	double a = pow(directionVector[0],2) + pow(directionVector[1],2);
	double b = (2*directionVector[0]*filmLinePoint[0] + 2*directionVector[1]*filmLinePoint[1]);
	double c = pow(filmLinePoint[0],2) + pow(filmLinePoint[1],2) - pow(radius,2);

	double discriminant = pow(b,2) - 4*a*c;

	//Discrim <0 means no real roots, = 0 means one root, > 0 means two roots.

	//printf("At filmLine 0, The discriminant is : %f \n", discriminant);
	

	//there should be an enter point and an exit point...
	

	double firstDistance = (-b + sqrt(discriminant)) / (2*a);
	double secondDistance = (-b - sqrt(discriminant)) / (2*a);

	if(filmLinePoint[0] == 0){
		//printf("firstDistance: %f, secondDistance: %f \n", firstDistance, secondDistance);

	}

	double intersectionDist;

	if(std::isnan(firstDistance) || std::isnan(secondDistance)){
		intersectionDist = NULL;
		return intersectionDist;

	}

	//what if the closest is like...behind film line.
	intersectionDist = std::min(firstDistance, secondDistance);
	
	return intersectionDist;	
	



}




void Circle::translate(float x, float y){

	//use homogenous coordinates to use affine transformation with matrix mult
	//rotation is a linear transformation, translation an affine transformation


	xPos = xPos + x;
	yPos = yPos + y;

	translationMatrix[0][2] = xPos;
	translationMatrix[1][2] = yPos;


}



float Circle::rotate(float angle){
	
	
	if(rotationValue+angle > 360){
		rotationValue = (rotationValue + angle) - 360;
	}

	else if (rotationValue + angle < 0){
		rotationValue = (rotationValue + angle) + 360;
	}

	else 
		rotationValue = rotationValue + angle;
	

	
	float theta = degreesToRadians(rotationValue);

	//printf("Testing degreesToRads: %f degrees becomes %f. That's %fpi radians. \n", rotationValue, theta, theta/PI );

	rotationMatrix[0][0] = cos(theta);
	rotationMatrix[0][1] = sin(theta);
	rotationMatrix[1][0] = -sin(theta);
	rotationMatrix[1][1] = cos(theta);
	return 3;
}



