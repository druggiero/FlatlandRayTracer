//Polygon.cpp
#include "Polygon.h"
#include "../Circle.h"
#include "../functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <memory>
#include <tuple>

Polygon::Polygon(){


	//this value is in degrees
	rotationValue = 0;

	//start at origin
	xPos = 0;
	yPos = 0; 
	size = 100;
	h = 0;
	v = 0;

	shared_ptr<Circle> boundingCircle;

}


pair<int, double> Polygon::checkIntersection(vector<double> filmLinePoint, vector<double> directionVector){
	double distance = 0.0;

	vector<pair<int, double> > sidesAndDistances;

	//applying transformations as per the stored matrices:

	//RT   (spinning order)
	//vector< vector<double>> transMatrix = multMatbyMat(rotationMatrix,  translationMatrix);

	//TR test:	(orbit order)
	//vector< vector<double>> transMatrix = multMatbyMat(translationMatrix, rotationMatrix);
	//https://bobobobo.wordpress.com/2011/12/20/rotation-translation-vs-translation-rotation/

	//ART
	//transformedSidesCoeffs = multMatbyMat(homoSidesCoeffs, transMatrix);
	//int sideCount = transformedSidesCoeffs.size() - 1;

	/*
	for(int i = 0; i<sideCount; i++){
		sides[i][0] = transformedSidesCoeffs[i][0];
		if(filmLinePoint[0]==-41){
			//printf("sides[i][0]: %f \n", sides[i][0] );
		}
		sides[i][1] = transformedSidesCoeffs[i][1];

		sides[i][2] = sidesConsts[i] - transformedSidesCoeffs[i][2];
	}
	*/

	filmLinePoint.push_back(1);
	directionVector.push_back(1);

	vector<double> filmLinePointT = multMatbyVec(composeMatrix, filmLinePoint);
	vector<double> directionVectorT = multMatbyVec(invLinearTransformMatrix, directionVector);


	for(int s = 0; s<sideCount; s++){
		vector<double> sideToTest = sides[s];
		distance = checkSideIntersection(sideToTest, filmLinePointT, directionVectorT);
		pair<int, double> sideWithDist;
		sideWithDist = std::make_pair(s, distance); 
		sidesAndDistances.push_back(sideWithDist);
		
		//printf("side: %d , dist: %f \n", s, distance);

	}

	//printf("filmLinePoint: %f, %f \n", filmLinePoint[0], filmLinePoint[1]);
	//printf("size: %d \n", sidesAndDistances.size());
	std::sort(sidesAndDistances.begin(), sidesAndDistances.end() , sortByDist);
	//printf("Distaces in last place: %f \n", sidesAndDistances[3]);
	//printf("Distances in order: %f, %f, %f, %f \n", sidesAndDistances[0].second, sidesAndDistances[1].second, sidesAndDistances[2].second, sidesAndDistances[3].second);

	//printf("sidesConsts: %f, %f, %f \n", sidesConsts[0], sidesConsts[1], sidesConsts[2]);

	
	//filmLinePoint.push_back(1);
	//directionVector.push_back(1);
	//filmLinePoint = multMatbyVec(invTransformMatrix, filmLinePoint);
	//directionVector = multMatbyVec(invTransformMatrix, directionVector);



	for(int s = 0; s<sidesAndDistances.size(); s++){
		float pDistance = sidesAndDistances[s].second;
		bool inBounds = true;

		if(pDistance > 0){
			//printf("iteration:%d side:%d distance:%f \n", s, sidesAndDistances[s].first, sidesAndDistances[s].second);
		
			//find intersection point using closest potential dist value
			//printf("dvec %f, %f \n", directionVector[0], directionVector[1]);
			//printf("pDistance %f \n", pDistance);
			vector<double> scaledDvec = applyMatScalar(pDistance, directionVector);
			vector<double> intersectionPoint = addMats1D(filmLinePoint, scaledDvec);


			//printf("intersection Point x: %f,  y: %f \n", intersectionPoint[0], intersectionPoint[1]);
			//printf("bounding x and y: %f, %f \n", boundingCircle->xPos, boundingCircle->yPos);
			//printf("shdkajshdkjahsdkja: %f \n", pow((intersectionPoint[0]+boundingCircle->xPos),2) + pow((intersectionPoint[1]+boundingCircle->yPos),2) );
			//printf("jahsdkja: %f \n", pow((intersectionPoint[0]-boundingCircle->xPos),2) + pow((intersectionPoint[1]-boundingCircle->yPos),2) );


			//check if the intersectionPoint lies inside the bounding circle.
			//ummmm....should this really by MINUS?
			if(pow((intersectionPoint[0]-boundingCircle->xPos),2) + pow((intersectionPoint[1]-boundingCircle->yPos),2) > (boundingCircle->radius*boundingCircle->radius)){
				inBounds = false;
			}

			/*

			if(inBounds ==true){


				intersectionPoint.push_back(1);//adding homogenous coordinate


				//does the intersection Point lie in the intersection of all the half-planes?
				//must check that Ax - b <= 0

				//vector<double> Ax = multMatbyVec(rotatedSidesCoeffs, intersectionPoint);

				vector<double> Ax = multMatbyVec(transformedSidesCoeffs, intersectionPoint);

				vector<double> Ax_minus_b = subtractMats1D(Ax, sidesConsts);


				//succesfully checks if the point is within the proper bounds.
				//maybe you don't need this if you have a bounding circle,
				//assuming the polgon is regular.	

				
				for(int v = 0; v<Ax_minus_b.size()-1; v++){
					//if(filmLinePoint[0]==0){

						//printf("IntersectionPoint: %f, %f \n", intersectionPoint[0], intersectionPoint[1]);
						//printf("Vindex: %d, Ax: %f, for side: %d, dist: %f \n", v, Ax[v], sidesAndDistances[s].first, sidesAndDistances[s].second);
						//printf("AxminusB: %f, for side: %d, dist: %f \n \n", Ax_minus_b[v], sidesAndDistances[s].first, sidesAndDistances[s].second);
					//}


					if(Ax_minus_b[v] > 0.005){  //this is the epsilon, to reduce problems from floating point precision error
						printf("Ray %f hit side %d, which is %f units away. But it is out of bounds.\n", filmLinePoint[0], sidesAndDistances[s].first, sidesAndDistances[s].second);
						inBounds = false;	
					}

				}

				

			}

			*/

			

			if(inBounds == true){
				//printf("Ray %f hit side %d, which is %f units away.\n", filmLinePoint[0], sidesAndDistances[s].first, sidesAndDistances[s].second);
				//printf("dvec %f, %f \n", directionVector[0], directionVector[1]);
				//printf("pDistance %f \n", pDistance);
				//printf("intersection Point x: %f,  y: %f \n", intersectionPoint[0], intersectionPoint[1]);

				return sidesAndDistances[s];
			}

			else{
				//printf("Ray %f intersects side %d, but is out of figure bounds. \n", filmLinePoint[0], sidesAndDistances[s].first);
			}
		}

	}
	
return std::make_pair(0, NULL);	
	

}

