/**
CS354 Jigsaw Puzzle Problem Implementation
@class matching.cpp
@purpose Perform matching on piece edges and store a score with the edge pairing
		 Compare edges and compute displacement score
		 Print and calculate best score for each edge to file
		 Print all scores to file
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include "Matching.h"

// Only compares corner to border pairs where the border is aligned and either concave to convex or convex to concave
// Fully commented first possibility the rest of code is repeated for the 3 other possiblities
vector<tuple<int,int,int,int,int>> computeCornerToBorder(vector<PieceNode> corners, vector<PieceNode> borders, vector<tuple<int, int, int, int, int>> scores) {
	// int to stores indexes below and above edge 
	int edgeIndexAbove, edgeIndexBelow;
	// Loops through all corners
	for (PieceNode cornerNode : corners)
	{
		// Store corner piece
		Piece cornerPiece = cornerNode.getPieceNodeData();

		// Stores corner edges
		vector<Edge> cornerEdges = cornerPiece.getEdgeList();

		// Loops through all edges
		for (int i = 0; i < cornerEdges.size(); i++) {

			// Stores corner edge
			Edge cornerEdge = cornerEdges.at(i);

			// calculates edge above and below
			edgeIndexAbove = i + 1;
			edgeIndexBelow = i - 1;

			// Ensures index does not go out of bounds in edge list
			if (edgeIndexAbove > cornerEdges.size()-1) {
				edgeIndexAbove = 0;
			}
			if (edgeIndexBelow < 0) {
				edgeIndexBelow = cornerEdges.size()-1;
			}

			// Checks edge type concave and if the border aligment is above or below
			if (cornerEdge.getType() == Edge::concave && cornerEdges.at(edgeIndexAbove).getType() == Edge::straight)
			{
				// Loops through all border pieces
				for (PieceNode borderNode : borders) {
					//Stores piece
					Piece borderPiece = borderNode.getPieceNodeData();
					//Stores edgelist
					vector<Edge> borderEdges = borderPiece.getEdgeList();
					//Loops through edges
					for (int j = 0; j < borderEdges.size(); j++) {
						// Stores edge
						Edge borderEdge = borderEdges.at(j);

						// calculates index of edge above
						edgeIndexAbove = j - 1;

						//out of bounds check
						if (edgeIndexAbove < 0) {
							edgeIndexAbove = borderEdges.size()-1;
						}
						// Checks edge type is convex and border aligned above
						if (borderEdge.getType() == Edge::convex && borderEdges.at(edgeIndexAbove).getType() == Edge::straight) {
							// Computes score on the two edges
							int score = compareEdge(cornerEdge.getEdgeCoords(), borderEdge.getEdgeCoords());
							// Adds score to scores
							scores.push_back(make_tuple(cornerPiece.getPieceID(),i,borderPiece.getPieceID(),j,score));
						}

					}
				}
			}
			else if (cornerEdge.getType() == Edge::concave && cornerEdges.at(edgeIndexBelow).getType() == Edge::straight)
			{	
				for (PieceNode borderNode : borders) {
					Piece borderPiece = borderNode.getPieceNodeData();
					vector<Edge> borderEdges = borderPiece.getEdgeList();
					for (int j = 0; j < borderEdges.size(); j++) {
						Edge borderEdge = borderEdges.at(j);
						edgeIndexBelow = j + 1;
						if (edgeIndexBelow > borderEdges.size()-1) {
							edgeIndexBelow = 0;
						}
						// Checks if edge is convex and border aligned below
						if (borderEdge.getType() == Edge::convex && borderEdges.at(edgeIndexBelow).getType() == Edge::straight) {
							int score = compareEdge(cornerEdge.getEdgeCoords(), borderEdge.getEdgeCoords());
							scores.push_back(make_tuple(cornerPiece.getPieceID(), i, borderPiece.getPieceID(), j, score));
						}

					}
				}
			}
			// Checks edge type convex and if the border aligment is above or below
			if (cornerEdge.getType() == Edge::convex && cornerEdges.at(edgeIndexAbove).getType() == Edge::straight)
			{
				for (PieceNode borderNode : borders) {
					Piece borderPiece = borderNode.getPieceNodeData();
					vector<Edge> borderEdges = borderPiece.getEdgeList();
					for (int j = 0; j < borderEdges.size(); j++) {
						Edge borderEdge = borderEdges.at(j);
						edgeIndexAbove = j - 1;
						if (edgeIndexAbove < 0) {
							edgeIndexAbove = borderEdges.size() - 1;
						}
						// Checks if edge is concave and border aligned above
						if (borderEdge.getType() == Edge::concave && borderEdges.at(edgeIndexAbove).getType() == Edge::straight) {
							int score = compareEdge(cornerEdge.getEdgeCoords(), borderEdge.getEdgeCoords());
							scores.push_back(make_tuple(cornerPiece.getPieceID(), i, borderPiece.getPieceID(), j, score));
						}

					}
				}
			}
			else if (cornerEdge.getType() == Edge::convex && cornerEdges.at(edgeIndexBelow).getType() == Edge::straight)
			{
				for (PieceNode borderNode : borders) {
					Piece borderPiece = borderNode.getPieceNodeData();
					vector<Edge> borderEdges = borderPiece.getEdgeList();
					for (int j = 0; j < borderEdges.size(); j++) {
						Edge borderEdge = borderEdges.at(j);
						edgeIndexBelow = j + 1;
						if (edgeIndexBelow > borderEdges.size() - 1) {
							edgeIndexBelow = 0;
						}
						// Checks if edge is concave and border aligned below
						if (borderEdge.getType() == Edge::concave && borderEdges.at(edgeIndexBelow).getType() == Edge::straight) {
							int score = compareEdge(cornerEdge.getEdgeCoords(), borderEdge.getEdgeCoords());
							scores.push_back(make_tuple(cornerPiece.getPieceID(), i, borderPiece.getPieceID(), j, score));
						}

					}
				}
			}
		}
	}
	// returns score tables
	return scores;
}

// Only compares border to border pairs where the border is aligned and either concave to convex or convex to concave
// Fully commented first possibility the rest of code is repeated for the 3 other possiblities
vector<tuple<int, int, int, int, int>> computeBorderToBorder(vector<PieceNode> borders, vector<tuple<int, int, int, int, int>> scores) {
	int edgeIndexAbove, edgeIndexBelow;
	for (PieceNode leftBorderNode : borders)
	{	
		// Stores border piece
		Piece leftBorderPiece = leftBorderNode.getPieceNodeData();

		// Stores edge list
		vector<Edge> leftBorderEdges = leftBorderPiece.getEdgeList();
		for (int i = 0; i < leftBorderEdges.size(); i++) {
			// Stores edge
			Edge leftBorderEdge = leftBorderEdges.at(i);
			// calculates indexes of edge below and above
			edgeIndexAbove = i + 1;
			edgeIndexBelow = i - 1;

			//out of bounds check
			if (edgeIndexAbove > leftBorderEdges.size() - 1) {
				edgeIndexAbove = 0;
			}
			if (edgeIndexBelow < 0) {
				edgeIndexBelow = leftBorderEdges.size() - 1;
			}
			// Checks for concave edge type and border alignment above
			if (leftBorderEdge.getType() == Edge::concave && leftBorderEdges.at(edgeIndexAbove).getType() == Edge::straight)
			{
				// Loops over border pieces
				for (PieceNode rightBorderNode : borders) {

					//Store border piece
					Piece rightBorderPiece = rightBorderNode.getPieceNodeData();

					//Store edgelist
					vector<Edge> rightBorderEdges = rightBorderPiece.getEdgeList();
					
					//Loops over edges
					for (int j = 0; j < rightBorderEdges.size(); j++) {
						//Stored edge
						Edge rightBorderEdge = rightBorderEdges.at(j);
						// calculates index above
						edgeIndexAbove = j - 1;
						// out of bounds check
						if (edgeIndexAbove < 0) {
							edgeIndexAbove = rightBorderEdges.size() - 1;
						}
						// Checks for concave edge and border alignment below and border pieces are not the same id
						if (rightBorderEdge.getType() == Edge::convex && rightBorderEdges.at(edgeIndexAbove).getType() == Edge::straight && leftBorderPiece.getPieceID() != rightBorderPiece.getPieceID()) {
							// Computes score between edges
							int score = compareEdge(leftBorderEdge.getEdgeCoords(), rightBorderEdge.getEdgeCoords());
							// adds score to score table
							scores.push_back(make_tuple(leftBorderPiece.getPieceID(), i, rightBorderPiece.getPieceID(), j, score));
						}

					}
				}
			} // Checks for concave and border aligned below
			else if (leftBorderEdge.getType() == Edge::concave && leftBorderEdges.at(edgeIndexBelow).getType() == Edge::straight)
			{
				for (PieceNode rightBorderNode : borders) {
					Piece rightBorderPiece = rightBorderNode.getPieceNodeData();
					vector<Edge> rightBorderEdges = rightBorderPiece.getEdgeList();
					for (int j = 0; j < rightBorderEdges.size(); j++) {
						Edge rightBorderEdge = rightBorderEdges.at(j);
						edgeIndexBelow = j + 1;
						if (edgeIndexBelow > rightBorderEdges.size()-1) {
							edgeIndexBelow = 0;
						}
						// Checks for convex border align below and border piece not identical
						if (rightBorderEdge.getType() == Edge::convex && rightBorderEdges.at(edgeIndexBelow).getType() == Edge::straight && leftBorderPiece.getPieceID() != rightBorderPiece.getPieceID()) {
							int score = compareEdge(leftBorderEdge.getEdgeCoords(), rightBorderEdge.getEdgeCoords());
							scores.push_back(make_tuple(leftBorderPiece.getPieceID(), i, rightBorderPiece.getPieceID(), j, score));
						}

					}
				}
			}
			// Checks if edge is convex and border aligned above
			if (leftBorderEdge.getType() == Edge::convex && leftBorderEdges.at(edgeIndexAbove).getType() == Edge::straight)
			{
				for (PieceNode rightBorderNode : borders) {
					Piece rightBorderPiece = rightBorderNode.getPieceNodeData();
					vector<Edge> rightBorderEdges = rightBorderPiece.getEdgeList();
					for (int j = 0; j < rightBorderEdges.size(); j++) {
						Edge rightBorderEdge = rightBorderEdges.at(j);
						edgeIndexAbove = j - 1;
						if (edgeIndexAbove < 0) {
							edgeIndexAbove = rightBorderEdges.size() - 1;
						}
						// Checks for concave border align above and border piece not identical
						if (rightBorderEdge.getType() == Edge::concave && rightBorderEdges.at(edgeIndexAbove).getType() == Edge::straight && leftBorderPiece.getPieceID() != rightBorderPiece.getPieceID()) {
							int score = compareEdge(leftBorderEdge.getEdgeCoords(), rightBorderEdge.getEdgeCoords());
							scores.push_back(make_tuple(leftBorderPiece.getPieceID(), i, rightBorderPiece.getPieceID(), j, score));
						}

					}
				}
			} // Checks if edge is convex and border aligned below
			else if (leftBorderEdge.getType() == Edge::convex && leftBorderEdges.at(edgeIndexBelow).getType() == Edge::straight)
			{
				for (PieceNode rightBorderNode : borders) {
					Piece rightBorderPiece = rightBorderNode.getPieceNodeData();
					vector<Edge> rightBorderEdges = rightBorderPiece.getEdgeList();
					for (int j = 0; j < rightBorderEdges.size(); j++) {
						Edge rightBorderEdge = rightBorderEdges.at(j);
						edgeIndexBelow = j + 1;
						if (edgeIndexBelow > rightBorderEdges.size()-1) {
							edgeIndexBelow = 0;
						}
						// Checks for concave border align below and border piece not identical
						if (rightBorderEdge.getType() == Edge::concave && rightBorderEdges.at(edgeIndexBelow).getType() == Edge::straight && leftBorderPiece.getPieceID() != rightBorderPiece.getPieceID()) {
							int score = compareEdge(leftBorderEdge.getEdgeCoords(), rightBorderEdge.getEdgeCoords());
							scores.push_back(make_tuple(leftBorderPiece.getPieceID(), i, rightBorderPiece.getPieceID(), j, score));
						}
					}
				}
			}
		}
	}
	// returns score table
	return scores;
}

// Only compares border to interior pairs where the border edge is opposite the straight edge and either concave to convex or convex to concave
vector<tuple<int, int, int, int, int>> computeBorderToInterior(vector<PieceNode> borders, vector<PieceNode> interiors, vector<tuple<int, int, int, int, int>> scores) {
	int edgeIndex;
	// Loops through all border pieces
	for (PieceNode borderNode : borders)
	{	
		// Stores piece 
		Piece borderPiece = borderNode.getPieceNodeData();
		// Stores edgelist
		vector<Edge> borderEdges = borderPiece.getEdgeList();
		//Loops through edges
		for (int i = 0; i < borderEdges.size(); i++) {
			// Stores Edge
			Edge borderEdge = borderEdges.at(i);
			// Calculates index of straight opposite
			edgeIndex = i + 2;
			// out of bounds check
			if (edgeIndex == borderEdges.size()) {
				edgeIndex = 0;
			}
			else if (edgeIndex == borderEdges.size()+1) {
				edgeIndex = 1;
			}
			// Checks if concave and opposite edge is straight
			if (borderEdge.getType() == Edge::concave && borderEdges.at(edgeIndex).getType() == Edge::straight)
			{
				// Loops through all interior pieces
				for (PieceNode interiorNode : interiors) {
					Piece interiorPiece = interiorNode.getPieceNodeData();
					vector<Edge> interiorEdges = interiorPiece.getEdgeList();
					// Loops through all edges
					for (int j = 0; j < interiorEdges.size(); j++) {
						Edge interiorEdge = interiorEdges.at(j);
						// Checks for convex type
						if (interiorEdge.getType() == Edge::convex) {
							// Compares Edges
							int score = compareEdge(borderEdge.getEdgeCoords(), interiorEdge.getEdgeCoords());
							// Adds Score
							scores.push_back(make_tuple(borderPiece.getPieceID(), i, interiorPiece.getPieceID(), j, score));
						}

					}
				}
			}
			// Checks for convex
			if (borderEdge.getType() == Edge::convex && borderEdges.at(edgeIndex).getType() == Edge::straight)
			{
				//Loops all interior pieces
				for (PieceNode interiorNode : interiors) {
					Piece interiorPiece = interiorNode.getPieceNodeData();
					vector<Edge> interiorEdges = interiorPiece.getEdgeList();
					// Loops all edges
					for (int j = 0; j < interiorEdges.size(); j++) {
						Edge interiorEdge = interiorEdges.at(j);
						// Checks for concave
						if (interiorEdge.getType() == Edge::concave) {
							// Compares Edges
							int score = compareEdge(borderEdge.getEdgeCoords(), interiorEdge.getEdgeCoords());
							// Adds score
							scores.push_back(make_tuple(borderPiece.getPieceID(), i, interiorPiece.getPieceID(), j, score));
						}

					}
				}
			}
		}
	}
	// returns score table
	return scores;
}
// compares all interior to interior pairs where concave to convex or convex to concave
vector<tuple<int, int, int, int, int>> computeInteriorToInterior(vector<PieceNode> interiors, vector<tuple<int, int, int, int, int>> scores) {
	// Loops every interior piece and edge and compares with every other valid interior piece and edge
	for (PieceNode leftInteriorNode : interiors) {
		Piece leftInteriorPiece = leftInteriorNode.getPieceNodeData();
		vector<Edge> leftInteriorEdges = leftInteriorPiece.getEdgeList();
		for (int i = 0; i < leftInteriorEdges.size(); i++) {
			Edge leftInteriorEdge = leftInteriorEdges.at(i);
			// Checks Concave
			if (leftInteriorEdge.getType() == Edge::concave) {
				for (PieceNode rightInteriorNode : interiors) {
					Piece rightInteriorPiece = rightInteriorNode.getPieceNodeData();
					vector<Edge> rightInteriorEdges = rightInteriorPiece.getEdgeList();
					for (int j = 0; j < rightInteriorEdges.size(); j++) {
						Edge rightInteriorEdge = rightInteriorEdges.at(j);
						// Checks for concave to convex and Interior Pieces not indentical
						if (rightInteriorEdge.getType() == Edge::convex && leftInteriorPiece.getPieceID() != rightInteriorPiece.getPieceID()) {
							int score = compareEdge(leftInteriorEdge.getEdgeCoords(), rightInteriorEdge.getEdgeCoords());
							scores.push_back(make_tuple(leftInteriorPiece.getPieceID(), i, rightInteriorPiece.getPieceID(), j, score));
						}

					}
				}
			}
			// Checks Convex
			if (leftInteriorEdge.getType() == Edge::convex) {
				for (PieceNode rightInteriorNode : interiors) {
					Piece rightInteriorPiece = rightInteriorNode.getPieceNodeData();
					vector<Edge> rightInteriorEdges = rightInteriorPiece.getEdgeList();
					for (int j = 0; j < rightInteriorEdges.size(); j++) {
						Edge rightInteriorEdge = rightInteriorEdges.at(j);
						// Checks for Convex to Concave and Interior Pieces not indentical
						if (rightInteriorEdge.getType() == Edge::concave && leftInteriorPiece.getPieceID() != rightInteriorPiece.getPieceID()) {
							int score = compareEdge(leftInteriorEdge.getEdgeCoords(), rightInteriorEdge.getEdgeCoords());
							scores.push_back(make_tuple(leftInteriorPiece.getPieceID(), i, rightInteriorPiece.getPieceID(), j, score));
						}
					}
				}
			}
		}
	}
	// returns score table
	return scores;
}

// All scores printed to file allscores.txt
void printScores(vector<tuple<int, int, int, int, int>> scores) {
	ofstream scorefile("allscores.txt");
	cout << "Storing scores to allscores.txt" << endl;
	for (tuple<int, int, int, int, int> score : scores) {
		//cout << "Piece: " << get<0>(score) << " Edge: " << get<1>(score) << endl;
		//cout << "Piece: " << get<2>(score) << " Edge: " << get<3>(score) << endl;
		//cout << "Score: " << get<4>(score) << endl;
		scorefile << "Piece: " << get<0>(score) << "  Edge: " << get<1>(score) << "		Piece: " << get<2>(score) << "	Edge: " << get<3>(score) <<  "		Score: " << get<4>(score) << endl;
	}
	scorefile.close();
}

// Best Score for every edge calculated and printed to file bestscores.txt
// The edge pairings that were closest to 0 for each edge added to best scores
void printBestScores(vector<PieceNode> pieceList, vector<tuple<int, int, int, int, int>> scores) {
	ofstream bestscorefile("bestscores.txt");
	cout << "Storing best scores to bestscores.txt" << endl;
	for (PieceNode p : pieceList) {
		vector<Edge> edgeList = p.getPieceNodeData().getEdgeList();
		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList.at(i).getType() != Edge::straight) {
				tuple<int, int, int, int, int> bestScore = make_tuple(0,0,0,0,0);
				for (tuple<int, int, int, int, int> score : scores) {
					if (get<0>(score) == p.getPieceNodeData().getPieceID() && get<1>(score) == i) {
						if (get<0>(bestScore) == 0) {
							bestScore = score;
						}
						if (abs(get<4>(bestScore)) > abs(get<4>(score))) {
							bestScore = score;
						}
					}
				}
				//cout << "Piece: " << get<0>(bestScore) << " Edge: " << get<1>(bestScore) << endl;
				//cout << "Piece: " << get<2>(bestScore) << " Edge: " << get<3>(bestScore) << endl;
				//cout << "Score: " << get<4>(bestScore) << endl;
				bestscorefile << "Piece: " << get<0>(bestScore) << "  Edge: " << get<1>(bestScore) << "		Piece: " << get<2>(bestScore) << "	Edge: " << get<3>(bestScore) << "		Score: " << get<4>(bestScore) << endl;
			}
		}
	}
	bestscorefile.close();
}


// Displacement Score for Matching
// Computes the absolute displacements between the two corner points along each edge.
// Displacements are calculated back and forth between the corners and an average is taken
// The smallest displacement between the x and y direction is taken to be the displacement for the two edges
// and the displacement that is just the sum of the length of the edge is IGNORED.
// Since no rotation is being applied the orientation issue has to be handled by calculating both the x and y displacement
// And using the smallest displacement calculated for each edge as the displacement of the edge
int compareEdge(vector<Point> edgeA, vector<Point>edgeB) {
	// Store first and last corner points in edge for each edge
	Point firstPointA = edgeA.front(), firstPointB = edgeB.front();
	Point lastPointA = edgeA.at(edgeA.size() - 1), lastPointB = edgeB.at(edgeB.size() - 1);

	// Intialise sum integers to calculate eight displacements
	// Two for x direction first to last and last to first edge A
	// Two for y direction last to first and first to last edge A
	// Two for x direction first to last and last to first edge B
	// Two for y direction last to first and first to last edge B
	int sumXA1 = 0, sumYA1 = 0, sumXB1 = 0, sumYB1 = 0;
	int sumXA2 = 0, sumYA2 = 0, sumXB2 = 0, sumYB2 = 0;

	// Displacements calculated for edge A
	for (int i = 0; i < edgeA.size(); i++) {
		Point p = edgeA.at(i);
		sumXA1 = firstPointA.x - p.x + sumXA1;
		sumYA1 = firstPointA.y - p.y + sumYA1;
		sumXA2 = lastPointA.x - p.x + sumXA2;
		sumYA2 = lastPointA.y - p.y + sumYA2;
	}

	//Displacements calculated for edge B
	for (int i = 0; i < edgeB.size(); i++) {
		Point p = edgeB.at(i);
		sumXB1 = firstPointB.x - p.x + sumXB1;
		sumYB1 = firstPointB.y - p.y + sumYB1;
		sumXB2 = lastPointB.x - p.x + sumXB2;
		sumYB2 = lastPointB.y - p.y + sumYB2;
	}
	
	// Averages calculated for displacements taken from first to last and last to first for each direction
	sumXA1 = int((abs(sumXA1) + abs(sumXA2)) / 2);
	sumXB1 = int((abs(sumXB1) + abs(sumXB2)) / 2);
	sumYA1 = int((abs(sumYA1) + abs(sumYA2)) / 2);
	sumYB1 = int((abs(sumYB1) + abs(sumYB2)) / 2);

	// Smallest Displacements calculated and the difference in displacements is returned
	// In a match there is no space between edges and pairs always meet at the corners
	// So in theory two displacements should cancel each other out and the difference should be 0
	// The best scores will produce values closest to 0

	if (sumXA1 > sumYA1) {
		if (abs(sumXB1) > abs(sumYB1)) {
			return sumYA1 - sumYB1;
		}
		else {
			return sumYA1 - sumXB1;
		}
	}
	else {
		if (sumXB1 > sumYB1) {
			return sumXA1 - sumYB1;
		}
		else {
			return sumXA1 - sumXB1;
		}
	}
}
