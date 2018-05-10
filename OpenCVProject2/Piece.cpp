/**
CS354 Jigsaw Puzzle Problem Implementation
@class Piece.cpp
@purpose: Stores a Piece object with list of edge objects, piece type corner, border, interior and piece ID
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/

#include "Piece.h"

// Constructor
Piece::Piece(vector<Edge> edgeList, pieceType pType, int pieceID) : edgeList(edgeList), pType(pType), pieceID(pieceID)
{

}
// Accessor for Piece
Piece::pieceType Piece::getPieceType()
{
	return pType;
}
// Accessor for Edge List
vector<Edge> Piece::getEdgeList()
{
	return edgeList;
}
// Accessor for Piece ID
int Piece::getPieceID()
{
	return pieceID;
}