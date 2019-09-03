//Woman.cpp

#include "Woman.h"
//#include "Polygon.h"
#include "../functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>

Woman::Woman(float xIn, float yIn, float sizeIn){
	size = sizeIn;
	sideCount = 4;

	sidesEquations = sideCountToSideCoeffs(sideCount);
	initMatrices();

	shear(200,0);
	translate(xIn, yIn);
	boundingCircle = std::make_shared<Circle>(xPos,yPos,size);
}


tuple<int,int,int> Woman::getColor(int side, float distance, int fogHue, int fogStrength){
	tuple<int,int,int> color = std::make_tuple(100,100,100);
	
	int red, green, blue;


	if(side == 0){
		red = 0;
		green = 0;
		blue = 0;
	}
	else if(side == 1){

		red = 0;
		green = 153;
		blue =51;
	}
	else if(side == 2){
		red = 255;
		green = 255;
		blue = 255;
	}

	else if(side == 3){
		red = 102;
		green = 0;
		blue = 102;
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


