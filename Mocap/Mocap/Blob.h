#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
class Blob
{
public:
	Blob(void);
	~Blob(void);
	/*!
	 * Gets the blob area.
	 *
	 * @return The blob area in number of points.
	 */
	int GetArea();

	/*!
	 * Gets the blob centroid.
	 *
	 * @return The blob centroid as a CvPoint.
	 */
	CvPoint2D32f GetCentroid();

	/*!
	 * Adds a point to the blob area. (Inline function)
	 *
	 * @param x The x moment of the point.
	 * @param y The y moment of the point.
	 */
	void AddPoint(int& x, int& y); 

private:

	//! The x moment of the blob.
	float _xMoment;

	//! The y moment of the blob.
	float _yMoment;

	//! The number of blob points.
	int _numPoints;
};

