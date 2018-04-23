#include "Piece.h"
#include "Edge.h"

using namespace cv;
using namespace std;

int calcEdgeType(vector<Point>);

Edge::edgeType getEdgeType(vector<Point> edgeCoords)
{
	int edge = calcEdgeType(edgeCoords);
	if (edge == 1) {
		return Edge::straight;
	}
	if (edge == 2) {
		return Edge::concave;
	}
	if (edge == 3) {
		return Edge::convex;
	}
}


int calcEdgeType(vector<Point> edgeCoords)
{
	// Use Displacement of X and Y Coordinates to determine Edge Type
	return 1;
}

Piece::pieceType getPieceType(vector<Edge> edgeList)
{
	int edgeNum = 0;
	for (Edge e : edgeList)
	{
		if (e.eType == Edge::straight)
		{
			edgeNum++;
		}
	}

	if (edgeNum > 1) {
		return Piece::Corner;
	}
	else if (edgeNum > 0) {
		return Piece::Border;
	}
	else {
		return Piece::Interior;
	}
}