float Polygon::rotate(float angle){
	
	
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


	//rotationMatrix[0][0] = cos(theta);
	//rotationMatrix[0][1] = sin(theta);
	//rotationMatrix[1][0] = -sin(theta);
	//rotationMatrix[1][1] = cos(theta);

	/*
	counterclockwise rotation matrix, will rotate line clockwise for whatever reason
	[cos   -sin ]
	[sin    cos ]
	*/

	/*Try this one instead? YEAH

	[cos   	 sin ]
	[-sin    cos ]

	*/


	//printf("Rotation Value: %f \n", rotationValue);

	invRotationMatrix[0][0] = cos(theta);
	invRotationMatrix[0][1] = sin(theta);
	//invLinearTransformMatrix[0][2] = -yPos*sin(theta) -xPos*cos(theta);
	invRotationMatrix[1][0] = -sin(theta);
	invRotationMatrix[1][1] = cos(theta);
	//invLinearTransformMatrix[1][2] = -yPos*cos(theta) + xPos*sin(theta);

	invLinearTransformMatrix = multMatbyMat(invSShearTransformMatrix, invRotationMatrix);
	composeMatrix = multMatbyMat(invLinearTransformMatrix, invTranslationMatrix);

	return 3;
}

void Polygon::shear(float horz, float vert){
	h = h + horz;
	v = v + vert;

	/*
	invSShearTransformMatrix[0][0] = -1/(h*v);
	invSShearTransformMatrix[0][1] = 1/v;
	invSShearTransformMatrix[1][0] = 1/h;
	invSShearTransformMatrix[1][1] = -1/(h*v);
	*/

	invSShearTransformMatrix[0][0] = 1;
	invSShearTransformMatrix[0][1] = -h;  //flipping the negative h and v --does it make a diff?
	invSShearTransformMatrix[1][0] = -v;
	invSShearTransformMatrix[1][1] = 1;


	invLinearTransformMatrix = multMatbyMat(invSShearTransformMatrix, invRotationMatrix);
	composeMatrix = multMatbyMat(invLinearTransformMatrix, invTranslationMatrix);

	//I imagine that the strange shear behavior has something to do with both bounding circle
	//...you don't check points being inbounds of shape, only points in bounds of circle, remember.


}


