#include "stdafx.h"
#include "DiamondSquareAlgorithm.h"

void DiamondSquareAlgorithm::SquareMethod(const Point point, const int step, const float randVal)
{
	/*
	if (step < 1) {
		return {}; //only needed for recursive version of DiamondSquare Algorithm
	}
	*/
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
		if (samplePoints[i].getX() + point.getX() < 0 //boundary
			|| samplePoints[i].getX() + point.getX() >= this->width
			|| samplePoints[i].getY() + point.getY() >= this->height
			|| samplePoints[i].getY() + point.getY() < 0) {
			continue;
		}
		sum += diamondSquareArr[samplePoints[i].getX() + point.getX()][samplePoints[i].getY() + point.getY()];
		count++;
	}
	diamondSquareArr[point.getX()][point.getY()] = sum / count + randVal;
	if (DEBUG) {
		printf("Square: (%d, %d) step: %d r-val: %.3f\n", point.getX(), point.getY(), step, randVal);
		displayDiamondSquareArray();
	}
	step_changes = (int)step_changes / 2;
	Point sampleDiamondPoints[4] = { //sample points of the surronding points
		Point(step_changes*(-1),step_changes*(-1)),
		Point(step_changes, step_changes*(-1)),
		Point(step_changes*(-1),step_changes),
		Point(step_changes,step_changes)
	};
	//set the next points for the diamond mthod
	for (int i = 0; i < 4; i++) { //using this while I figure out a better way
		diamondHolder.push_back(Point(sampleDiamondPoints[i].getX() + point.getX(), sampleDiamondPoints[i].getY() + point.getY()));
	}
}

void DiamondSquareAlgorithm::SquareMethod(const int x, const int y, const int step, const float randVal)
{
	/*
	if (step < 1) {
	return {}; //only needed for recursive version of DiamondSquare Algorithm
	}
	*/
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	float sum = 0;
	int step_changes = step;
	//could make it so that the main method can handle this but, hard to make it to a parallel process if sharing the same memory(for access and modification)
	Point samplePoints[4] = {
		Point(0,step_changes*(-1)),
		Point(0,step_changes),
		Point(step_changes*(-1),0),
		Point(step_changes,0)
	};
	int count = 1;//keep track if it took 3 points(aka, one is out of bound) or 4 (no points out of bound)
	for (int i = 0; i < 4; i++) {
		if (samplePoints[i].getX() + x < 0 //boundary
			|| samplePoints[i].getX() + x >= this->width
			|| samplePoints[i].getY() + y >= this->height
			|| samplePoints[i].getY() + y < 0) {
			continue;
		}
		sum += diamondSquareArr[samplePoints[i].getX() + x][samplePoints[i].getY() + y];
		count++;
	}
	diamondSquareArr[x][y] = sum / count + randVal;
	if (DEBUG) {
		printf("Square: (%d, %d) step: %d r-val: %.3f\n", x, y, step, randVal);
		//displayDiamondSquareArray();
	}
}

void DiamondSquareAlgorithm::DiamondMethod(const Point point, const int step, const float randVal)
{
	/*
		if the point is out of bound then return back to original function
	*/
	if (point.getX() < 0 || point.getX() >= width || point.getY() < 0 || point.getY() >= height) {
		return;
	}
	float sum = 0;
	int step_changes = (int)(step / 2);
	Point samplePoints[4] = { //sample points of the surronding points
		Point(step_changes*(-1),step_changes*(-1)),
		Point(step_changes, step_changes*(-1)),
		Point(step_changes*(-1),step_changes),
		Point(step_changes,step_changes)
	};
	int count = 0;
	//get all the surronding radius points given step_changes
	for (int i = 0; i < 4; i++) {
		if (samplePoints[i].getX() + point.getX() < 0
			|| samplePoints[i].getX() + point.getX() >= this->width
			|| samplePoints[i].getY() + point.getY() >= this->height
			|| samplePoints[i].getY() + point.getY() < 0) {
			continue;
		}
		sum += diamondSquareArr[point.getX() + samplePoints[i].getX()][point.getY() + samplePoints[i].getY()];
		count++;
	}
	if (diamondSquareArr[point.getX()][point.getY()] < _threshold) //check if the index is empty
		diamondSquareArr[point.getX()][point.getY()] = (sum / count + randVal);
	if (DEBUG) {
		printf("Diamond: (%d, %d) step: %d r-val: %.3f\n", point.getX(), point.getY(), step, randVal);
		displayDiamondSquareArray();
	}
	Point sampleSquarePoints[4] = {
		Point(0,step_changes*(-1)),
		Point(0,step_changes),
		Point(step_changes*(-1),0),
		Point(step_changes,0)
	};
	//call diamond with the point
	for (int i = 0; i < 4; i++) { //using this while I figure out a better way
		squareHolder.push_back(Point(sampleSquarePoints[i].getX() + point.getX(), sampleSquarePoints[i].getY() + point.getY()));
	}
}

void DiamondSquareAlgorithm::DiamondMethod(const int x, const int y, const int step, const float randVal)
{
	/*
	if the point is out of bound then return back to original function
	*/
	if (x < 0 || y >= width || x < 0 || y >= height) {
		return;
	}
	float sum = 0;
	int step_changes = step;
	Point samplePoints[4] = { //sample points of the surronding points
		Point(step_changes*(-1),step_changes*(-1)),
		Point(step_changes, step_changes*(-1)),
		Point(step_changes*(-1),step_changes),
		Point(step_changes,step_changes)
	};
	int count = 0;
	//get all the surronding radius points given step_changes
	for (int i = 0; i < 4; i++) { //boundaries
		if (samplePoints[i].getX() + x < 0
			|| samplePoints[i].getX() + x >= this->width
			|| samplePoints[i].getY() + y >= this->height
			|| samplePoints[i].getY() + y < 0) {
			continue;
		}
		sum += diamondSquareArr[x + samplePoints[i].getX()][y + samplePoints[i].getY()];
		count++;
	}
	if (diamondSquareArr[x][y] < _threshold) //check if the index is empty
		diamondSquareArr[x][y] = (sum / count) + randVal;
	if (DEBUG) {
		printf("Diamond: (%d, %d) step: %d r-val: %.3f\n", x, y, step, randVal);
		//displayDiamondSquareArray();
	}
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

float DiamondSquareAlgorithm::getRandVal(){
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)); /// this->arbitraryThreshold));
}

void DiamondSquareAlgorithm::generateCorners()
{
	srand(generationSeedValue);
	float corners[4];
	for (int i = 0; i < 4; i++) {
		 corners[i] = getRandVal();
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


