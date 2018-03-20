#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Edge
{
	enum edgeType {straight,convex,concave};
	private:
		vector<Point> edgeCoords;
		edgeType eType;
	public:
		Edge(vector<Point> edgeCoords, edgeType type);
		edgeType getType();
		vector<Point> getEdgeCoords();

};