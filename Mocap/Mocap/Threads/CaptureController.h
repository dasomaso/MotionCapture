#ifndef CAPTURECONTROLLER_H
#define CAPTURECONTROLLER_H

#include <QThread>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <map>
#include <fstream>
#include <vector>
#include "BasicReconstructor.h"
#include "POI.h"
#include "Profile.h"
using namespace std;
class CaptureController : public QThread
{
	Q_OBJECT

public:
	CaptureController(QObject *parent, int frameRate, int frameWidth, int frameHeight, int numCameras);
	~CaptureController();
	void RefreshCaptureTime();
	void StartReconstruction();
	void LoadProjectionMatrix(QString calibrationResultLocation);
	void StaticCalibration();
	void FloorCalibration();
	float GetDistance(POI& p1, POI& p2);

	
	void CalculateAccuracy();
	void CalculateMarkerLoss();
	void SaveMarkerLoss();
	void SaveAccuracy();

protected:
	void run();

private:

	QTimer * _captureTimer;
	int _frameRate;
	Para::CaptureStatus _captureStatus;
	QTime _captureTime;
	BasicReconstructor * _reconstructor;
	int _frameWidth;
	int _frameHeight;
	int _numCameras;
	CvMat* _disparityToDepth;
	ofstream outfile;
	float _euclideanScale;
	float _euclideanDistance;
	//int _frameCount ; // the frame count of static calibration
	int _staticCalibCount;// the frame count of static calibration
	int _floorCalibCount;
	vector<int> _markerLoss;
	vector<vector<POI>> _floorPoints;
	vector<Para::ACCURACY_TWO_POINTS> _accracy;
	int _accracyCount;
	int _markerFrameCount;
	public slots:
			void CaptureRun();
			
signals:
		void signalRefreshTime(QTime);
		void signalPointCloud(vector<POI> pointCloud);
		void signalStaticCalibrationReady();
		void signalFloorCalibrationReady();
		void signalMarkerLoss();
		void signalCameraCenters(Vector3f*);
	//	void signalFloorCalibrated();
	
};

#endif // CAPTURECONTROLLER_H
