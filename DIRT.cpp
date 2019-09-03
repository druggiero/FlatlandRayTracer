//Flatland Ray-Tracer
//First Started: 02/20/17
//Last Updated: 12/17/18
//D.Ruggiero 

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <tuple>
#include <memory>
#include <list>
#include <type_traits>
#include <typeinfo>
//#include <time.h>
//#include <windows.h>


//don't need to include Polygon because Polygon.h is included in the derived classes
#include "Polygon/Triangle.h"
#include "Polygon/Square.h"
#include "Polygon/Pentagon.h"
#include "Polygon/Hexagon.h"
#include "Polygon/Heptagon.h"
#include "Polygon/Octagon.h"
#include "Polygon/Nonagon.h"
#include "Polygon/Decagon.h"
#include "Polygon/Priest.h"
#include "Polygon/Woman.h"

#include "Circle.h"
#include "Sphere.h"
#include "Viewer.h"

#include "functions.h"



using std::vector;
using std::list;
using std::get;
using std::shared_ptr;
//using namespace std;


int frameNum = 0;

int main(int argc, char* args[]){
	
	init();
	//ofstream outText("output.txt");

	//srand(time(NULL));


	for(int x = 0; x < WIDTH; x++){
		for(int y = 0; y < HEIGHT; y++){
		//setPix(x,y, 16, 16, 16);
		setPix(x,y, 255, 255, 255);
		}				
	}

	int focalLength = (int) WIDTH * (50/35.0);
	//for width of 300, this focal length of 428
	
	//float viewerPos = -foc - 3022;  //for testing error.

	//Polygon *pwe = &t;
	//Polygon * test[100];
	//Square * test[100];

	vector<std::shared_ptr<Polygon> > objects;


	shared_ptr<Triangle> iso_triangle = std::make_shared<Triangle>(0,0,100,20);
	shared_ptr<Triangle> triangle = std::make_shared<Triangle>(0,0,100);
	shared_ptr<Square> square = std::make_shared<Square>(0, 0, 100);
	shared_ptr<Pentagon> pentagon = std::make_shared<Pentagon>(0, 0, 100);
	shared_ptr<Hexagon> hexagon = std::make_shared<Hexagon>(0, 0, 100);
	shared_ptr<Heptagon> heptagon = std::make_shared<Heptagon>(0, 0, 100);
	shared_ptr<Octagon> octagon = std::make_shared<Octagon>(0, 0, 100);
	shared_ptr<Nonagon> nonagon = std::make_shared<Nonagon>(0, 0, 100);
	shared_ptr<Decagon> decagon = std::make_shared<Decagon>(0, 0, 100);	
	shared_ptr<Priest> priest = std::make_shared<Priest>(0,0,100);
	shared_ptr<Woman> woman = std::make_shared<Woman>(0,0,100);

	objects.emplace_back(square);
	

	/*code for the military review image:
	 set width to 1100 before compilation*/
	/*
	for(int i = 0; i<20; i++){
		shared_ptr<Triangle> iso_triangle_1 = std::make_shared<Triangle>(-548 + (i*58),10,22,28);
		objects.emplace_back(iso_triangle_1);}
	for(int i = 0; i<5; i++){
		shared_ptr<Triangle> triangle = std::make_shared<Triangle>(-500 + (i*80),-14,34);
		objects.emplace_back(triangle);}
	for(int i = 0; i<3; i++){
		shared_ptr<Square> sq = std::make_shared<Square>(100+(i*130),-21,38);
		objects.emplace_back(sq);}
	shared_ptr<Pentagon> pt = std::make_shared<Pentagon>(650, -33, 44);
	shared_ptr<Hexagon> hx = std::make_shared<Hexagon>(-650, -33, 44);
	objects.emplace_back(pt);
	objects.emplace_back(hx);
	for(int i = 0; i<3; i++){
		shared_ptr<Triangle> gun = std::make_shared<Triangle>(45+(i*126), -21, 21);
		gun->rotate(90);
		objects.emplace_back(gun);}
	*/
	/*ends*/

	//vector<std::shared_ptr<Circle> > circles;
	//shared_ptr<Circle> circley = std::make_shared<Circle>();
	//circles.emplace_back(circley);

	vector<std::shared_ptr<Sphere> > spheres;
	shared_ptr<Sphere> sphere = std::make_shared<Sphere>(0,0,0,100);
	spheres.emplace_back(sphere);
	bool sphereView = false;

	Viewer viewer(0, -focalLength - 140);
	SDL_Event event;
	bool running = true;

	int fogHue = 255;
	int fogStrength = 50;
	//military image FS was 78
	//int fogStrength = 78;

	//int ptog = -1;
	//int htog = 1;

	//main loop
	while(running){
		int intersectionCount = 0;

		for(int w = 0; w<WIDTH; w++){
			setPix(w,HEIGHT/2, fogHue, fogHue, fogHue);
		
			vector<double> pixelPoint;
			float pixelCoor[] = {w - (WIDTH/2), focalLength};  //location of film line, assuming origin
			pixelPoint.assign(pixelCoor, pixelCoor+2);
			
			vector<double> scaledDirection = subtractMats1D(pixelPoint, {0,0});
			//renormalize the dvec by 1/foc, as the film line is foc units away from emission point			
			vector<double> reScaledDirection = applyMatScalar((1/(float)focalLength), scaledDirection); 

			//I am still not 100% certain why we don't need to rotate the viewer DVec.
			pixelPoint.push_back(1);
			pixelPoint = multMatbyVec(viewer.transformMatrix, pixelPoint);
			pixelPoint.erase(pixelPoint.end()-1);
			//printf("pixelPoint: %f,%f \n", pixelPoint[0], pixelPoint[1]);

			//we now have pixel point and direction vector. We have both vectors needed for ray.
			float closestDist = 1000000000;
			float intersectionDist;
			int intersectedSide;
			std::shared_ptr<Polygon> closestPoly = NULL;
			pair<int, double> closestIntersectedSideAndDist;
		
			for(int o = 0; o<objects.size(); o++){

				//may be helpful to use  a template function depending on class it is fed
				//i.e., when you got to process the object.
				//returns a distance and a side number (if it is a circle, returns 0, maybe the quadrant someday)
				
				double boundingDist = objects[o]->boundingCircle->checkIntersection(pixelPoint, reScaledDirection);
				if(boundingDist>0.00001){
					//setPix(pixelCoor[0]+(WIDTH/2), HEIGHT/2, 50,255,155);
					pair<int, double> intersectionSideAndDist  = objects[o]->checkIntersection(pixelPoint, reScaledDirection);
					intersectionDist = intersectionSideAndDist.second;
					intersectedSide = intersectionSideAndDist.first;

					//printf("Object: %d, intersectionDist: %f \n", o, intersectionDist);
					//printf("intersectedSide: %d \n", intersectedSide);

					if(intersectionDist!=NULL && intersectionDist < closestDist){
						//printf("intersectionDist is smaller than closestDist");
						closestDist = intersectionDist;
						closestIntersectedSideAndDist = intersectionSideAndDist;
						closestPoly = objects[o];
						//printf("intersectedSide: %d \n", intersectedSide);
					}
				}
			}

			if(closestPoly != NULL && sphereView==false){
				tuple<int,int,int> colorRGB = closestPoly->getColor(closestIntersectedSideAndDist.first, closestIntersectedSideAndDist.second, fogHue, 300-fogStrength);
				//printf("INTERSECTION!!!\n");
				intersectionCount = intersectionCount + 1;
				setPix(pixelCoor[0]+(WIDTH/2), HEIGHT/2, get<0>(colorRGB),get<1>(colorRGB),get<2>(colorRGB));
			}

			if(sphereView==true){
				double sphereIntersectionDist = spheres[0]->checkIntersection(pixelPoint, reScaledDirection);
				if(sphereIntersectionDist!=NULL && sphereIntersectionDist > 0){
					tuple<int,int,int> colorRGB = spheres[0]->getColor(sphereIntersectionDist, fogHue, 300-fogStrength);
					setPix(pixelCoor[0]+(WIDTH/2), HEIGHT/2, get<0>(colorRGB),get<1>(colorRGB),get<2>(colorRGB));
				}
			}
		}

		
		for(int i = 0; i<objects.size(); i++){
			objects[i]->rotate(0.7);
		}

		/*military review animation:*/
		/*
		for(int i = 0; i<objects.size(); i++){
			if(i<20){
				objects[i]->rotate(1.5);
			}
			if(i>=20 && i<=24){
				objects[i]->rotate(-3);
			}
			if(i>24 && i<=27){
				objects[i]->rotate(-4.5);
			}
			if(i==28){
				//pentagon
				if(objects[i]->xPos >= 651 || objects[i]->xPos <= -651){
					ptog = -ptog;
				}
				objects[i]->rotate(-3);
				objects[i]->translate(2*ptog,0);
			}
			if(i==29){
				//hexagon
				if(objects[i]->xPos >= 651 || objects[i]->xPos <= -651){
					htog = -htog;
				}
				objects[i]->rotate(3);
				objects[i]->translate(2*htog,0);
			}
		}
		*/
		/*ends */

		//update texture
		updateScreen();

		/* for gif making: */
		if(frameNum % 4 == 0){
			char charBuffer[50];
			sprintf(charBuffer, "frames/screen_%04d.png", frameNum);		
			//SDL_SaveBMP(baseSurface, charBuffer);
		}
		
		frameNum ++;
		bool move = true;	
		int speed = 4;

			while(SDL_PollEvent(&event)){
				switch(event.type){
					case SDL_QUIT:
						printf("Exiting DIRT.");
						running = false;
						break;

					case SDL_KEYDOWN:
						switch(event.key.keysym.sym ){

							case SDLK_UP:			
								//tentative step
								viewer.forward(speed);							
								for(int i = 0; i<objects.size(); i++){
									if( sqrt((viewer.xPos-objects[i]->xPos)*(viewer.xPos-objects[i]->xPos)  + (viewer.yPos-objects[i]->yPos)*(viewer.yPos-objects[i]->yPos)) <= objects[i]->size + focalLength ){
										//gotta check x as well. in fact just check x,y. euclidean dist.
										move = false;
									}
								}

								//move = true;
								if(move==false){
									//if it intersects, undo tentative step
									viewer.forward(-speed);	
								}
								else{
									printf("Pressed Up, viewer position at %f \n", viewer.yPos);
								}
								break;

							case SDLK_DOWN:
								//tentative step
								viewer.forward(-speed);
								for(int i = 0; i<objects.size(); i++){
									if( sqrt((viewer.xPos-objects[i]->xPos)*(viewer.xPos-objects[i]->xPos)  + (viewer.yPos-objects[i]->yPos)*(viewer.yPos-objects[i]->yPos)) <= objects[i]->size + focalLength ){
										move = false;
									}
								}

								//move = true;
								if(move==false){
									//if it intersects, undo tentative step
									viewer.forward(speed);	
								}
								else{
									printf("Pressed Down, viewer position at %f \n", viewer.yPos);	

						
								}
								break;

							case SDLK_LEFT:
								viewer.rotate(2);
								printf("Pressed Left, rotation value at %f \n \n", viewer.rotationValue);
							
								break;

							case SDLK_RIGHT:
								viewer.rotate(-2);
								printf("Pressed Right, rotation value at %f \n \n", viewer.rotationValue);
								break;
							

							case SDLK_a:
								objects[0]->translate(-2,0);
								break;
							case SDLK_d:
								objects[0]->translate(2,0);
								break;
							case SDLK_w:
								objects[0]->translate(0,2);
								break;
							case SDLK_s:
								objects[0]->translate(0,-2);
								break;

							case SDLK_e:
								objects[0]->rotate(2);
								//printf("object rot value: %f \n", objects[0]->rotationValue);
								objects[0]->translate(3,0);
								break;
							case SDLK_q:
								objects[0]->rotate(-2);
								objects[0]->translate(-3,0);
								break;

							case SDLK_r:
								objects[0]->rotate(1);
								printf("Pressed R, obj rotation value at %f \n \n", objects[0]->rotationValue);
								break;

							case SDLK_t:
								objects[0]->rotate(-1);
								printf("Pressed T, obj rotation value at %f \n \n", objects[0]->rotationValue);
								break;
								
							case SDLK_l:
								objects[0]->shear(0.25,0);
								printf("shear, %f \n", objects[0]->h);
								break;

							case SDLK_k:
								objects[0]->shear(-0.25,0);
								printf("shear, %f \n", objects[0]->h);
								break;
					
							case SDLK_1:
								printf("Viewing Woman \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(woman);
								break;

							case SDLK_2:
								printf("Viewing Isoceles Triangle \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(iso_triangle);
								break;

							case SDLK_3:
								printf("Viewing Equilateral Triangle \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(triangle);
								break;

							case SDLK_4:				
								printf("Viewing Square \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(square);
								break;
							
							case SDLK_5:
								printf("Viewing Pentagon \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(pentagon);
								break;

							case SDLK_6:
								printf("Viewing Hexagon \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(hexagon);
								break;

							case SDLK_7:
								printf("Viewing Heptagon \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(heptagon);
								break;

							case SDLK_8:
								printf("Viewing Octagon \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(octagon);
								break;

							case SDLK_9:
								printf("Viewing Nonagon \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(nonagon);
								break;

							case SDLK_0:
								printf("Viewing Decagon \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(decagon);
								break;

							case SDLK_p:
								printf("Viewing Priest \n");
								sphereView=false;
								objects.erase(objects.end()-1);
								objects.emplace_back(priest);
								break;

							case SDLK_o:
								printf("Viewing Sphere \n");
								sphereView=true;
								break;

							case SDLK_u:
								if(sphereView==true){
									printf("translating sphere up\n");
									spheres[0]->translate(0,0,1);
								}
								break;
							case SDLK_j:
								if(sphereView==true){
									printf("translating sphere down\n");
									spheres[0]->translate(0,0,-1);
									printf("sphere Zpos %f \n", spheres[0]->zPos);
								}
								break;

							case SDLK_i:
								printf("Saved Screenshot %04d \n", frameNum);
								char charBuffer[50];
								sprintf(charBuffer, "frames/screen_%07d.png", frameNum);		
								SDL_SaveBMP(baseSurface, charBuffer);
								break;
						}
						break;
				}
			}
	}
	close();
}

