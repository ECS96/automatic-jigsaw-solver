/**
CS354 Jigsaw Puzzle Problem Implementation
@class ExtractionMethods.h
@purpose Performs Piece and Edge Type Detection
	     Calculates Edge Type by calculating the displacement to extreme points in x and y direction of the edge
		 Calculates Piece Type by counting number of straight edges.
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/

#include "Piece.h"
#include "Edge.h"
#include <cmath>

using namespace cv;
using namespace std; 

#ifndef _EXTRACTIONSMETHODS_H
#define _EXTRACTIONMETHODS_H

Edge::edgeType getEdgeType(vector<Point>);
int calcEdgeType(vector<Point>);
Piece::pieceType getPieceType(vector<Edge>);
int compareEdge(vector<Point>, vector<Point>);

#endif 


