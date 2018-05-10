/**
CS354 Jigsaw Puzzle Problem Implementation
@class matching.h
@purpose Perform matching on piece edges and store a score with the edge pairing
		 Compare edges and compute displacement score
		 Print and calculate best score for each edge to file
		 Print all scores to file
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/

#include "PieceNode.h"
#include "Piece.h"
#include "Puzzle.h"
#include <cmath>
#include <fstream>

using namespace std;

#ifndef MATCHING_HEADER
#define MATCHING_HEADER

vector<tuple<int,int,int,int,int>> computeCornerToBorder(vector<PieceNode>, vector<PieceNode>, vector<tuple<int,int,int,int,int>>);
vector<tuple<int, int, int, int, int>> computeBorderToBorder(vector<PieceNode>, vector<tuple<int, int, int, int, int>>);
vector<tuple<int, int, int, int, int>> computeBorderToInterior(vector<PieceNode>, vector<PieceNode>, vector<tuple<int, int, int, int, int>>);
vector<tuple<int, int, int, int, int>> computeInteriorToInterior(vector<PieceNode>, vector<tuple<int, int, int, int, int>>);
void printScores(vector<tuple<int, int, int, int, int>>);
void printBestScores(vector<PieceNode>,vector<tuple<int, int, int, int, int>>);
int compareEdge(vector<Point>, vector<Point>);


#endif