#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QThread>
#include "AbstractCamera.h"
#include "OptiTrackCamera.h"
#include "KalmanFilterTracker.h"
#include <QDebug>
#include <fstream>
#include <cameralibrary.h>
#include "POIFinder.h"
#include "Profile.h"
using namespace CameraLibrary;
using namespace std;
class VideoController : public QThread
{
	Q_OBJECT

public:
	VideoController(QObject *parent, int cameraIndex, int frameWidth, int frameHeight);
	~VideoController();

	void TrackNewPOIs(vector<POI> detectedPOIs, IplImage* currentFrame);
	void StopVideoCapture();
	void StartVideoCapture();
	void StartCalibration();
	void Denoising();
	void PlayLive();
	void StopThread();
	void InsertPOI(POI & POItoInsert);
	bool ContainNoise(vector<POI>& noisyList, POI & noise);
	void WriteCalibratedPoints();
	//void OpenCamera();

protected:
	void run();

private:
	AbstractCamera * _optiCamera;
	AbstractTracker * _tracker;
	int _cameraIndex;
	POIFinder * _POIFinder;
	vector<POI> POIsDisplayList;
	Para::VideoStatus _videoStatus;
	int _frameWidth;
	int _frameHeight;
//	ofstream outfile;
	map<int ,Point2f> _calibratedPoints;
	vector<POI> _noisyList;
	int _frameCount;
signals:
	void signalShowPOIsImage(vector<POI> POIsDisplayList, IplImage* currentFrame);
	void signalShowPOIsImageWithoutImage(vector<POI> POIsDisplayList);
	//void signalPOIsReady(map<QString, POI> POIs);
	void signalPOIsReady(vector<POI> POIs, int cameraIndex);

	void signalCalibrationReady(int ); // emit when current camera calibration already

	
};

#endif // VIDEOCONTROLLER_H
