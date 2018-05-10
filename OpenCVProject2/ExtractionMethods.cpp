/**
CS354 Jigsaw Puzzle Problem Implementation
@class ExtractionMethods.cpp
@purpose Performs Piece and Edge Type Detection
		 Calculates Edge Type by calculating the displacement to extreme points in x and y direction of the edge
		 Calculates Piece Type by counting number of straight edges.
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/

#include "ExtractionMethods.h"

int maxDisp = 600;
int minDisp = 190;
int minStraightDisp = 105;
int straight = 1, concave = 2, convex = 3;

// Returns Straight, Concave, Convex based on displacement calculated in CalcEdgeType()
Edge::edgeType getEdgeType(vector<Point> edgeCoords)
{
	int edge = calcEdgeType(edgeCoords);
	if (edge == straight) {
		return Edge::straight;
	}
	if (edge == concave) {
		return Edge::concave;
	}
	if (edge == convex) {
		return Edge::convex;
	}
}

// Finds the extreme points along the edge and stores them in xmax,xmin,ymax,ymin
// 
int calcEdgeType(vector<Point> edgeCoords)
{
	//Calculates Extreme Points
	Point corner = edgeCoords.front();
	int xdist = 0, ydist = 0;
	int xmax = 0, ymax = 0, xmin = 0, ymin = 0;
	for (Point p : edgeCoords) {
		ydist = corner.y - p.y;
		xdist = corner.x - p.x;
		if (xdist > xmax) {
			xmax = xdist;
		}
		if (ydist > ymax) {
			ymax = ydist;
		}
		if (ydist < ymin) {
			ymin = ydist;
		}
		if (xdist < xmin) {
			xmin = xdist;
		}
	}

	// Calculates Edge Type from the Displacement of Extreme Points
	// A straight would have 0 displacement
	// A convex would have + displacement
	// A concave would have - displacement
	// Edges are not all in same orientation so four branches catch all possibilities
	// Where an edge could be either on the top,left,right,bottom of the piece

	if (ymin < -(maxDisp)) {
		if (maxDisp > xmax > minDisp) {
			return concave;
		}
		else if (maxDisp > abs(xmin) > minDisp) {
			return concave;
		}
		else {
			if (xmax < minStraightDisp && xmin > -(minStraightDisp)) {
				return straight;
			}
			if (xmax > abs(xmin)) {
				return convex;
			}
			else {
				return concave;
			}
		}	
	}
	if (ymax > maxDisp) {
		if (maxDisp > xmax > minDisp) {
			return concave;
		}
		else if (maxDisp > abs(xmin) > minDisp) {
			return convex;
		}
		else {
			if (xmax < minStraightDisp && xmin > -(minStraightDisp)) {
				return straight;
			}
			if (xmax > abs(xmin)) {
				return concave;
			}
			else {
				return convex;
			}
		}
	}
	if (xmin < -(maxDisp)) {
		if (maxDisp > ymax > minDisp) {
			return concave;
		}
		else if (maxDisp > abs(ymin) > minDisp) {
			return convex;
		}
		else {
			if (ymax < minStraightDisp && ymin > -(minStraightDisp)) {
				return straight;
			}
			if (ymax > abs(ymin)) {
				return concave;
			}
			else {
				return convex;
			}

		}
	}

	if (xmax > maxDisp) {
		if (maxDisp > ymax > minDisp) {
			return convex;
		}
		else if (maxDisp > abs(ymin) > minDisp) {
			return concave;
		}
		else {
			if (ymax < minStraightDisp && ymin > -(minStraightDisp)) {
				return straight;
			}
			if (ymax > abs(ymin)) {
				return convex;
			}
			else {
				return concave;
			}
		}
	}

	return straight;
}

// Returns Piece type on number of straight edges counted in the edge list
Piece::pieceType getPieceType(vector<Edge> edgeList)
{
	int edgeNum = 0;
	for (Edge e : edgeList)
	{
		if (e.getType() == Edge::straight)
		{
			edgeNum++;
		}
	}

	if (edgeNum > 1) {
		return Piece::Corner;
	}
	else if (edgeNum == 1) {
		return Piece::Border;
	}
	else if (edgeNum == 0) {
		return Piece::Interior;
	}
}
