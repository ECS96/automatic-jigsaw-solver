/**
CS354 Jigsaw Puzzle Problem Implementation
@class PieceNode.h
@purpose: Stores a PieceNode which stores a piece object which can be linked to other nodes
		  A piece node has set number of pairs for the type of piece it stores
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include "Piece.h"

using namespace std;

#ifndef PieceNode_HEADER
#define PieceNode_HEADER

class PieceNode
{
private:
	Piece::pieceType pType;
	Piece piece;
	vector<PieceNode> piecePairs;
	int maxPairs;
public:
	PieceNode(Piece piece);
	Piece getPieceNodeData();
	void addPiecePair(PieceNode pN);
	bool isPairable();
};

#endif