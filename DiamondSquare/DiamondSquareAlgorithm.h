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

	float _threshold = 0.05f; //used for non-whole number comparison
	/*
		For each mid point, set the outter edges of the square
		point = sum(adjacent points) + rand(seed)
	*/
	std::vector<Point> SquareMethod(Point, int, float);
	/*
		generate a mid point from the corners of the square
		midPoint = sum(corners) + rand(seed)
	*/
	std::vector<Point> DiamondMethod(Point, int, float);



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
		int step = width - 1;
		std::vector<Point> diamondHolder;
		std::vector<Point> squareHolder;
		float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
		DEBUG = true;

		diamondHolder.push_back(startingMidPoint);
		int totalDiamond = 0;
		int totalSquare = 0;
		while (step > 1) {
			//displayDiamondSquareArray();
			//float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
			
			while (!diamondHolder.empty()) {
				squareHolder  = squareHolder + DiamondMethod(diamondHolder.back(), step, getRandVal());
				diamondHolder.pop_back();//erase this point 
				totalDiamond++;
			}
			while (!squareHolder.empty()) {
				diamondHolder = diamondHolder + SquareMethod(squareHolder.back(), step, getRandVal());
				squareHolder.pop_back();
				totalSquare++;
			}
			step = (int)(step / 2);
			/*
			displayDiamondSquareArray();
			SquareMethod(Point(0, 2), step, r);
			SquareMethod(Point(2, 0), step, r);
			SquareMethod(Point(4, 2), step, r);
			SquareMethod(Point(2, 4), step, r);
			displayDiamondSquareArray();
			//r = 10.0f;
			//DiamondMethod(Point((int)(width / 2), (int)(height / 2)), step, r);
			//from point (2,2)
			DiamondMethod(Point(1, 1), step / 2, r); //(x-1,y-1)
			DiamondMethod(Point(1, 3), step / 2, r); //(x,y+1)
			DiamondMethod(Point(3, 1), step / 2, r); //(x+1,y)
			DiamondMethod(Point(3, 3), step / 2, r); //(x+1,y+1)
			displayDiamondSquareArray();
			//for point (1,1)
			SquareMethod(Point(1, 0), step / 2, r);
			SquareMethod(Point(0, 1), step / 2, r);
			SquareMethod(Point(1, 2), step / 2, r);
			SquareMethod(Point(2, 1), step / 2, r);
			displayDiamondSquareArray();
			//for point (1,3)
			SquareMethod(Point(1, 2), step / 2, r);
			SquareMethod(Point(0, 3), step / 2, r);
			SquareMethod(Point(1, 4), step / 2, r);
			SquareMethod(Point(2, 3), step / 2, r);
			displayDiamondSquareArray();
			//for point (3,1)
			SquareMethod(Point(3, 0), step / 2, r); //(x,y-1)
			SquareMethod(Point(2, 1), step / 2, r); //(x-1, y)
			SquareMethod(Point(3, 2), step / 2, r); //(x,y+1)
			SquareMethod(Point(4, 1), step / 2, r); //(x+1,y)
			displayDiamondSquareArray();
			//for point (3,3)

			SquareMethod(Point(3, 2), step / 2, r); //(x,y-1)
			SquareMethod(Point(2, 3), step / 2, r); //(x-1, y)
			SquareMethod(Point(3, 4), step / 2, r); //(x,y+1)
			SquareMethod(Point(4, 3), step / 2, r); //(x+1,y)
			//displayDiamondSquareArray();
			*/
			printf("Total diamond %i\nTotal square %i\n", totalDiamond, totalSquare);
		}
	}
	

	/*
		Purpose: To display the array for debugging purposes
	*/
	void displayDiamondSquareArray();


};

#endif // !__DIAMONDSQUAREALGORITHM_H_
