//Viewer.cpp
#include "Viewer.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <math.h>

Viewer::Viewer(double xIn, double yIn){

	xPos = 0;
	yPos = 0;
	initMatrices();
	translate(xIn, yIn);
	rotationValue = 0;
	//printf("rotationBVa %f \n", rotationValue);

}


bool Viewer::initMatrices(){

	//transform rotation matrix initialization
	
	//for viewer, it will be TR.

	vector<double> row0;
	vector<double> row1;
	vector<double> row2;

	//may need to switch signage.
	double row0Vals[] = {cos(0), -sin(0), 0}; //cos, -sin, tx
	double row1Vals[] = {sin(0),  cos(0), 0}; //sin, cos, ty  
	double row2Vals[] = {0, 0, 1};

	row0.assign(row0Vals, row0Vals+3);
	row1.assign(row1Vals, row1Vals+3);
	row2.assign(row2Vals, row2Vals+3);

	transformMatrix.push_back(row0);
	transformMatrix.push_back(row1);
	transformMatrix.push_back(row2);


}


void Viewer::translate(float x, float y){

	//use homogenous coordinates to use affine transformation with matrix mult
	//rotation is a linear transformation, translation an affine transformation
	//(linear transformations are also affines)

	xPos = xPos + x;
	yPos = yPos + y;

	transformMatrix[0][2] = xPos;
	transformMatrix[1][2] = yPos;

	//printf("new xPos: %f \n", xPos);
	//printf("new yPos: %f \n", yPos);

}

void Viewer::forward(float distance){

	//adding shift of 90 because it starts, facing north, at 0.
	xPos = xPos + (distance)*cos(degreesToRadians(rotationValue+90));
    yPos = yPos + (distance)*sin(degreesToRadians(rotationValue+90));

    transformMatrix[0][2] = xPos;
	transformMatrix[1][2] = yPos;

	printf("Viewer's new xPos: %f \n", xPos);
	printf("Viewer's new yPos: %f \n", yPos);

}


float Viewer::rotate(float angle){
	
	
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

	transformMatrix[0][0] = cos(theta);
	transformMatrix[0][1] = -sin(theta);
	transformMatrix[1][0] = sin(theta);
	transformMatrix[1][1] = cos(theta);

	//printf("Rotation Value: %f \n", rotationValue);



	return 3;
}



