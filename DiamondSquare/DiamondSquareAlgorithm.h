#pragma once
#ifndef __DIAMONDSQUAREALGORITHM_H_
#define __DIAMONDSQUAREALGORITHM_H_

#include "stdafx.h"
#include <time.h>
#include <random>
#include <map>
#include <queue> 
#include <math.h>
#include <exception>

#include "VectorOverload.h"
#include "PointValue.h"
#include "CustomException.h"

class DiamondSquareAlgorithm {
private:

	float** diamondSquareArr;
	int height;
	int width;
	time_t generationSeedValue = time(NULL);
	bool cornerSet;
	float arbitraryThreshold = 100.0f;
	bool DEBUG = false;
	std::vector<Point> diamondHolder;
	std::vector<Point> squareHolder;

	float _threshold = 0.005f; //used for non-whole number comparison
	/*
		For each mid point, set the outter edges of the square
		point = sum(adjacent points) + rand(seed)
	*/
	void SquareMethod(const Point, const int, const float);
	void SquareMethod(const int, const int, const int, const float);
	/*
		generate a mid point from the corners of the square
		midPoint = sum(corners) + rand(seed)
	*/
	void DiamondMethod(const Point, const int, const float);
	void DiamondMethod(const int, const int, const int, const float);



public:
	//constructor

	DiamondSquareAlgorithm() : DiamondSquareAlgorithm(5) {} //delegation constructors c++11 and newer
	DiamondSquareAlgorithm(int);

	//deconstructor
	~DiamondSquareAlgorithm();

	//getters
	int getHeight() const {
		return this->height;
	}
	int getWidth() const {
		return this->width;
	}
	int getSize() const {
		return this->height*this->width;
	}
	float** getHeightMap() {
		return diamondSquareArr;
	}

	//setters
	/*
		Purpose to set the generation seed
		either getting hardware clock via call to os
		or manual input, only used for generating corners
	*/
	void setSeed();
	void setSeed(unsigned int);
	float getRandVal();

	//probably shouldn't do as it won't be as useful

	//method helpers
	/*
		Name: Generate Constructor
		Purpose: To generate the four corners of the height map

		Other information:
			corners are considered the [0,0] [0,n] [n,0] [n,n]
			these are set to a random value to start, depending on the seed this will either auto generate a height map that is consistant or psudorandom
	*/
	void generateCorners();
	/*
		For testing/debugging purposes
	*/
	void generateCorners(float[]);

	//main method
	void diamondSquare() {
		generateCorners();
		Point startingMidPoint = Point((int)width / 2, (int)height / 2);
		srand(time(0));


		//float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
		DEBUG = true;
		//does one quadrant at a time?
		for (int p = 0; p < 2; p++) {
			int step = width - 1;
			while (step > 1) {
				//diamond method calling
				for (int i = (int)step / 2; i < step; i += (int)(step / 2)) {
					for (int j = (int)step / 2; j < step; j += (int)(step / 2)) {
						Point offset[4] = {
							Point(0,0), //quadrant 1 (top left) no changes 
							Point(0,(int)(step)), //quadrant 3 (bottom left)
							Point((int)(step),0),//top right
							Point((int)(step),(int)(step)) //bottom right
						};
						for (int p = 0; p < 4; p++) {
							int a = i + offset[p].getX();
							int b = j + offset[p].getY();
							if (a >= width || b >= height) {
								continue; //don't want to continue past this point because the point is invalid and 
							}
							DiamondMethod(a, b, step, getRandVal());
							float yep = getRandVal();
							SquareMethod(a + (int)step / 2, b, step, yep);

							SquareMethod(a, b + (int)step / 2, step, yep);

							SquareMethod(a - (int)step / 2, b, step, yep);

							SquareMethod(a, b - (int)step / 2, step, yep);
						}
					}
				}
				step = (int)(step / 2);
			}
		}
		/*
		for (int i = 0; i < width; i += (int)(step / 2)) {
			for (int j = 0; j < height; j += (int)(step / 2)) {
				SquareMethod(i, j, step, getRandVal());
			}
		}
		*/
	}

	/*
	while (step > 1) {
		//displayDiamondSquareArray();
		//float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
		int totalDiamond = 0;
		int totalSquare = 0;
		for(int i = 0; i < step; i+= (int)step/2)

		while (!diamondHolder.empty()) {
			DiamondMethod(diamondHolder.back(), step, getRandVal());
			diamondHolder.pop_back();//erase this point
			totalDiamond++;
		}
		while (!squareHolder.empty()) {
			SquareMethod(squareHolder.back(), step, getRandVal());
			squareHolder.pop_back();
			totalSquare++;
		}
		printf("Total diamond %i\nTotal square %i\n step: %i\n", totalDiamond, totalSquare,step);
		step = (int)(step / 2);

	}
	*/

	/*
		Purpose: To display the array for debugging purposes
	*/
	void displayDiamondSquareArray();


};

#endif // !__DIAMONDSQUAREALGORITHM_H_
