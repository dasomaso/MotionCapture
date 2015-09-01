#pragma once
#include "Image.h"
#include <map>
#include <QString>
#include <cameralibrary.h>

#include "POI.h"
using namespace CameraLibrary;
class AbstractCamera
{
public:
	AbstractCamera(void);
	virtual ~AbstractCamera(void);
	//map<QString, POI> GetPOIs();
	vector<POI> GetPOIs();
	//void SetPOIs(map<QString, POI> POIs);
	void SetPOIs(vector<POI> POIs);
	void InsertPOI(POI& POItoInsert);
	virtual IplImage* GetCameraFrame() = 0;
	// this function supposed to be included in the OptitrackCamera itself, i don't know how to put it, so ...
	virtual Frame* GetOptitrackFrame() = 0;

protected:
	Image * _frame;
	//map<QString, POI> _POIs;
	vector<POI> _POIs;

};

