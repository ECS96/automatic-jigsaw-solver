/**
CS354 Jigsaw Puzzle Problem Implementation
@class ImageOperations.h
@purpose Perform Contour detection using a canny edge detector, 
		 Corner Detection using harris corner detector.
		 All computer vision algorithms performed using OpenCV Library
		 Perform Segmentation on the Shape Contours
		 Returns 4 segmented edge contours
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>

using namespace std;
using namespace cv;

#ifndef _IMAGEOPERATIONS_H
#define _IMAGEOPERATIONS_H

vector<vector<Point>> detectContour(Mat, int);
vector<Point> detectCorners(Mat, int);
Mat dilation(Mat);
Mat Morphology_Operations(Mat);
vector<vector<Point>> segment(vector<vector<Point>>, vector<Point>);
bool CompareXY(const Point&, const Point&);


#endif