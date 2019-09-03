//Pentagon.cpp
#include "Pentagon.h"
//#include "Polygon.h"
#include "../functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>

Pentagon::Pentagon(float xIn, float yIn, float sizeIn){


	size = sizeIn;
	sideCount = 5;

	sidesEquations = sideCountToSideCoeffs(sideCount);
	initMatrices();
	translate(xIn, yIn);

	boundingCircle = std::make_shared<Circle>(xPos,yPos,size);

	chroma  = false;

}


tuple<int,int,int> Pentagon::getColor(int side, float distance, int fogHue, int fogStrength){
	tuple<int,int,int> color = std::make_tuple(100,100,100);
	
	int red, green, blue;

	if(chroma == false){

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
			green = 185;
			blue = 255;
		}
		else if(side == 4){
			red = 0;
			green = 30;
			blue = 255;
		}
	}

	else{

		if(side == 0){
			red = 255;
			green =130;
			blue = 13;
		}

		else if(side == 1){
			red = 244;
			green = 0;
			blue = 203;
		}

		else if(side == 2){
			red = 0;
			green =39;
			blue = 43;
		}


		else if(side == 3){

			red = 120;
			green = 170;
			blue = 245;
		}
		else if(side == 4){
			red = 0;
			green = 153;
			blue = 51;
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









