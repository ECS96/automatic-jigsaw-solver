#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat puzzImage;
	vector<Mat> puzzImages;
	vector<cv::String> fn;
	glob("/src/images/*.jpg", fn, false);
	size_t count = fn.size();
	for (size_t i = 0; i < count; i++)
	{
		puzzImages.push_back(imread(fn[i]));
	}
}