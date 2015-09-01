#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <QString>
#include <QPainter>
#include "Profile.h"
using namespace cv;
class POI
{
public:
	POI(CvPoint2D32f coordinates2d);
	POI(float x = 0, float y = 0);
	~POI(void);

	//! "POI" radius.
	static const int DRAW_RADIUS = 2;

	//! "POI" diameter.
	static const int DRAW_DIAMETER = DRAW_RADIUS * 2;

	//! 2D "POI" coordinates.
	//CvPoint2D32f _coordinates2d;
	Point2f _coordinates2d;

	//! 2D velocity vector of the "POI".
	CvPoint2D32f _velocityVector2d;
	
	//! 3D "POI" coordinates.
	CvPoint3D32f _coordinates3d;

	//! "POI" semantic.
	//	QString _semantic;
	QString _semantic;

	//! "Predicted Position"
	CvPoint2D32f _predictedPosition;

	//! POI Kalman tracker
	CvKalman* _kalman;

	bool _calibrationPoint;

	bool isPointInsideSelectionArea2d(int& pointX, int& pointY);
	bool isInitialized();
	void draw2d(QPainter* painter);

};

