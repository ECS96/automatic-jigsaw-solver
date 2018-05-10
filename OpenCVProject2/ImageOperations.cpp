/**
CS354 Jigsaw Puzzle Problem Implementation
@class ImageOperations.cpp
@purpose Perform Contour detection using a canny edge detector,
		 Corner Detection using harris corner detector.
		 All computer vision algorithms performed using OpenCV Library
		 Perform Segmentation on the Shape Contours
		 Returns 4 segmented edge contours
@author Edwin Stephens
@student_number 826723
@version 1.0 07/05/2018
*/
#include "ImageOperations.h"

// Directory of Source
string sourceDir = "CHANGE/TO/YOUR/OWN/DIRECTORY";

// Images
Mat im_in, img_out, dst;

//Threshold Values
int minThresh = 50;
int maxThresh = 255;
int minClusterSize = 4;
int maxCornerPoints = 4;
int minDistThresh = 10;
int maxDistThresh = 50;
int harrisThresh = 30;
int cornerPointThresh = 60;
int minContourLenThresh = 750;

// Vectors to store shape data
vector<Point> strongCornerPoints;
vector<vector<Point> > contours;

// PieceID for writing image files
String pieceName;

/*	@function segment
	@param contours points, corner points
	Finds corner points in contour and stores the index
	Using the indexes the contour points are split into four edge contours
	@return vector containing four separate edge contours
*/
vector<vector<Point>> segment(vector<vector<Point>> contours, vector<Point> corners) {
	// Define new vector to store edge contours
	vector<vector<Point>> edgeList;

	// Define new double to store minimum distance between points
	double minDist = 0;

	// Define vector to store the indexes of the corner points in the contour vector
	vector<int> pointIndexes;

	//Define int to store index of the point closest to the corner point in the contour vector
	int closestPointIndex;

	// For each corner point the distance is calculated between every point in the contour 
	// The minimum distance is assumed to be corner point in the contour vector and index of that point is stored
	for (Point corner : strongCornerPoints) {
		for (int i = 0; i < contours.at(0).size(); i++) {
				// distance is computed for each point and stored in res
				Point coord = contours.at(0).at(i);
				double res = cv::norm(coord - corner);

				// if minDist is set to 0 set to first dist calculated
				// if minDist is greater than res set minDist to res
				if (minDist == 0) {
					minDist = res;
					closestPointIndex = i;
				}
				else if (minDist > res) {
					minDist = res;
					closestPointIndex = i;
			}
		
		}
		// Clears minimum distance 
		minDist = 0;

		// adds index of minDist corner point in contour vector to vector of corner point indexes
		pointIndexes.push_back(closestPointIndex);
	}

	/* An issue occurs with piece 14 where the contour vector being detected
	is twice the size and effectively storing the contour twice so the size
	is halved so the 3 edges can be fully segmented and partial segment for the fourth edge
	The fourth edge type can still be identified and the cause was not discovered so this a not full fix
	The accuracy of edge matching on this piece will be weakened due to this bug.
	See piece14edge3.jpg in Edges Folder
	*/
	vector<Point> c = contours.at(0);
	int size = c.size();
	if (size > 10000) {
		size = 5500;
	}
	
	// Define vector of points for storing an edge contour
	vector<Point> edge;

	// Sort the indexes in ascending order
	sort(pointIndexes.begin(), pointIndexes.end());

	// Set the first corner index to firstIndex variable
	int firstIndex = pointIndexes.front();

	// Remove index from corner point indexes
	pointIndexes.erase(pointIndexes.begin());

	/*
		Stores all the points between the indexes in the edge vector
		Each edge vector begins and ends with a corner point
		Loops over every point in the contour and segments where corner point indexes are
		Each edge contour is added to the edgeList contour containing all four segmented edges
	*/
	for (int i = firstIndex; i < size; i++) {
		Point point = c.at(i);
		if (i != pointIndexes.front()) {
			edge.push_back(point);
		}
		else {
			// Adds final corner point to edge vector
			edge.push_back(point);
			// Adds Edge vector to Edge List
			edgeList.push_back(edge);
			// Clear Edge vector for next edge in contour 
			edge.clear();
			// Adds the start point for the next edge
			edge.push_back(point);
			// Removes index of the last edge
			pointIndexes.erase(pointIndexes.begin());
			// Adds size of contour to indexes so loop continues adding points 
			// until the end of the contour is reached
			if (pointIndexes.empty()) {
				pointIndexes.push_back(size);
			}
		}
	}

	// Points between 0 and first index are added to the final edge vector
	for (int i = 0; i < firstIndex; i++) {
		edge.push_back(c.at(i));
	}
	// final edge vector added to list
	edgeList.push_back(edge);

	// clears vectors for next piece
	contours.clear();
	strongCornerPoints.clear();

	//returns segmented edge contours
	return edgeList;
}

