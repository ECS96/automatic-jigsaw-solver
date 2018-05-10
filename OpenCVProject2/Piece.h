/**
CS354 Jigsaw Puzzle Problem Implementation
@class Piece.h
@purpose: Stores a Piece object with list of edge objects, piece type corner, border, interior and pieceID
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/

#include <opencv2\opencv.hpp>
#include <iostream>
#include "Edge.h"

using namespace cv;
using namespace std;

#ifndef Piece_HEADER
#define Piece_HEADER

class Piece
{
	public:
		enum pieceType {Corner,Border,Interior};
		Piece(vector<Edge> edgeList, pieceType pType, int pieceID);
		pieceType getPieceType();
		vector<Edge> getEdgeList();
		int getPieceID();
	private:
		vector<Edge> edgeList;
		pieceType pType;
		int pieceID;
};

#endif