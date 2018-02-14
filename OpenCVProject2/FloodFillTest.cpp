#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat im_in, im_th, im_floodfill, im_floodfill_inv, im_out, src,gray, dst,dst_norm, dst_norm_scaled, dilated, im_th_inv;
int thresh = 200;
int max_thresh = 255;
int contour_length_threshold = 75;
int dilation_size = 0; 
int dilation_elem = 0;
int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
RNG rng(12345);

list<int> l;

const char* corners_window = "Corners detected";

void thresh_callback(int, void*);
void harris_corner(int, void*);
void dilation(int, void*);
void Morphology_Operations(int, void*);

int main(int argc, char **argv)
{

	im_in = imread("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/lowres4.png", IMREAD_GRAYSCALE);


	// Threshold.
	// Set values equal to or above 220 to 0.
	// Set values below 220 to 255.
	im_th;
	threshold(im_in, im_th, thresh, max_thresh, THRESH_BINARY_INV);

	//dilation(0, 0);
	//Morphology_Operations(0, 0);
	// Floodfill from point (0, 0)
	im_floodfill = im_th.clone();
	floodFill(im_floodfill, cv::Point(0,0), Scalar(255));
	// Invert floodfilled image
	bitwise_not(im_floodfill, im_floodfill_inv);

	// Combine the two images to get the foreground.
	im_out = (im_th | im_floodfill_inv);

	// Display images
	imshow("Thresholded Image", im_th);
	imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/threshhold008.png", im_in);
	imshow("Floodfilled Image", im_floodfill);
	imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/floodfill008.png", im_floodfill);
	imshow("Inverted Floodfilled Image", im_floodfill_inv);
	imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/floodfillinv008.png", im_floodfill_inv);
	imshow("Foreground", im_out);

	createTrackbar(" Canny thresh:", "Floodfilled Image", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	//harris_corner(0, 0);
	//contour_length_threshold = 7;
	//im_th = dilated;
	//thresh_callback(0, 0);
	return 0;
}
//
void harris_corner(int, void*)
	{	
//	IplImage *im = cvLoadImage("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/lowrescontours004.png", CV_LOAD_IMAGE_GRAYSCALE);

	gray = imread("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/lowrescontours102.png", IMREAD_GRAYSCALE);

	dst = Mat::zeros(gray.size(), CV_32FC1);

	int blocksize = 5;
	int aperturesize = 7;
	double k = 0.05;

	//double *minv, *maxv;
	//CvPoint *minl, *maxl;

	//IplImage *dst = cvCreateImage(cvGetSize(im), IPL_DEPTH_32F, 1);

	//cvCornerHarris(im, dst, blocksize, aperturesize, k);


	cornerHarris(gray, dst, blocksize, aperturesize, k, BORDER_DEFAULT);
//	cvMinMaxLoc(dst, minv, maxv, minl, maxl);
//
//	IplImage *dilated = cvCloneImage(dst);
//
//	cvDilate(dst, dilated);
//
//	CvMat *localMax = cvCreateMat(dst->height, dst->width, CV_8U);
//
//	cvCmp(dst, dilated, localMax, CV_CMP_EQ);
//
//	double threshold = 0.01 * *(maxv);
//	cvThreshold(dst, dst, threshold, 255, CV_THRESH_BINARY);
//
//	CvMat *cornerMap = cvCreateMat(dst->height, dst->width, CV_8U);
//	cvConvert(dst, cornerMap);
//	cvAnd(cornerMap, localMax, cornerMap);
//
//	int radius = 3;
//	int thickness = 2;
//
//	for (int i = 0; i < cornerMap->height; i++) {
//		for (int j = 0; j < cornerMap->width; j++) {
//			Scalar colour = cornerMap.at<ucahr
//			if () {
//				l.append((j, i));
//			}
//		}
//}
	/*normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);

	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
			}
		}
	}*/

	namedWindow(corners_window, WINDOW_AUTOSIZE);
	imshow(corners_window, dst);
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
	vector<vector<Point> > contours;
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
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
	imwrite("C:/Users/Edwin/Documents/Uni/3rd Year/Project/Scanned Pictures/lowrescontours008.png", drawing);
	waitKey(0);
	destroyAllWindows();

}

void Morphology_Operations(int, void*)
{
	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator + 2;

	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

	/// Apply the specified morphology operation
	morphologyEx(dilated, dst, operation, element);
	imshow("Morph", dst);
}