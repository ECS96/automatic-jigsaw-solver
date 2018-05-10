/**
CS354 Jigsaw Puzzle Problem Implementation
@class Puzzle.h
@purpose: Stores a Puzzle where piece nodes can be added, linked and retrieved based on type
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include "Piece.h"
#include "PieceNode.h"

using namespace std;
using namespace cv;

#ifndef Puzzle_HEADER
#define Puzzle_HEADER
class Puzzle
{	
	private:
		vector<PieceNode> pieceList;
	public:
		Puzzle();
		void addPuzzleNode(PieceNode pN);
		void addPair(PieceNode pN, PieceNode pN2);
		vector<PieceNode> getPieceList();
		vector<PieceNode> getPieceNodes(Piece::pieceType p);
};

#endif