//functions.cpp
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <SDL.h>

#define PI (3.14159265358979323846)  

const int WIDTH = 301;
//const int WIDTH = 1100;  //military image
const int HEIGHT = 1;


SDL_Window* win = NULL;
SDL_Surface* baseSurface = NULL;

SDL_Texture* texture = NULL;
SDL_Renderer* renderer = NULL;


void setPix(int x, int y, int r, int g, int b){

	SDL_UnlockSurface(baseSurface);


	Uint32 colorInteger = SDL_MapRGB(baseSurface->format,r,g,b);
	//printf("Cool color: %d \n", colorInteger);
	Uint32 *pixelPointer = (Uint32*)baseSurface->pixels;
	int width = baseSurface->w;
	pixelPointer[(y * width) + x] = colorInteger;  

	SDL_LockSurface(baseSurface);

}


vector<double> addMats1D(vector<double> matrix1, vector<double> matrix2){

	vector<double> outMat(matrix1.size());

	if(matrix1.size() != matrix2.size()){
		printf("Not the same size, cannot add matrices. Returning empty matrix. \n");
		return outMat;
	}

	for(int i =0; i <matrix1.size(); i++){
		outMat[i] = matrix1[i] + matrix2[i];
	}


	return outMat;

}


vector<double> subtractMats1D(vector<double> matrix1, vector<double> matrix2){

	vector<double> outMat(matrix1.size());

	if(matrix1.size() != matrix2.size()){
		//printf("Not the same size, cannot subtract matrices. Returning empty matrix. \n");
		return outMat;
	}

	for(int i =0; i <matrix1.size(); i++){
		outMat[i] = matrix1[i] - matrix2[i];
	}

	return outMat;

}

vector<double> applyMatScalar(double scalar, vector<double> matrix){
	for(int i = 0; i<matrix.size();i++){
		matrix[i] = matrix[i] * scalar;
	}

	return matrix;
}

 vector<double> multMatbyVec(vector<vector<double> > matrix, vector<double> vect){
 	vector<double> outMat(matrix.size());
 	//printf("Number of columns in  matrix: %d \n", matrix[0].size());
 	//printf("Number of rows in vector: %d \n", vect.size());
	

 	if(matrix[0].size() != vect.size()){
 		printf("Number of columns in matrix does not match number of rows in vector. \n");
 		return outMat;
 	}


 	for(int i = 0; i< matrix.size(); i++){  //for every row of the matrix...
 		for(int j = 0; j<vect.size(); j++){
 			outMat[i] = outMat[i] + (vect[j] * matrix[i][j]);
 		}


 	}

 	return outMat;

 }

vector<vector<double>> multMatbyMat(vector<vector<double> > matrix1, vector<vector<double> > matrix2){

	//multiply two matrices here!

	vector<vector<double>> outMatrix(matrix1.size(), vector<double>(matrix2[0].size(), 0));


	if(matrix1[0].size() != matrix2.size()){
		printf("Number of columns in matrix 1 does not match number of rows in matrix2.");
		return outMatrix;
	}

	for(int i = 0; i< matrix1.size(); i++){  //for every row of the matrix...
 		for(int j = 0; j<matrix2[0].size(); j++){
 			for(int h = 0; h<matrix1[0].size(); h++){
 				outMatrix[i][j] = outMatrix[i][j] + (matrix1[i][h]*matrix2[h][j]);
 				//wtf is goin on here/
 			}
 			//printf("outmatrix[i][j]: %f\n", outMatrix[i][j]);
 		}
 	}

	return outMatrix;

}


 double degreesToRadians(double degrees){
 	return (degrees * PI)/180.0;

 }


bool sortByDist(pair<int, double> one, pair <int,double> two){
	return one.second < two.second;

}


void init(){

	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL Initialization Failed. How did that happen? \n");
	}

	else{
		win = SDL_CreateWindow("Flatland Ray-Tracer", 450,100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(win, -1, 0);
		//renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(renderer, 0,0,0,255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

		//get a surface directly from the window
		//baseSurface = SDL_GetWindowSurface(win);


/*
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif
	*/


		baseSurface = SDL_CreateRGBSurface(0,WIDTH, HEIGHT,32,0xff000000, 0x00ff0000, 0x0000ff00,  0x000000ff);
		//texture = SDL_CreateTextureFromSurface(renderer, baseSurface);

		//SDL_CreateTextureFromSurface(renderer, baseSurface);


		SDL_Surface *iconSurface = SDL_LoadBMP("icon2.bmp");
		SDL_SetWindowIcon(win, iconSurface);
		SDL_FreeSurface(iconSurface);

	}

}

void updateScreen(){


	//printf("EVerything is just fine. \n \n ");


	SDL_UpdateTexture(texture, NULL, baseSurface->pixels, WIDTH * 4);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

}



void close(){

	//do not free this surface if it comes from win
	SDL_FreeSurface(baseSurface);

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(win);
	win = NULL;

	SDL_Quit();

}

