#include "Blob.h"


Blob::Blob(void)
{
	_xMoment = 0;
	_yMoment = 0;
	_numPoints = 0;
}


Blob::~Blob(void)
{
}

void Blob::AddPoint(int& x, int& y)
{
	_xMoment += x;
	_yMoment += y;
	_numPoints++;
}

int Blob::GetArea()
{

	return _numPoints;
}

CvPoint2D32f Blob::GetCentroid()
{

	(_numPoints <= 0) ? _numPoints = 1 : _numPoints;

	CvPoint2D32f centroid;

	//TODO (+0.25 just for tests)
	centroid.x = _xMoment / (float)_numPoints + 0.25;
	centroid.y = _yMoment / (float)_numPoints;

	return centroid;
}
