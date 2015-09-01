#ifndef POISIMAGEWIDGET_H
#define POISIMAGEWIDGET_H

#include "ImageWidget.h"
#include "POI.h"
#include <vector>
#include "Profile.h"
using namespace std;
class POIsImageWidget : public ImageWidget
{
	Q_OBJECT

public:
	POIsImageWidget(QWidget *parent, int frameWidth, int frameHeight, int numCameras);
	~POIsImageWidget();
	void drawPOIsList(QPainter *painter);
	void drawGrid(QPainter * painter);
	void DrawCameraName(int cameraIndex, QPainter * painter);
	void SetCameraNames(QStringList cameraNames);


	
	POI getPOIAtPosition(int x, int y);
	void SetPOIs(vector<POI> POIs);
	void  SetShowRange(int w, int h);
	

private:
	vector<POI> _POIs;
	vector<vector<POI>> _POIsList;
	int _numCameras;
	int _avaliableWidth;
	int _avaliableHeight;
	int _frameWidth;
	int _frameHeight;
	float _squareSize;
	QStringList _cameraNames;
//	int _cameraWidth;
//	int _cameraHeight; //the width and height that each camera points should draw in. 
	void paintEvent(QPaintEvent *paintEvent);
	void drawPOIs(QPainter *painter);
	



public slots:
	void RefreshImage(vector<POI> POIs, IplImage* image);
	void RefreshImageWithoutImage(vector<POI> POIs);
	void ShowAllCameraPOIs(vector<vector<POI>>& POIsList);
	

	
};

#endif // POISIMAGEWIDGET_H
