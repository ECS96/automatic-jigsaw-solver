// FloodFillingAlgorithm.cpp : Defines the entry point for the console application.
// @author Edwin Stephens
//

#include "stdafx.h"
#include "FloodFillingAlgorithm.h"

FloodFillingAlgorithm::~FloodFillingAlgorithm() {
}

void FloodFillingAlgorithm::flood(Point startPoint, Scalar tgtColor, Scalar loDiff) {
	floodFill(*image, startPoint, tgtColor, 0, loDiff);
}

void FloodFillingAlgorithm::flood(Point startPoint, Mat* tgtMat) {
	if (!insideImage(startPoint))
		return;

	Vec3b srcColor = image->at<Vec3b>(startPoint);

	if (image->at<Vec3b>(startPoint) == srcColor) {

		queue<Point> pointQueue;
		pointQueue.push(startPoint);

		while (!pointQueue.empty()) {
			Point p = pointQueue.front();
			pointQueue.pop();

			if (insideImage(p)) {

				if ((image->at<Vec3b>(p) == srcColor)) {
					image->at<Vec3b>(p) = tgtMat->at<Vec3b>(p);

					pointQueue.push(Point(p.x + 1, p.y));
					pointQueue.push(Point(p.x - 1, p.y));
					pointQueue.push(Point(p.x, p.y + 1));
					pointQueue.push(Point(p.x, p.y - 1));
				}
			}

		}
	}
}

bool FloodFillingAlgorithm::insideImage(Point p) {
	return (p.x >= 0) && (p.x < image->size().width) && (p.y >= 0) && (p.y < image->size().height);
}
