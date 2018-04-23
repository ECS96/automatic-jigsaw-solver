#ifndef PieceNode_HEADER
#define PieceNode_HEADER

#include "Piece.h"

using namespace std;

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