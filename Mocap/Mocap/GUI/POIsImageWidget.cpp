#include "POIsImageWidget.h"

POIsImageWidget::POIsImageWidget(QWidget *parent, int frameWidth, int frameHeight, int numCameras)
	: ImageWidget(parent, frameWidth, frameHeight)
{
	if(_imageRef == NULL)
		_imageRef = cvCreateImage(cvSize(frameWidth / Para::scale, frameHeight / Para::scale), 8, 1);

	_numCameras = numCameras;
	_frameHeight = frameHeight;
	_frameWidth = frameWidth;
//	_POIsList.resize(_numCameras);
}

POIsImageWidget::~POIsImageWidget()
{

}

void POIsImageWidget::drawPOIs(QPainter *painter) 
{
	vector<POI> draw_POI = _POIs;
	for (unsigned int i = 0; i < draw_POI.size(); i++)
	{
		CvPoint2D32f p = draw_POI.at(i)._coordinates2d;
		p.x /= Para::scale;
		p.y /= Para::scale;
		draw_POI.at(i)._coordinates2d = p;
		draw_POI.at(i).draw2d(painter);
	}
}

void POIsImageWidget::drawPOIsList(QPainter *painter) 
{
	for(int i = 0; i < _POIsList.size(); i++)
	{
		DrawCameraName(i, painter);            // draw camera name
		vector<POI> POIs = _POIsList[i];
		int shiftX;
		int shiftY;
		if(i < 6)
		{
			shiftX = i * _squareSize;
			shiftY = 0;
		}
		else
		{
			shiftX = (i - 6 ) * _squareSize;
			shiftY = _squareSize;
		}
		for(int j = 0; j < POIs.size(); j++)     // draw all points
		{
			cv::Point2f p = POIs[j]._coordinates2d;
			p.x = (p.x / _frameWidth) * _squareSize + shiftX;
			p.y = (p.y / _frameHeight) * _squareSize + shiftY;
			POIs[j]._coordinates2d = p;
			POIs[j].draw2d(painter);
		}
	}
}

void POIsImageWidget::DrawCameraName(int cameraIndex, QPainter * painter)
{
		painter->setPen(QColor(0, 255, 0));
		int shiftX;
		int shiftY;
		if(cameraIndex < 6)
		{
			shiftX = cameraIndex * _squareSize;
			shiftY = 10;
		}
		else
		{
			shiftX = (cameraIndex - 6) * _squareSize;
			shiftY = 10 + _squareSize;
		}
		painter->drawText(shiftX, shiftY, _cameraNames[cameraIndex]);
}

void POIsImageWidget::drawGrid(QPainter * painter)
{
	painter->setPen(QColor(255, 0, 0));
	// draw 3 horizontal lines
	for(int i = 0; i < 3; i++)
	{
		// draw the horizontal line
		QPointF horizontalStart(0, i * _squareSize);
		QPointF horizontalEnd(_avaliableWidth, i * _squareSize);
		painter->drawLine(horizontalStart, horizontalEnd);
	}
	// draw 7 vertical lines
	for(int i = 0; i < 7; i++)
	{
		QPointF verticalStart( i * _squareSize, 0);
		QPointF verticalEnd(i * _squareSize, _avaliableHeight);
		painter->drawLine(verticalStart, verticalEnd);
	}
}


void POIsImageWidget::paintEvent(QPaintEvent *paintEvent)
{

	//--- Make this widget the current context for OpenGL drawing
	makeCurrent();

	//Save current state, QPainter modifies MODELVIEW matrix.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	setupViewPort(width(), height());
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

//	drawBackgroundImage();

	//Restore state after drawing pure openGL
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	QPainter painter;
	painter.begin(this);
	drawGrid(&painter);
//	drawPOIs(&painter);
	drawPOIsList(&painter);
	painter.end();

	//--- Set OpenGL drawing context to no area
	doneCurrent();

}

POI POIsImageWidget::getPOIAtPosition(int x, int y)
{

	for (unsigned int i = 0; i < _POIs.size(); i++) 
	{
		if (_POIs.at(i).isPointInsideSelectionArea2d(x, y)) 
		{
			return _POIs.at(i);
		}
	}
	return POI(-1.0f, -1.0f);
}


void POIsImageWidget::RefreshImage(vector<POI> POIs, IplImage* image) 
{
/*	if(_imageRef == NULL)
	{
	//	qDebug()<<"creating imgRef...";
		_imageRef = cvCreateImage(cvSize(image->width/SCALE, image->height/SCALE), image->depth, 1);
	//	if(_imageRef ==NULL)
	//		qDebug()<<"create imageRef failed...";
		//_imageRef = cvCreateImage(cvSize(image->width/2, image->height/2), image->depth, 1);
	}*/
	//	cvCopyImage(image, _imageRef);
	//qDebug()<<"creating temp_img...";
	IplImage * temp_img = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);
	//qDebug()<<"create temp_img success...";
	if(image->nChannels > 1)
	{
		//qDebug()<<"enter nChannel!=1";
		cvCvtColor(image, temp_img, CV_BGR2GRAY);
		//cvCopyImage(temp_img, _imageRef);
		//cvPyrDown(temp_img, _imageRef);
		cvResize(temp_img, _imageRef);
	}
	else 
	{
		cvResize(image, _imageRef);
	}

	_POIs = POIs;
	cvReleaseImage(&temp_img);
	update();
}

void POIsImageWidget::RefreshImageWithoutImage(vector<POI> POIs) 
{
	_POIs = POIs;
	update();
}

void POIsImageWidget::SetPOIs(vector<POI> POIs)
{
	_POIs = POIs;
}

// show each POIs in splitted subwindows.
void POIsImageWidget::ShowAllCameraPOIs(vector<vector<POI>>& POIsList)
{
	_POIsList = POIsList;
	update();
}

void POIsImageWidget::SetShowRange(int w, int h)
{
	_avaliableWidth = w;
	_avaliableHeight = h;
	int a = _avaliableWidth / 6;
	int b = _avaliableHeight / 2 ;
	_squareSize = a < b ? a : b;	// the show area should be square
}

void POIsImageWidget::SetCameraNames(QStringList cameraNames)
{
	_cameraNames = cameraNames;
}