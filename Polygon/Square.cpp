//Square.cpp

#include "Square.h"
//#include "Polygon.h"
#include "../functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>

Square::Square(float xIn, float yIn, float sizeIn){


	size = sizeIn;
	sideCount = 4;


	sidesEquations = sideCountToSideCoeffs(sideCount);
	initMatrices();


	//printf("xpos, ypos: %f, %f \n", -xPos, -yPos);
	translate(xIn, yIn);	
	boundingCircle = std::make_shared<Circle>(xPos,yPos,size);

	book = false;
	narr = false;
}


tuple<int,int,int> Square::getColor(int side, float distance, int fogHue, int fogStrength){
	tuple<int,int,int> color = std::make_tuple(100,100,100);
	
	int red, green, blue;


	if(book == false && narr ==false){
		if(side == 0){
			red = 255;
			green = 0;
			blue = 0;
		}
		else if(side == 1){
			red = 255;
			green = 155;
			blue = 0;
		}
		else if(side == 2){
			red = 0;
			green =255;
			blue = 0;
		}
		else if(side == 3){
			red = 0;
			green = 30;
			blue = 255;
		}
	}

	else if(book==true){
		if(side == 0){
			red = 212;
			green = 115;
			blue = 212;
		}
		else if(side == 1){
			red = 64;
			green = 0;
			blue = 255;
		}
		else if(side == 2){
			red = 228;
			green = 155;
			blue = 15;
		}
		else if(side == 3){
			red = 138;
			green = 51;
			blue = 36;
		}
	}

	else{
		if(side == 0){
			/*
			red = 0;
			green = 255;
			blue = 255;
			*/
			red = 255;
			green = 0;
			blue = 0;
		}
		else if(side == 1){
			/*
			red = 0;
			green = 255;
			blue = 255;
			*/
			red = 255;
			green = 0;
			blue = 0;
		}
		else if(side == 2){
			/*
			red = 0;
			green = 255;
			blue = 255;
			*/
			red = 255;
			green = 0;
			blue = 0;
		}
		else if(side == 3){
			/*
			red = 0;
			green = 255;
			blue = 255;
			*/
			red = 255;
			green = 0;
			blue = 0;
		}
	}

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


