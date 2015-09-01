#include "POI.h"


POI::POI(CvPoint2D32f coordinates2d):_coordinates2d(coordinates2d),_velocityVector2d(cvPoint2D32f(0, 0)),
	_predictedPosition(cvPoint2D32f(0.0f, 0.0f)), _coordinates3d(cvPoint3D32f(0.0f, 0.0f, 0.0f)), _calibrationPoint(false)
{
	_kalman = NULL;
	_semantic = "NULL";
}

POI::POI(float x, float y) :
_coordinates2d(cvPoint2D32f(x, y)), _velocityVector2d(cvPoint2D32f(0, 0)),
	_predictedPosition(cvPoint2D32f(0.0f, 0.0f)), _coordinates3d(cvPoint3D32f(0.0f, 0.0f, 0.0f)), _calibrationPoint(false) 
{
	_kalman = NULL;
	_semantic = "NULL";

}


POI::~POI(void)
{
}


void POI::draw2d(QPainter* painter)
{

	//--- Draw POI Info
	if (!_calibrationPoint)
	{
		painter->setPen(QPen(Qt::white));
		painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));

		QPoint centerPoint(_coordinates2d.x, _coordinates2d.y);
		painter->drawEllipse(centerPoint, DRAW_RADIUS, DRAW_RADIUS);
		painter->drawPoint(centerPoint);
	} 
	else
	{
		QPen pen(QBrush(QColor(0, 255, 0)), 2.0f);
		painter->setPen(pen);
		QLine horizontalLine(_coordinates2d.x - DRAW_RADIUS, _coordinates2d.y, _coordinates2d.x + DRAW_RADIUS, _coordinates2d.y);
		QLine verticalLine(_coordinates2d.x, _coordinates2d.y - DRAW_RADIUS, _coordinates2d.x, _coordinates2d.y + DRAW_RADIUS);
		painter->drawLine(horizontalLine);
		painter->drawLine(verticalLine);

	}
}

bool POI::isPointInsideSelectionArea2d(int& pointX, int& pointY) {

	double x = abs(_coordinates2d.x - pointX);
	double y = abs(_coordinates2d.y - pointY);

	double distance = sqrt((x * x) + (y * y));

	return (distance > DRAW_RADIUS) ? false : true;
}

bool POI::isInitialized()
{

	if ( _semantic == "NULL") 
		return false;
	return true;
}
