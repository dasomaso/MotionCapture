#include "CaptureController.h"
extern vector<vector<POI>> globalPOIsList;
CaptureController::CaptureController(QObject *parent, int frameRate, int frameWidth, int frameHeight, int numCameras)
	: QThread(parent)
{
	_frameRate = frameRate;
	_captureStatus = Para::NON_START;
	_captureTimer = NULL;
	_frameHeight = frameHeight;
	_frameWidth = frameWidth;
	_euclideanScale = 1;
	_numCameras = numCameras;
	_staticCalibCount = 0;
	_floorCalibCount = 0;
	_reconstructor = new BasicReconstructor(_frameWidth, _frameHeight, _numCameras);
	_captureTime.setHMS(0, 0, 0, 0);
	outfile.open("3dpoints.txt");
}

CaptureController::~CaptureController()
{
	outfile.close();
	if(_captureTimer != NULL)
		delete _captureTimer;
}


void CaptureController::run()
{
	_captureTimer = new QTimer();
	_captureTimer->start(1000/_frameRate);
	connect(_captureTimer, SIGNAL(timeout()), this, SLOT(CaptureRun()));

	exec();
}



void CaptureController::CaptureRun()
{
	//qDebug()<<"timeout...";
	if(_captureStatus == Para::RECONSTRUCTION)
	{
		RefreshCaptureTime();
		if(globalPOIsList.size() >= 2)
		{

			//	vector<POI> tridimensionalPOIs = _reconstructor->reconstructPOIs(_POIsList[0], _POIsList[1]);
			//emit signalPointCloud(tridimensionalPOIs);
			long long start = clock();
			//_reconstructor->UnDistorted(globalPOIsList);
			_reconstructor->Find2DMarkerMatching(globalPOIsList);

			vector<POI> tridimensionalPOIs = _reconstructor->Reconstruction();

/********** 
 I didn't multiply the _euclideanScale because it is not needed when showing these points.
 If you need to output the points in euclidean coordinates, you need to multiply _euclideanScale after static calibration.
 ************/
/*			for(int i = 0; i < tridimensionalPOIs.size(); i++)               
			{
				tridimensionalPOIs[i]._coordinates3d.x *= _euclideanScale;
				tridimensionalPOIs[i]._coordinates3d.y *= _euclideanScale;
				tridimensionalPOIs[i]._coordinates3d.z *= _euclideanScale;

			}*/        
			//	long long end = clock();

			emit signalPointCloud(tridimensionalPOIs);
		}

	}
	else if(_captureStatus == Para::STATIC_CALIBRATION && _staticCalibCount <= 100)
	{
		if(globalPOIsList.size() >= 2)         // at least 3 cameras 
		{
			long long start = clock();
			_reconstructor->Find2DMarkerMatching(globalPOIsList);
			vector<POI> tridimensionalPOIs = _reconstructor->Reconstruction();
			int size = tridimensionalPOIs.size();
			if(size == 2)
			{
				_euclideanDistance += GetDistance(tridimensionalPOIs[0], tridimensionalPOIs[1]);
				_staticCalibCount++;
			}
			
			if(_staticCalibCount == 99)
			{
				_euclideanScale = (Para::wandLength * 100.0) / _euclideanDistance;
				emit signalStaticCalibrationReady();
				_captureStatus = Para::RECONSTRUCTION;
			}
			emit signalPointCloud(tridimensionalPOIs);
		}

	}
	else if(_captureStatus == Para::FLOOR_CALIBRATION && _staticCalibCount <= 200)
	{
		if(globalPOIsList.size() >= 2)         // at least 3 cameras 
		{
			long long start = clock();
			_reconstructor->Find2DMarkerMatching(globalPOIsList);
			vector<POI> tridimensionalPOIs = _reconstructor->Reconstruction();
			int size = tridimensionalPOIs.size();
			if(size == 3)
			{
				_floorPoints.push_back(tridimensionalPOIs);
				_floorCalibCount++;	
			}
			if(_floorCalibCount == 199)
			{
				vector<POI> tridimensionalPOIs;
				for(int i = 0; i < 3; i++)
				{
					POI p;
					CvPoint3D32f temp;
					temp.x = 0;
					temp.y = 0;
					temp.z = 0;
					for(int j = 0; j < _floorPoints.size(); j++)
					{
						temp.x += _floorPoints[j][i]._coordinates3d.x;
						temp.y += _floorPoints[j][i]._coordinates3d.y;
						temp.z += _floorPoints[j][i]._coordinates3d.z;
					}
					temp.x /= _floorPoints.size();
					temp.y /= _floorPoints.size();
					temp.z /= _floorPoints.size();
					p._coordinates3d = temp;
					tridimensionalPOIs.push_back(p);
				}
				_reconstructor->FloorRotationTranslation(tridimensionalPOIs);
				emit signalFloorCalibrationReady();
				_captureStatus = Para::RECONSTRUCTION;
			}
			emit signalPointCloud(tridimensionalPOIs);
		}
	}
	else if(_captureStatus == Para::NON_START)
	{

	}
	else if(_captureStatus == Para::STOP)                  // pass blank points to show
	{
		vector<POI> tridimensionalPOIs;
		emit signalPointCloud(tridimensionalPOIs);
	}
	else if(_captureStatus == Para::MARKER_LOSS)
	{
		if(globalPOIsList.size() >= 2)
		{
			_reconstructor->Find2DMarkerMatching(globalPOIsList);
			vector<POI> tridimensionalPOIs = _reconstructor->Reconstruction();
			_markerLoss.push_back(tridimensionalPOIs.size());
		
			if(_markerFrameCount == 1999)
			{
				SaveMarkerLoss();

				emit signalMarkerLoss();
			_captureStatus = Para::RECONSTRUCTION;

			}
			_markerFrameCount++;
			emit signalPointCloud(tridimensionalPOIs);
		}
	}
	else if(_captureStatus == Para::ACCURACY)
	{
		if(globalPOIsList.size() >= 2)
		{
			_reconstructor->Find2DMarkerMatching(globalPOIsList);
			vector<POI> tridimensionalPOIs = _reconstructor->Reconstruction();
			if(tridimensionalPOIs.size() == 2)
			{
				
				Para::ACCURACY_TWO_POINTS temp;
				temp.left = tridimensionalPOIs[0]._coordinates3d;
				temp.right = tridimensionalPOIs[1]._coordinates3d;
				_accracy.push_back(temp);
				if(_accracyCount == 499)
				{
					SaveAccuracy();
					_captureStatus = Para::RECONSTRUCTION;
				}
				_accracyCount++;				
			}
			emit signalPointCloud(tridimensionalPOIs);		
		}
	}
	
}

