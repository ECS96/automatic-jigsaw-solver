#include "PieceNode.h"

using namespace cv;

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

Piece PieceNode::getPieceNodeData()
{
	return piece;
}

void PieceNode::addPiecePair(PieceNode pN)
{
	piecePairs.push_back(pN);
}

bool PieceNode::isPairable()
{
	if (maxPairs >= piecePairs.size()) {
		return false;
	}
	else {
		return true;
	}
}