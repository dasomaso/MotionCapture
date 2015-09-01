#ifndef SYNCAPTURETHREAD_H
#define SYNCAPTURETHREAD_H

#include <QThread>
#include <cameralibrary.h>
#include <vector>
#include <QMetaType>
#include <QDebug>
#include <fstream>
#include "POI.h"
#include "Profile.h"
using namespace CameraLibrary;
using namespace std;
class SynCaptureThread : public QThread
{
	Q_OBJECT

public:
	SynCaptureThread(QObject *parent, int frameWidth, int frameHeight, int numCameras);
	~SynCaptureThread();
	void StopSynCapture();
	void StartSynCapture();
	void StopThread();
	void StartCalibration();
	void Denoising();
	void PlayLive();
	bool ContainNoise(vector<POI>& noisyList, POI & noise);
	void WriteCalibratedPoints();
protected:
	void run();

private:
	int _frameHeight;
	int _frameWidth;
	int _numCameras;
	Para::VideoStatus _videoStatus;
	vector<vector<POI>> _POIsList;
	vector<vector<POI>> _noisyList;
	int _frameCount;
	map<int ,vector<Point2f>> _calibratedPoints;
	
signals:
	void signalPOIsListReady(vector<vector<POI>>);
	void signalCalibrationReady();
};

#endif // SYNCAPTURETHREAD_H
