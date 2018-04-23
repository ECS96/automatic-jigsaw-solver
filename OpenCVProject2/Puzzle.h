#ifndef Puzzle_HEADER
#define Puzzle_HEADER


#include "Piece.h"
#include "PieceNode.h"

using namespace std;
using namespace cv;

class Puzzle
{	
	private:
		vector<PieceNode> pieceList;
	public:
		Puzzle();
		void addPuzzleNode(Piece piece);
		void addPair(PieceNode pN, PieceNode pN2);
		vector<PieceNode> getPieceList();
};

#endif