void Polygon::translate(float x, float y){

	//use homogenous coordinates to use affine transformation with matrix mult
	//rotation is a linear transformation, translation an affine transformation

	xPos = xPos + x;
	yPos = yPos + y;

	//translationMatrix[0][2] = xPos;
	//translationMatrix[1][2] = yPos;

	//printf("new xPos: %f \n", xPos);
	//printf("new yPos: %f \n", yPos);

	invTranslationMatrix[0][2] = -xPos;
	invTranslationMatrix[1][2] = -yPos;


	composeMatrix = multMatbyMat(invLinearTransformMatrix, invTranslationMatrix);
	//printf("invTransform,x and y: %f, %f \n", invTransformMatrix[0][2], invTransformMatrix[1][2]);


	//translate bounding circle with the shape.
	if(boundingCircle!=NULL){
		boundingCircle->translate(x,y);
		//printf("bounding circ X, Y: %f, %f \n", boundingCircle->xPos, boundingCircle->yPos);
	}

}




float Polygon::checkSideIntersection(vector<double> side, vector<double> filmLinePoint,
 									vector<double> directionVector){

	/*
	float testy = filmLinePoint[0];
	if(testy==0){
	//	printf("filmLinePoint, b4 transform: %f, %f \n", filmLinePoint[0], filmLinePoint[1]);
	//	printf("directionVector, b4 transform: %f, %f \n", directionVector[0], directionVector[1]);
	}
	*/



	float lambda;
	//thx Gortler

	/*
	if(testy==0){
	//	printf("side information: A:%f, B:%f, C:%f \n", side[0], side[1], side[2]);
	//	printf("filmLinePoint, after transform: %f, %f \n", filmLinePoint[0], filmLinePoint[1]);
	//	printf("directionVector, after transform: %f, %f \n", directionVector[0], directionVector[1]);

	}
	*/


	//this *adds* the C value, as once the half-space stuff is figured out the lines lind of swap sides
	lambda = ((-side[0]*filmLinePoint[0])-(side[1]*filmLinePoint[1]) + side[2]) 
	/ (side[0]*directionVector[0] + side[1]*directionVector[1]);

	/*
	if(testy==0){
		//printf("lambda: %f \n \n", lambda);
	}
	*/


	return lambda;
}


vector< vector<double> > Polygon::sideCountToSideCoeffs (int sideCount){

	//printf("Side Count: %d \n", sideCount);
	double rotationAngle = 360/(double)sideCount;
	//printf("Rotation Angle: %f \n", rotationAngle);
	int radius = size;


	vector< vector<double> > vertices;

	double theta = 90;

	double x;
	double y;

	for(int i = 0; i<sideCount; i++){

		//printf("theta is a changing: %f \n", theta);

	 	x = radius * cos(degreesToRadians(theta));
		y = radius * sin(degreesToRadians(theta));
	
		//printf("Vertex %d: x, y,  %f, %f \n",i, x, y);

		vector<double> vert = {x,y};

		vertices.push_back(vert);

		theta = theta + rotationAngle;
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

		//printf("\nSide %d: point1 is (%f, %f), and point2 is (%f, %f) \n", i, point1[0], point1[1], point2[0], point2[1]);

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

			//printf("Vertical Line: %fx + %fy <= %f  \n \n", side[0], side[1], side[2]);
			
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

			//printf("Non-Vertical Line: %fx + %fy <= %f \n \n", side[0], side[1], side[2]);
			
			sideCoeffs.push_back(side);
		}



	}

	return sideCoeffs;
}



