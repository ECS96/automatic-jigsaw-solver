#ifndef PROCESSING_FLOODFILLALGORITHM_H_
#define PROCESSING_FLOODFILLALGORITHM_H_

#include <opencv.hpp>
#include <string.h>
#include <queue>

using namespace cv;
using namespace std;

class FloodFillingAlgorithm {
public:
	FloodFillingAlgorithm(Mat* image) :
		image(image) {
	}
	virtual ~FloodFillingAlgorithm();

	void flood(Point startPoint, Scalar tgtColor, Scalar loDiff);
	void flood(Point startPoint, Mat* tgtMat);

protected:
	Mat * image;
private:
	bool insideImage(Point p);
};

#endif /* PROCESSING_FLOODFILLALGORITHM_H_ */