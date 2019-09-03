//functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL.h>
#include <vector>
using std::vector;
using std::pair;

extern const int WIDTH;
extern const int HEIGHT;

extern SDL_Window* win;
extern SDL_Surface* baseSurface;


void init();
void close();
void updateScreen();

void setPix(int x, int y, int r, int g, int b);

vector<double> addMats1D(vector<double> m1, vector<double> m2);
vector<double> subtractMats1D(vector<double> m1, vector<double> m2);
vector<double> applyMatScalar(double scalar, vector<double> mat);
vector<double> multMatbyVec(vector<vector<double> > mat, vector<double> vec);
vector<vector<double>> multMatbyMat(vector<vector<double> > mat1, vector<vector<double> > mat2);

double degreesToRadians(double deg);
bool sortByDist(pair<int, double> one, pair<int, double> two);


#endif