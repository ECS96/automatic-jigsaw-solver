#ifndef Piece_HEADER
#define Piece_HEADER


#include <opencv2\opencv.hpp>
#include "Edge.h"

using namespace cv;
using namespace std;

class Piece
{
	public:
		enum pieceType {Corner,Border,Interior};
		Piece(vector<Edge> edgeList, pieceType pType);
		pieceType getPieceType();
		vector<Edge> getEdgeList();
	private:
		vector<Edge> edgeList;
		pieceType pType;
};

#endif