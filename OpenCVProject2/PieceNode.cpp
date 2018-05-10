/**
CS354 Jigsaw Puzzle Problem Implementation
@class PieceNode.cpp
@purpose: Stores a PieceNode which stores a piece object which can be linked to other nodes
	      A piece node has set number of pairs for the type of piece it stores
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include "PieceNode.h"

// Constructor Sets maximum pairs for piece type
PieceNode::PieceNode(Piece piece) : piece(piece)
{
	if (piece.getPieceType() == Piece::Corner) {
		maxPairs = 2;
	}
	else if (piece.getPieceType() == Piece::Border) 
	{
		maxPairs = 3;
	}
	else if (piece.getPieceType() == Piece::Interior)
	{
		maxPairs = 4;
	}
}

// returns piece object in node
Piece PieceNode::getPieceNodeData()
{
	return piece;
}

// adds pair to piece node
void PieceNode::addPiecePair(PieceNode pN)
{
	piecePairs.push_back(pN);
}

// Checks to see if piece is pairable 
// NOT FULLY IMPLEMENTED EDGEs WOULD HAVE TO BE CHECKED INDIVIDUALLY
bool PieceNode::isPairable()
{
	if (maxPairs >= piecePairs.size()) {
		return false;
	}
	else {
		return true;
	}
}