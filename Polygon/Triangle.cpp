//Triangle.cpp
#include "Triangle.h" 
#include "../functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>

Triangle::Triangle(float xIn, float yIn, float sizeIn, float topAngleIn){


	size = sizeIn;
	sideCount = 3;

	topAngle = topAngleIn;

	//isoceles triangle needs its own version of this functino:
	sidesEquations = sideCountToSideCoeffs(sideCount, topAngle);
	initMatrices();


	//printf("Tri b4 trans: xpos, ypos: %f, %f \n", xPos, yPos);
	translate(xIn, yIn);

	//printf("Tri: xpos, ypos: %f, %f \n", xPos, yPos);



	//could also initilize it to 0 position, then translate the shape.
	boundingCircle = std::make_shared<Circle>(xPos,yPos,size);

	//printf("Circ: getting rad: %f \n", boundingCircle->radius);
	//printf("Circ: xpos, yupos: %f, %f \n \n", boundingCircle->xPos, boundingCircle->yPos);

	book = false;
}


tuple<int,int,int> Triangle::getColor(int side, float distance, int fogHue, int fogStrength){
	tuple<int,int,int> color = std::make_tuple(100,100,100);
	
	int red, green, blue;



	if(book==false){

		if(side == 0){
			red = 255;
			green = 0;
			blue = 0;

			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}

		else if(side == 1){
			red = 0;
			green = 255;
			blue = 0;

			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}

		else if(side == 2){
			red = 0;
			green = 30;
			blue = 255;


			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}
	}

	else if(book==true && topAngle!=60){

		if(side == 0){
			red = 255;
			green = 110;
			blue = 0;

			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}

		else if(side == 1){
			red = 0;
			green = 0;
			blue = 0;

			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}

		else if(side == 2){
			red = 115;
			green = 0;
			blue = 255;


			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}
	}


	else{

		if(side == 0){
			red = 255;
			green = 0;
			blue = 0;

			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}

		else if(side == 1){
			red = 170;
			green = 170;
			blue = 170;

			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}

		else if(side == 2){
			red = 0;
			green = 0;
			blue = 255;


			red = (red*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			green  = (green*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));
			blue = (blue*(1 - distance/fogStrength)) + (fogHue*(distance/fogStrength));

		}
	}


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




vector< vector<double> > Triangle::sideCountToSideCoeffs (int sideCount, float topAngle){

	float rotationAngle = 360/(float)sideCount;
	int radius = size;


	vector< vector<double> > vertices;

	double theta = 90;

	double x;
	double y;


	if(topAngle==60){

		for(int i = 0; i<sideCount; i++){

			//printf("theta is a changing: %f \n", theta);

		 	x = radius * cos(degreesToRadians(theta));
			y = radius * sin(degreesToRadians(theta));
		
			//printf("Vertex %d: x, y,  %f, %f \n",i, x, y);

			vector<double> vert = {x,y};

			vertices.push_back(vert);

			theta = theta + rotationAngle;
		}

	}

	//special rotation case for isoceles triangles :)
	else{

		float baseRotation = topAngle * 2; //see Euclid Bk III, Prop 20.
		float sideRotation = (360-baseRotation)/2;
		vector<float> rotationAngleSequence = {sideRotation, baseRotation, sideRotation};

		for(int i = 0; i<sideCount; i++){

				//printf("theta is a changing: %f \n", theta);

			 	x = radius * cos(degreesToRadians(theta));
				y = radius * sin(degreesToRadians(theta));
			
				//printf("Side %d: x, y,  %f, %f \n",i, x, y);

				vector<double> vert = {x,y};

				vertices.push_back(vert);

				theta = theta + rotationAngleSequence[i];
			}


	}



	vector< vector<double> > sideCoeffs;

	for(int i = 0; i <sideCount; i++){
		vector<double> point1 = vertices[i];
		vector<double> point2;

		if(i==sideCount-1){
			point2 = vertices[0];
		}
		else{
			point2 = vertices[i+1];
		}

		//printf("Side %d we have point1 as (%f, %f), and point2 as (%f, %f) \n", i, point1[0], point1[1], point2[0], point2[1]);

		//take point1, point2, find linear equation of line which has both points.
		double rise = point1[1] - point2[1]; 
		double run = point1[0] - point2[0];

		double slope;
		double yCoeff;

		double xCoeff;
		vector<double> side;


		//printf("Rise: %f, Run: %f \n", rise, run);


		//margin of error for zero testing
		if(fabs(run)-0.004<0){
			//line is vertical
			slope = NULL;
			if(point1[0]< 0){

				xCoeff = -1;
			}
			else{
				xCoeff = 1;
			}

			vector<double> side = {xCoeff,0,fabs(point1[0])}; 
			//printf("Vertical Line: %fx + %fy lt %f  \n \n", side[0], side[1], side[2]);
			sideCoeffs.push_back(side);

			//you should try outputting this nice data :). TO a text file.

		}

		else{

			slope = rise/run;

			
			double yIntercept = point1[1] - (slope*point1[0]);

			//printf("slope is %f , yIntercept is  %f \n", slope, yIntercept);
		

			if(yIntercept < 0){
				yCoeff = -1;
				xCoeff = slope;

			}
			else{
				yCoeff = 1;
				xCoeff = -slope;

			}
			//this function is currently going in counter-clockwise order.
			vector<double> side = {xCoeff, yCoeff, fabs(yIntercept)};

			//printf("Non-Vertical Line: %fx + %fy lt %f \n \n", side[0], side[1], side[2]);
			sideCoeffs.push_back(side);
		}



	}

	return sideCoeffs;
}



