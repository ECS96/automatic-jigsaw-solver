#include <iostream>
#include <opencv2/opencv.hpp>
#include "Edge.h"


using namespace std;
using namespace cv;

/*
	Stores the coordinates of each edge and the type of edge stored
*/

Edge::Edge(vector<Point> eC, edgeType t): edgeCoords(eC), eType(t)
{
}

Edge::edgeType Edge::getType()
{
	return eType;
}

vector<Point> Edge::getEdgeCoords()
{
	return edgeCoords;
}
