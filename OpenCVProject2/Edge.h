#ifndef Edge_HEADER
#define Edge_HEADER

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Edge Class to store the coordinate Points of the edge and the type of edge
*/
class Edge
{
	private:
		vector<Point> edgeCoords;
	public:
		enum edgeType { straight, convex, concave };
		edgeType eType;
		Edge(vector<Point> edgeCoords, edgeType type);
		edgeType getType();
		vector<Point> getEdgeCoords();

};

#endif