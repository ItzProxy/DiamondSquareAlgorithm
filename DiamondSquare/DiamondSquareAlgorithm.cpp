#include "stdafx.h"
#include "DiamondSquareAlgorithm.h"


void DiamondSquareAlgorithm::SquareMethod(int step, float randVal)
{
	//printf("(%d, %d) step: %d r-val: %.3f\n", point->getX(), point->getY(), step, randVal);
	diamondSquareArr[0][2] = (diamondSquareArr[2][2] + diamondSquareArr[0][0] + diamondSquareArr[0][4]) /3 + randVal;
	diamondSquareArr[2][0] = (diamondSquareArr[2][2] + diamondSquareArr[0][0] + diamondSquareArr[4][0]) / 3 + randVal;
	diamondSquareArr[4][2] = (diamondSquareArr[2][2] + diamondSquareArr[4][0] + diamondSquareArr[4][4]) / 3 + randVal;
	diamondSquareArr[2][4] = (diamondSquareArr[2][2] + diamondSquareArr[4][4] + diamondSquareArr[0][4]) / 3 + randVal;
}
void DiamondSquareAlgorithm::SquareMethod(Point point, int step, float randVal) 
{
	if (step < 1) {
		return; //only needed for recursive version of DiamondSquare Algorithm
	}
	printf("Square: (%d, %d) step: %d r-val: %.3f\n", point.getX(), point.getY(), step, randVal);
	float sum = 0;
	int step_changes = (int)(step / 2);
	//could make it so that the main method can handle this but, hard to make it to a parallel process if sharing the same memory(for access and modification)
	Point samplePoints[4] = {
		Point(0,step_changes*(-1)),
		Point(0,step_changes),
		Point(step_changes*(-1),0),
		Point(step_changes,0)
	};
	int count = 0;//keep track if it took 3 points(aka, one is out of bound) or 4 (no points out of bound)
	for (int i = 0; i < 4; i++) {
		if (samplePoints[i].getX() + point.getX() < 0
			|| samplePoints[i].getX() + point.getX() >= this->width
			|| samplePoints[i].getY() + point.getY() >= this->height
			|| samplePoints[i].getY() + point.getY() < 0) {
			continue;
		}
		sum += diamondSquareArr[samplePoints[i].getX() + point.getX()][samplePoints[i].getY() + point.getY()];
		count++;
	}
	diamondSquareArr[point.getX()][point.getY()] = sum / count + randVal;
	
}

void DiamondSquareAlgorithm::DiamondMethod(Point point, int step, float randVal)
{
	if (step < 1) {
		return; //only needed for recursive version of DiamondSquare Algorithm
	}
	printf("Diamond: (%d, %d) step: %d r-val: %.3f\n", point.getX(), point.getY(), step, randVal);
	float sum = 0;
	int step_changes = (int)(step / 2);
	Point samplePoints[4] = {
		Point(step_changes*(-1),step_changes*(-1)),
		Point(step_changes, step_changes*(-1)),
		Point(step_changes*(-1),step_changes), 
		Point(step_changes,step_changes) 
	};
	for (int i = 0; i < 4; i++) {
		sum += diamondSquareArr[point.getX() + samplePoints[i].getX()][point.getY() - samplePoints[i].getY()];
	}
	if(diamondSquareArr[point.getX()][point.getY()] < 1)
		diamondSquareArr[point.getX()][point.getY()] = (sum/4.0f + randVal);
}

void DiamondSquareAlgorithm::DiamondMethod(PointValue* point, int step, float randVal)
{
	printf("(%d, %d) step: %d r-val: %.3f\n", point->getX(), point->getY(), step, randVal);
	float sum = 0;
	sum += diamondSquareArr[point->getX()- 2][point->getY()-2];
	sum += diamondSquareArr[point->getX() + 2][point->getY() - 2];
	sum += diamondSquareArr[point->getX() - 2][point->getY() + 2];
	sum += diamondSquareArr[point->getX() + 2][point->getY() + 2];
	sum /= 4;
	sum += randVal;
	diamondSquareArr[point->getX()][point->getY()] = sum;
}


//constructor
DiamondSquareAlgorithm::DiamondSquareAlgorithm(int _n) {
	height = _n;
	width = height;
	if (width*height % 2 == 0) {
		throw DiamondSquareArraySizeException();
	}
	//create 2D array
	diamondSquareArr = new float*[height];
	for (int i = 0; i < height; i++) //create an array of an array with given height and width
		diamondSquareArr[i] = new float[width];

	//intialize each point to 0.0f
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			diamondSquareArr[i][j] = 0.0f;
		}
	}
	cornerSet = false;
}
//destructor
DiamondSquareAlgorithm::~DiamondSquareAlgorithm() {
	for (int i = 0; i < height; i++)
		delete(diamondSquareArr[i]); //delete each allocated array of the array space
	delete(diamondSquareArr);
}

void DiamondSquareAlgorithm::setSeed()
{
	//just set to computer hardware clock
	generationSeedValue = time(0);
	//call to reset seed to a different time seed
}

void DiamondSquareAlgorithm::setSeed(unsigned int _seed)
{
	//used to generate same values each set for remainder of simulation
	generationSeedValue = _seed;
}

void DiamondSquareAlgorithm::generateCorners()
{
	srand(generationSeedValue);
	float corners[4];
	for (int i = 0; i < 4; i++) {
		 corners[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / this->arbitraryThreshold));
	}
	generateCorners(corners);
}

void DiamondSquareAlgorithm::generateCorners(float cornerValue[])
{
	std::vector<PointValue> corners{
		PointValue(0, 0, cornerValue[0]),
		PointValue(width - 1, 0, cornerValue[1]),
		PointValue(0, height - 1, cornerValue[2]),
		PointValue(width - 1, height - 1, cornerValue[3])
	};

	for (auto i : corners) {
		diamondSquareArr[i.getX()][i.getY()] = i.getValue();
	}
	
}

void DiamondSquareAlgorithm::displayDiamondSquareArray()
{
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			printf("%.2f \t", diamondSquareArr[i][j]); //print column
		}
		printf("\n"); //next row
	}
}


