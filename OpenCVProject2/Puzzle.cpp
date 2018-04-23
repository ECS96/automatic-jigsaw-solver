#include "Puzzle.h"
#include "PieceNode.h"

Puzzle::Puzzle() 
{

}

void Puzzle::addPuzzleNode(Piece piece)
{
	pieceList.push_back(PieceNode(piece));
}

void Puzzle::addPair(PieceNode pN, PieceNode pN2)
{
	if (pN.isPairable() && pN2.isPairable())
	{
		pN.addPiecePair(pN2);
	}
}

vector<PieceNode> Puzzle::getPieceList()
{
	return pieceList;
}