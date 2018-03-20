#include <opencv2/opencv.hpp>
#include <iostream>
#include "Piece.h"

using namespace cv;
using namespace std;

Piece::Piece(vector<Edge> edgeList, pieceType pType) : edgeList(edgeList), pType(pType)
{

}

Piece::pieceType Piece::getPieceType()
{
	return pieceType();
}

vector<Edge> Piece::getEdgeList()
{
	return vector<Edge>();
}