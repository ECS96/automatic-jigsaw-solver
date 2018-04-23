#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <numeric>

using namespace cv;
using namespace std;

Mat im_in, im_in2, im_th, im_floodfill, im_floodfill_inv, im_out, src, gray, dst, dst_norm, dst_norm_scaled, dilated, im_th_inv;
int thresh = 50;
int max_thresh = 255;
int contour_length_threshold = 500;
int dilation_size = 0;
int dilation_elem = 0;
int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
RNG rng(12345);
vector<Point> strongCornerPoints;

vector<vector<Point> > contours;

list<int> l;

const char* corners_window = "Corners detected";

void thresh_callback(int, void*);
void harris_corner(int, void*);
void dilation(int, void*);
void Morphology_Operations(int, void*);
void segment(int, void*);


int main(int argc, char **argv)
{

	im_in = imread("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/lowres4.png", IMREAD_GRAYSCALE);
	GaussianBlur(im_in, im_in2, Size(5,5), 11.0);
	// Threshold.
	// Set values equal to or above 220 to 0.
	// Set values below 220 to 255.
	im_th;
	threshold(im_in2, im_th, thresh, max_thresh, THRESH_BINARY_INV);

	dilation(0, 0);
	Morphology_Operations(0, 0);
	// Floodfill from point (0, 0)
	im_floodfill = im_th.clone();
	floodFill(im_floodfill, cv::Point(0, 0), Scalar(255));
	// Invert floodfilled image
	//bitwise_not(im_floodfill, im_floodfill_inv);

	// Combine the two images to get the foreground.
	//im_out = (im_th | im_floodfill_inv);

	// Display images
	imshow("Thresholded Image", im_th);
	imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/threshhold.png", im_th);
	imshow("Floodfilled Image", im_floodfill);
	imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/floodfill.png", im_floodfill);
	//imshow("Inverted Floodfilled Image", im_floodfill_inv);
	//imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/floodfillinv.png", im_floodfill_inv);
	//imshow("Foreground", im_out);

	createTrackbar(" Canny thresh:", "Floodfilled Image", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	harris_corner(0, 0);
	segment(0, 0);
	return 0;
}

void segment(int, void*) {
	vector<vector<Point>> edgeList;
	double min = -1;
	vector<int> pointIndexes;
	int closestPointIndex;
	for (Point corner : strongCornerPoints) {
		for (vector<Point> v : contours) {
			for (int i = 0; i < v.size(); i++) {
				Point temp;
				Point coord = v.at(i);
				temp.x = coord.y;
				temp.y = coord.x;
				double res = cv::norm(temp - corner);
				if (min == -1) {
					min = res;
				}
				else if (min > res) {
					min = res;
					closestPointIndex = i;
				}
			}
		}
		cout << min << endl;
		min = -1;
		pointIndexes.push_back(closestPointIndex);
	}
	vector<Point> temp;
	sort(pointIndexes.begin(), pointIndexes.end());

	int firstIndex = pointIndexes.front();
	pointIndexes.erase(pointIndexes.begin());
	for (vector<Point> c : contours) {
		for (int i = firstIndex; i < c.size(); i++) {
			if (i != pointIndexes.front()+1) {
				temp.push_back(c.at(i));
			}
			else {
				edgeList.push_back(temp);
				temp.clear();
				temp.push_back(c.at(i - 1));
				pointIndexes.erase(pointIndexes.begin());
				pointIndexes.push_back(c.size());
			}
		}
		for (int i = 0; i < firstIndex; i++) {
			temp.push_back(c.at(i));
		}
		edgeList.push_back(temp);
	}
	for (vector<Point> edge : edgeList) {
		for (Point p : edge) {
			cout << p;
		}
		cout << endl;
	}
	cout << edgeList.size() << endl;
	imshow("display", gray);
	waitKey(0);

}
//
void harris_corner(int, void*)
{
	gray = imread("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/lowrescontours.png", IMREAD_GRAYSCALE);
	dst = Mat::zeros(gray.size(), CV_32FC1);
	vector<Point> cornerPoints;
	int blocksize = 5;
	int aperturesize = 7;
	double k = 0.05;
	cornerHarris(gray, dst, blocksize, aperturesize, k, BORDER_DEFAULT);

	for (int j = 0; j < dst.rows; j++) {
		for (int i = 0; i < dst.cols; i++) {
			if ((int)dst.at<float>(j, i) > thresh) {
				cornerPoints.push_back(Point(j, i));
			}
		}
	}
	vector<Point> temp;
	Mat test = gray;
;	for (int i = 1; i < cornerPoints.size(); i++)
	{
		Point a = cornerPoints.at(i-1);
		Point b = cornerPoints.at(i);
		double res = cv::norm(a - b);
		if (res > 10 && temp.size() < 5) {
			temp.clear();
		}
		else if (res > 10 || i+1 == cornerPoints.size()) {
			Point zero(0,0);
			Point sum = std::accumulate(temp.begin(), temp.end(), zero);
			Point mean(sum.x / temp.size(), sum.y / temp.size());
			//test.at<uchar>(mean.x,mean.y) = 255;
			strongCornerPoints.push_back(mean);
			temp.clear();
		}
		else {
			temp.push_back(a);
		}
	}


	for (Point x : strongCornerPoints) {
			std::cout << x << ' ';
			std::cout << std::endl;
	}

	namedWindow(corners_window, WINDOW_AUTOSIZE);
	imshow(corners_window, test);
	waitKey(0);
	destroyAllWindows();

}
/** @function dilation */
void dilation(int, void*)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	/// Apply the dilation operation
	dilate(im_th, dilated, element);
	imshow("Dilation Demo", dilated);
}


void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(im_th, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	for (vector<vector<Point> >::iterator it = contours.begin(); it != contours.end(); )
	{
		if (it->size()<contour_length_threshold)
			it = contours.erase(it);
		else
			++it;
	}

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}
	
	std::cout << std::endl;
	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
	imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/lowrescontours.png", drawing);
	waitKey(0);
	destroyAllWindows();

}

void Morphology_Operations(int, void*)
{
	int operation = morph_operator + 2;

	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

	morphologyEx(dilated, dst, operation, element);
	imshow("Morph", dst);
}