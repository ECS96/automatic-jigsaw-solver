/**
CS354 Jigsaw Puzzle Problem Implementation
@class Edge.cpp
@purpose: Stores an Edge with object with coordinate data and edge type concave,convex,straight
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include "Edge.h"

/*
	Stores the coordinates of each edge and the type of edge stored
*/
// Constructor
Edge::Edge(vector<Point> eC, edgeType t): edgeCoords(eC), eType(t)
{
}
// Accessor for Edge Type
Edge::edgeType Edge::getType()
{
	return eType;
}
// Accessor for Edge Coords
vector<Point> Edge::getEdgeCoords()
{
	return edgeCoords;
}
