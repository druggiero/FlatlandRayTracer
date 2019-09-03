//Sphere.cpp
#include "Sphere.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <math.h>

Sphere::Sphere(double xIn, double yIn, double zIn, double sizeIn){

	xPos = 0;
	yPos = 0;
	zPos = 0;

	radius = sizeIn;
	translate(xIn, yIn, zIn);


}


tuple<int,int,int> Sphere::getColor(float distance, int fogHue, int fogStrength){
	tuple<int,int,int> color = std::make_tuple(100,100,100);
	
	int red, green, blue;

	red = 255;
	green = 0;
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



double Sphere::checkIntersection(vector<double> filmLinePoint, vector<double> directionVector){

	//no Matrix multiplication happening. Just adding the coordinates to get the position correct.

	filmLinePoint[0] = filmLinePoint[0] - xPos; //it's positive because the polygons are backwards
	filmLinePoint[1] = filmLinePoint[1] - yPos; //position becaue polygons are abckwards

	//using discriminant: b^2 - 4ac. Tells you # of roots.
	double a = pow(directionVector[0],2) + pow(directionVector[1],2);
	double b = (2*directionVector[0]*filmLinePoint[0] + 2*directionVector[1]*filmLinePoint[1]);
	double c = pow(filmLinePoint[0],2) + pow(filmLinePoint[1],2) + zPos*zPos - pow(radius,2);

	double discriminant = pow(b,2) - 4*a*c;

	//Discrim <0 means no real roots, = 0 means one root, > 0 means two roots.
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




void Sphere::translate(float x, float y, float z){
	xPos = xPos + x;
	yPos = yPos + y;
	zPos = zPos + z;
}




