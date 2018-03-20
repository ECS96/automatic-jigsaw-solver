#include <iostream>
#include <opencv2/opencv.hpp>
#include "Edge.h"


using namespace std;
using namespace cv;

Edge::Edge(vector<Point> eC, edgeType t): edgeCoords(eC), eType(t)
{
}

Edge::edgeType Edge::getType()
{
	return edgeType();
}

vector<Point> Edge::getEdgeCoords()
{
	return vector<Point>();
}