void CaptureController::RefreshCaptureTime()
{
	int timeToAddInMSec = 1000/ _frameRate;
	_captureTime = _captureTime.addMSecs(timeToAddInMSec);
	emit signalRefreshTime(_captureTime);
}


void CaptureController::StartReconstruction()
{
	_captureStatus = Para::RECONSTRUCTION;
}

void CaptureController::LoadProjectionMatrix(QString calibrationResultLocation)
{
	_reconstructor->LoadProjectionMatrix(calibrationResultLocation);
	Vector3f* cameraCenters = _reconstructor->GetCameraCenters();

	emit signalCameraCenters(cameraCenters);
}


void CaptureController::StaticCalibration()
{
	_captureStatus = Para::STATIC_CALIBRATION;
	_euclideanDistance = 0;
	_staticCalibCount = 0;
}

void CaptureController::FloorCalibration()
{
	_captureStatus = Para::FLOOR_CALIBRATION;
	_floorCalibCount = 0;
	_floorPoints.clear();
}

float CaptureController::GetDistance(POI& left, POI& right)
{
	Point3f p1 = left._coordinates3d;
	Point3f p2 = right._coordinates3d;
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
}


void CaptureController::CalculateAccuracy()
{
	_accracy.clear();
	_accracyCount = 0 ;  // calculate 1000 frames
	_captureStatus = Para::ACCURACY;

}

void CaptureController::CalculateMarkerLoss()
{
	_markerLoss.clear();
	_markerFrameCount = 0 ;  // calculate 1000 frames
	_captureStatus = Para::MARKER_LOSS;	
}

void CaptureController::SaveMarkerLoss()
{
	ofstream outfile("markerloss.txt");
	for(int i = 0; i < _markerLoss.size(); i++)
		outfile << _markerLoss[i] << endl;
	outfile.close();
}

void CaptureController::SaveAccuracy()
{
	ofstream outfile("accuracy.txt");
	for(int i = 0; i < _accracy.size(); i++)
		outfile << _accracy[i].left.x << " " <<  _accracy[i].left.y  <<" "<< _accracy[i].left.z << " "<<  _accracy[i].right.x << " " <<  _accracy[i].right.y  <<" "<< _accracy[i].right.z << endl;	
	outfile.close();
}
