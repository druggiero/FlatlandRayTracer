//Hexagon.cpp
#include "Hexagon.h"
//#include "Polygon.h"
#include "../functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>

Hexagon::Hexagon(float xIn, float yIn, float sizeIn){

	size = sizeIn;
	sideCount = 6;

	sidesEquations = sideCountToSideCoeffs(sideCount);
	initMatrices();
	translate(xIn, yIn);

	//printf("xpos, ypos: %f, %f \n", -xPos, -yPos);

	boundingCircle = std::make_shared<Circle>(xPos,yPos,size);
}


tuple<int,int,int> Hexagon::getColor(int side, float distance, int fogHue, int fogStrength){
	tuple<int,int,int> color = std::make_tuple(100,100,100);
	
	int red, green, blue;

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
		red = 255;
		green = 255;
		blue = 0;
	}
	else if(side == 3){
		red = 0;
		green =255;
		blue = 0;
	}
	else if(side == 4){

		red = 0;
		green = 185;
		blue = 255;
	}

	else if(side == 5){
		red = 0;
		green = 30;
		blue = 255;
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



