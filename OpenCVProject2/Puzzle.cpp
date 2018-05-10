/**
CS354 Jigsaw Puzzle Problem Implementation
@class Puzzle.cpp
@purpose: Stores a Puzzle where piece nodes can be added, linked and retrieved based on type
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include "Puzzle.h"
// Constructor
Puzzle::Puzzle() 
{

}
// Add piece node to puzzle
void Puzzle::addPuzzleNode(PieceNode pN)
{
	pieceList.push_back(PieceNode(pN));
}
// Add pair between nodes to the puzzle
// Checks if pieceNode has reached max pairings
void Puzzle::addPair(PieceNode pN, PieceNode pN2)
{
	if (pN.isPairable() && pN2.isPairable())
	{
		pN.addPiecePair(pN2);
	}
}
// returns all piece nodes
vector<PieceNode> Puzzle::getPieceList()
{
	return pieceList;
}

// returns all piece nodes of a certain type
vector<PieceNode> Puzzle::getPieceNodes(Piece::pieceType pType)
{
	vector<PieceNode> pieces;
	for (PieceNode pN : Puzzle::getPieceList()) {
		Piece piece = pN.getPieceNodeData();
		if (piece.getPieceType() == pType) {
			pieces.push_back(pN);
		}
	}
	return pieces;
}