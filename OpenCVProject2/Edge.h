/**
CS354 Jigsaw Puzzle Problem Implementation
@class Edge.h
@purpose: Stores an Edge with object with coordinate data and edge type concave,convex,straight
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef Edge_HEADER
#define Edge_HEADER

/*
	Edge Class to store the coordinate Points of the edge and the type of edge
*/
class Edge
{
	private:
		vector<Point> edgeCoords;
	public:
		enum edgeType { straight, convex, concave };
		edgeType eType;
		Edge(vector<Point> edgeCoords, edgeType type);
		edgeType getType();
		vector<Point> getEdgeCoords();

};

#endif