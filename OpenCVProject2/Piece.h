#include <opencv2\opencv.hpp>
#include "Edge.h"

using namespace cv;
using namespace std;

class Piece
{
	enum pieceType {Corner,Border,Interior};
	private:
		vector<Edge> edgeList;
		pieceType pType;
	public:
		Piece(vector<Edge> edgeList, pieceType pType);
		pieceType getPieceType();
		vector<Edge> getEdgeList();
};