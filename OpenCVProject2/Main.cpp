/**
	CS354 Jigsaw Puzzle Problem Implementation
	@class main.cpp
	@purpose Run Image Operations on Pieces
			 Run Extraction Methods to identify pieces
			 Construct a Puzzle with Piece and Edge objects
			 Perform Matching on Piece Edges to produce a score for each pair possibility
	@author Edwin Stephens
	@student_number 826723
	@version 1.0 07/05/2018
*/

#include "ImageOperations.h"
#include "ExtractionMethods.h"
#include "Puzzle.h"
#include "PieceNode.h"
#include "Matching.h"
#include <string>
#include <fstream>

// Size of Jigsaw
int PUZZLE_SIZE = 24;
// Directory of Source Folder
String sourceDir = "CHANGE/TO/YOUR/OWN/DIRECTORY";
// Path in source
String filePath;
// Input img
Mat img;

int main()
{
	// Define pieces to store raw extracted edges about pieces
	vector<vector<vector<Point>>> pieces;

	//Extract Contours and Corners for all pieces in the puzzle and store in vector pieces
	//Run Image Operations Methods to retrieve shape information of piece images.
	for (int i = 1; i <= PUZZLE_SIZE; i++) {
		//Read in piece image as grayscale
		filePath = sourceDir+"/826723/automatic-jigsaw-solver/Final Jigsaw Scans/jigsawpiece" + to_string(i) + ".jpg";
		img = imread(filePath, IMREAD_GRAYSCALE);

		// Set piece num to i
		int pieceNum = i;
		cout << "Piece: " << i << " Processing";

		// Detect contours store in vector contours
		vector<vector<Point>> contours;
		contours = detectContour(img, pieceNum);

		// Detect corners store in vector corners
		img = imread(sourceDir + "/826723/automatic-jigsaw-solver/Final Jigsaw Scans/Contours/piececontour" + to_string(pieceNum) + ".jpg", IMREAD_GRAYSCALE);
		vector<Point> corners;
		corners = detectCorners(img, pieceNum);

		// Segment shape contour to four edge contours
		vector<vector<Point>> edgeList; 
		edgeList = segment(contours, corners);

		// Store edgeList for each piece in the puzzle
		pieces.push_back(edgeList);
		cout << " Complete" << endl;
	}

	int count = 0; 
	// Store images of all segmented edges in Edges Folder
	for (vector<vector<Point>> edge : pieces) {
		for (int i = 0; i < 4; i++) {
			
			Mat dst = Mat::zeros(img.size(), CV_32FC1);
			for (Point p : edge.at(i)) {
				circle(dst, p, 1, Scalar(255, 255, 255), 1, 8, 0);
			}
			imwrite(sourceDir + "/826723/automatic-jigsaw-solver/Final Jigsaw Scans/Edges/piece" + to_string(count) +"edge"+to_string(i)+ ".jpg", dst);
		}
		count = count + 1;
	}
	
	// Construct Puzzle
	Puzzle puzzle = Puzzle();

	// Construct Edges and Pieces with extracted data stored in pieces
	count = 0;
	for (vector<vector<Point>> edge : pieces) {
		// count for piece ID
		count++;
		// vector of Edge objects 
		vector<Edge> edges;
		// Construct Each Edge with type and coordinate data push to Edges vector
		for (int i = 0; i < 4; i++) {
			Edge::edgeType newEdgeType = getEdgeType(edge.at(i));
			Edge newEdge = Edge(edge.at(i), newEdgeType);
			edges.push_back(newEdge);
		}
		// Construct piece with type, edges vector and piece id
		Piece::pieceType newPieceType = getPieceType(edges);
		Piece newPiece = Piece(edges, newPieceType, count);

		// Construct PieceNode and store piece object, add to puzzle
		PieceNode pN = PieceNode(newPiece);
		puzzle.addPuzzleNode(pN);
	}

	// Outputs the types of the pieces and the edges to types.txt
	count = 0;
	ofstream types("types.txt");
	for (PieceNode pN : puzzle.getPieceList()) {
		count++;
		if (pN.getPieceNodeData().getPieceType() == Piece::Border) {
			types <<"Piece " << to_string(count) << ": Border" << endl;
		}
		else if (pN.getPieceNodeData().getPieceType() == Piece::Corner) {
			types << "Piece " << to_string(count) << ": Corner" << endl;
		}
		else if (pN.getPieceNodeData().getPieceType() == Piece::Interior) {
			types << "Piece " << to_string(count) << ": Interior" << endl;
		}

		vector<Edge> edges = pN.getPieceNodeData().getEdgeList();
		int edgeCount = 0;
		for (Edge e : edges) {
			edgeCount++;
			if (e.eType == Edge::straight) {
				types << "Edge " << to_string(edgeCount) << ": Straight" << endl;
			}
			else if (e.eType == Edge::concave) {
				types << "Edge " << to_string(edgeCount) << ": Concave" << endl;
			}
			else if (e.eType == Edge::convex) {
				types << "Edge " << to_string(edgeCount) << ": Convex" << endl;
			}
		}
		types << endl;
	}
	types.close();
	
	// piece nodes retrieved for matching
	vector<PieceNode> corners = puzzle.getPieceNodes(Piece::Corner);
	vector<PieceNode> borders = puzzle.getPieceNodes(Piece::Border);
	vector<PieceNode> interiors = puzzle.getPieceNodes(Piece::Interior);

	// vector for storing scores for pairs piece, edge, piece, edge, score
	vector<tuple<int, int, int, int, int>> scores;

	// Matching Scores Computed
	scores = computeCornerToBorder(corners, borders, scores);
	cout << "Corner-Border Matching Complete" << endl;
	scores = computeBorderToBorder(borders, scores);
	cout << "Border-Border Matching Complete" << endl;
	scores = computeBorderToInterior(borders, interiors, scores);
	cout << "Border-Interior Matching Complete" << endl;
	scores = computeInteriorToInterior(interiors, scores);
	cout << "Interior-Interior Matching Complete" << endl;

	// Output scores to file allscores.txt bestscores.txt
	printScores(scores);
	printBestScores(puzzle.getPieceList(),scores);

	return 0;
}