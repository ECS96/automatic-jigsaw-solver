#include "PieceNode.h"
#include "Puzzle.h"

using namespace std;
/*
tuple<Edge, Edge, int> score;
vector<tuple<Edge,Edge,int>> scores;

vector<pair<Edge, Edge>, int> getMatchScores(Puzzle puzzle)
{


	vector<PieceNode> corners;
	vector<PieceNode> borders;
	vector<PieceNode> interiors;

	for (PieceNode p : puzzle.getPieceList())
	{
		Piece piece = p.getPieceNodeData();
		if (piece.getPieceType == Piece::Corner)
		{
			corners.push_back(p);
		}
		else if (piece.getPieceType == Piece::Border)
		{
			borders.push_back(p);
		}
		else if (piece.getPieceType == Piece::Interior)
		{
			interiors.push_back(p);
		}
	}
	
	//Store each set of coords for each piece in the puzzle
}

void computeCornerToBorder(vector<PieceNode> corners, vector<PieceNode> borders) {
	int edgeIndexAbove, edgeIndexBelow;
	for (PieceNode corner : corners)
	{
		Piece l = corner.getPieceNodeData();
		vector<Edge> lEdgeList = l.getEdgeList();
		for (int i = 0; i < lEdgeList.size(); i++) {
			Edge e = lEdgeList.at(i);
			edgeIndexAbove = i - 1;
			edgeIndexBelow = i + 1;
			if (edgeIndexAbove < 0) {
				edgeIndexAbove = lEdgeList.size();
			}
			if (edgeIndexBelow > lEdgeList.size()) {
				edgeIndexBelow = 0;
			}
			if (e.getType() == Edge::concave && lEdgeList.at(edgeIndexAbove).getType() == Edge::straight)
			{
				for (PieceNode border : borders) {
						Piece r = border.getPieceNodeData();
						vector<Edge> rEdgeList = r.getEdgeList();
						for (int j = 0; i < rEdgeList.size(); j++) {
							Edge eComp = rEdgeList.at(j);
							edgeIndexAbove = j + 1;
							if (edgeIndexAbove > rEdgeList.size()) {
								edgeIndexAbove = 0;
							}
							if (eComp.getType() == Edge::convex && rEdgeList.at(edgeIndexAbove).getType() == Edge::straight) {
								compareEdge(e.getEdgeCoords, eComp.getEdgeCoords);
							}

						}
				}	
			}
			else if (e.getType() == Edge::concave && lEdgeList.at(edgeIndexBelow).getType() == Edge::straight)
			{

			}
		}
	}
}

int compareEdge(Edge edge, Edge edge2) {
	scores.push_back(make_tuple(edge,edge2,1));
}
*/