// Sort Points by y coordinate
bool compareYX(const Point& a, const Point& b)
{
	return std::tie(a.y, a.x) < std::tie(b.y, b.x);
}

// Sort Points by x coordinate
bool compareXY(const Point& a, const Point& b)
{
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

/*
	@function detectCorners
	@param Mat img and int pieceNum
	Detects variance in intensity gradients of the image
	Clusters of points are stored where variance is marked
	Clusters are averaged to a single strong point
	Clusters that have been split by being on the same x axis 
	produce multiple strong corner points that are narrowed down by sorting by y-coord 
	and narrrowing down to a single strong point for each cluster
	@returns a vector of strong corner points
*/
vector<Point> detectCorners(Mat img, int pieceNum)
{
	// Harris Corner detects variations in intensity gradients of the contour image
	// Define image with size of input image to record variation detected
	dst = Mat::zeros(img.size(), CV_32FC1);
	// Parameters for the window size the gradient is computed
	int blockSize = 5;
	int apertureSize = 7;
	double k = 0.05;
	cornerHarris(img, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

	// Image with corner responses stored in Corners Folder
	imwrite(sourceDir + "/826723/automatic-jigsaw-solver/Full Jigsaw Scans/Corners/piececorner" + to_string(pieceNum) + ".jpg", dst);

	// Stores corner points marked by Harris Corner Method
	vector<Point> cornerPoints;
	for (int j = 0; j < dst.rows; j++) {
		for (int i = 0; i < dst.cols; i++) {
			if ((int)dst.at<float>(j, i) > cornerPointThresh) {
				cornerPoints.push_back(Point(i, j));
			}
		}
	}

	// Sorts points by x coord
	sort(cornerPoints.begin(), cornerPoints.end(), compareXY);

	// Define vector cluster to store individual clusters of points
	vector<Point> cluster;
;	for (int i = 1; i < cornerPoints.size(); i++)
	{
		// Calculates distance between two points
		Point a = cornerPoints.at(i-1);
		Point b = cornerPoints.at(i);
		double dist = cv::norm(a - b);

		// if distance is greater than 10 pixels and cluster contains less than four points then cluster is ignored
		// if distance is greater than 10 pixels and cluster contains five points or more then average point of cluster is calculated 
		// and added as a strong point. Cluster vector is cleared to accumulate the next cluster
		// if distance is less than 10 pixels it is added as part of the cluster vector
		if (dist > minDistThresh && cluster.size() < minClusterSize) {
			cluster.clear();
		}
		else if (dist > minDistThresh || i+1 == cornerPoints.size()) {
			Point zero(0,0);
			Point sum = std::accumulate(cluster.begin(), cluster.end(), zero);
			Point mean(sum.x / cluster.size(), sum.y / cluster.size());
			strongCornerPoints.push_back(mean);
			cluster.clear();
		}
		else {
			cluster.push_back(a);
		}
	}

	// Clusters that are positioned along the same point on the x axis have to be separated
	// So each point is sorted along the y axis and removed if the distance between them is less than 50 pixels then one is removed.

	while (strongCornerPoints.size() > maxCornerPoints) {
		for (int i = 1; i < strongCornerPoints.size(); i++) {
			Point a = strongCornerPoints.at(i - 1);
			Point b = strongCornerPoints.at(i);

			double dist = cv::norm(a - b);
			if (dist < maxDistThresh) {
				strongCornerPoints.erase(strongCornerPoints.begin() + i);
			}
		}
		//points sorted by y-coord
		sort(strongCornerPoints.begin(), strongCornerPoints.end(), compareYX);
	}

	// points sorted by x-coord
	sort(strongCornerPoints.begin(), strongCornerPoints.end(), compareXY);

	// corner points cleared for next piece
	cornerPoints.clear();

	// Strong points are marked on contour image and stored in Contours Folder
	for (Point p : strongCornerPoints) {
		circle(img, p, 50, Scalar(255,255,255) , 5, 8, 0);
	}
	imwrite(sourceDir + "/826723/automatic-jigsaw-solver/Final Jigsaw Scans/Corners/piececornercircle" + to_string(pieceNum) + ".jpg", img);
	
	// returns four corner points
	return strongCornerPoints;
}

/*
	@function detectContour
	@param Mat img and int pieceNum
	Takes an image applys gaussian blur to remove noise
	and thresholding to convert to a binary image.
	Detects contours by applying the canny edge detector and stores strong edge links with suzuki algorithm findContours
	Smaller contours are removed and the single piece contour is returned
	@returns vector<vector<Point>> of contour points
*/
vector<vector<Point>> detectContour(Mat img, int pieceNum)
{	
	// 5x5 Gaussian Blur reduces noise
	//Look in Gaussian Folder for Image Output
	GaussianBlur(img, img_out, Size(5, 5), 11.0);
	imwrite(sourceDir + "/826723/automatic-jigsaw-solver/Final Jigsaw Scans/Gaussian/piece" + to_string(pieceNum) + ".jpg", img_out);

	//Converts to Binary Image Black Background White Piece Foreground
	//Look in Threshold Folder for Image Output
	cv::threshold(img_out, img, minThresh, maxThresh, THRESH_BINARY_INV);
	floodFill(img, cv::Point(0, 0), Scalar(255));
	imwrite(sourceDir + "/826723/automatic-jigsaw-solver/Final Jigsaw Scans/Threshold/piece" + to_string(pieceNum) + ".jpg", img);

	//Define Image for Contour Detection
	Mat canny_output;
	//Technically hierarchy is unnecessary parameter as only one contour will be detected after smaller ones are removed.
	vector<Vec4i> hierarchy;

	//Run Edge Detection on Piece
	Canny(img, canny_output, minThresh, minThresh * 2, 3);

	//Stores Canny Output in Canny Output Folder include smaller contours that will be removed 
	imwrite(sourceDir + "/826723/automatic-jigsaw-solver/Final Jigsaw Scans/Canny Output/piececanny" + to_string(pieceNum) + ".jpg", canny_output);

	//Detect Contours in Canny
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//Remove all contours below minimum contour size
	for (vector<vector<Point> >::iterator it = contours.begin(); it != contours.end(); )
	{
		if (it->size()<minContourLenThresh)
			it = contours.erase(it);
		else
			++it;
	}

	// Draw Piece Contour Detected
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar white = Scalar(255,255,255);
		drawContours(drawing, contours, i, white, 2, 8, hierarchy, 0, Point());
	}

	//Stores Contour Image in Contours Folder
	imwrite(sourceDir +"/826723/automatic-jigsaw-solver/Final Jigsaw Scans/Contours/piececontour"+to_string(pieceNum)+".jpg", drawing);

	//Returns Vector of Contour Points
	return contours;
}