bool Polygon::initMatrices(){

	//Ax + By = C


	//takes A and B from sidesEquations, puts it in sidesCoeffs
	for(int i =0; i<sideCount; i++){
		vector<double> sideHoldVector = {sidesEquations[i][0], sidesEquations[i][1]};
		sidesCoeffs.push_back(sideHoldVector);
	}


	//gets constant values from sidesEquations. (these can vary by side)
	for (int i = 0; i<sideCount; i++){
		sidesConsts.push_back(sidesEquations[i][2]);
		
	}

	sidesConsts.push_back(1);
	
	for(int i = 0; i<sidesCoeffs.size(); i++){
		vector<double> holderVec(sidesCoeffs[i]); //copies sidesCoeffs
		holderVec.push_back(sidesConsts[i]);
		sides.push_back(holderVec);

	}	


	/*
	transformedSidesCoeffs = sidesCoeffs;
	homoSidesCoeffs = sidesCoeffs;


	for(int i = 0; i<sideCount; i++){
		transformedSidesCoeffs[i].push_back(0); //homo?
		homoSidesCoeffs[i].push_back(0);
	} 

	vector<double> finalRow;
	double fRowVals[] = {0,0,1};
	finalRow.assign(fRowVals, fRowVals+3);
	transformedSidesCoeffs.push_back(finalRow);
	homoSidesCoeffs.push_back(finalRow);

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

	*/

	//inverse simul-shear matrix
	vector<double> invS_row0;
	vector<double> invS_row1;
	vector<double> invS_row2;

	/*
	double invS_row0Vals[] = {-1/(h*v), 1/v, 0};
	double invS_row1Vals[] = {1/h, -1/(h*v), 0};
	double invS_row2Vals[] = {0, 0, 1};
	*/

	double invS_row0Vals[] = {1, 0, 0};
	double invS_row1Vals[] = {0, 1, 0};
	double invS_row2Vals[] = {0, 0, 1};


	invS_row0.assign( invS_row0Vals, invS_row0Vals+3);
	invS_row1.assign( invS_row1Vals, invS_row1Vals+3);
	invS_row2.assign( invS_row2Vals, invS_row2Vals+3);

	invSShearTransformMatrix.push_back(invS_row0);
	invSShearTransformMatrix.push_back(invS_row1);
	invSShearTransformMatrix.push_back(invS_row2);



	//inverse linear transform matrix
	vector<double> inv_row0;
	vector<double> inv_row1;
	vector<double> inv_row2;

	double inv_row0Vals[] = {cos(0), sin(0), 0};
	double inv_row1Vals[] = {-sin(0), cos(0), 0};
	double inv_row2Vals[] = {0, 0, 1};


	inv_row0.assign( inv_row0Vals, inv_row0Vals+3);
	inv_row1.assign( inv_row1Vals, inv_row1Vals+3);
	inv_row2.assign( inv_row2Vals, inv_row2Vals+3);

	invRotationMatrix.push_back(inv_row0);
	invRotationMatrix.push_back(inv_row1);
	invRotationMatrix.push_back(inv_row2);



	//inverse translation matrix
	vector<double> invT_row0;
	vector<double> invT_row1;
	vector<double> invT_row2;

	double invT_row0Vals[] = {1, 0, -xPos};
	double invT_row1Vals[] = {0, 1, -yPos};
	double invT_row2Vals[] = {0, 0, 1};

	invT_row0.assign( inv_row0Vals, inv_row0Vals+3);
	invT_row1.assign( inv_row1Vals, inv_row1Vals+3);
	invT_row2.assign( inv_row2Vals, inv_row2Vals+3);

	invTranslationMatrix.push_back(invT_row0);
	invTranslationMatrix.push_back(invT_row1);
	invTranslationMatrix.push_back(invT_row2);


	//printf("xPos, yPos: %f, %f \n \n ", invTransformMatrix[0][2], invTransformMatrix[1][2]);

	invLinearTransformMatrix = multMatbyMat(invSShearTransformMatrix, invRotationMatrix);
	composeMatrix = multMatbyMat(invLinearTransformMatrix, invTranslationMatrix);

}



