#include "VideoController.h"

VideoController::VideoController(QObject *parent, int cameraIndex, int frameWidth, int frameHeight)
	: QThread(parent)
{
	_cameraIndex = cameraIndex;
	_frameHeight = frameHeight;
	_frameWidth = frameWidth;
	//create camera
	_optiCamera = new OptiTrackCamera(_cameraIndex, frameWidth, frameHeight);
	_POIFinder = new POIFinder;
	_tracker = new KalmanFilterTracker;
	_videoStatus = Para::PLAY_LIVE;
	string str = to_string((long long)_cameraIndex);
	str += ".txt";
	_frameCount = 0;
	//	outfile.open(str.c_str());
}

VideoController::~VideoController()
{
	delete _POIFinder;	
}


void VideoController::run()
{

	while(1)
	{
		if(_videoStatus == Para::PLAY_LIVE)
		{
			Frame * currentFrame = _optiCamera->GetOptitrackFrame();
			if(currentFrame!=NULL)
			{
				//vector<POI> newPOIs = _POIFinder->GetPOIsInImage(currentFrame);
				int count = currentFrame->ObjectCount();
				int i;
				vector<POI> newPOIs;
				for(i = 0; i < count; i++)
				{
					float area = currentFrame->Object(i)->Area();
					if(area > Para::markerFilterThreshold)
					{
						float x = currentFrame->Object(i)->X();
						float y = currentFrame->Object(i)->Y();
						POI temp(x, y);
						if(!ContainNoise(_noisyList, temp))         // if temp is not in the nosiyList, which means temp is not a noise
							newPOIs.push_back(temp);
					}

				}
				//TrackNewPOIs(newPOIs, currentFrame);
				_optiCamera->SetPOIs(newPOIs);
				emit signalPOIsReady(_optiCamera->GetPOIs(), _cameraIndex);
				//	emit signalShowPOIsImageWithoutImage(newPOIs);
				currentFrame->Release();
			}
		}
		else if(_videoStatus == Para::DENOISE)
		{
			Frame * currentFrame = _optiCamera->GetOptitrackFrame();
			if(currentFrame != NULL)
			{
				int count = currentFrame->ObjectCount();
				int i;
				for(i = 0; i < count; i++)
				{
					float area = currentFrame->Object(i)->Area();
					if(area > Para::markerFilterThreshold)
					{
						float x = currentFrame->Object(i)->X();
						float y = currentFrame->Object(i)->Y();
						POI temp(x, y);
						if(!ContainNoise(_noisyList, temp))
							_noisyList.push_back(temp);
					}

				}
				currentFrame->Release();
			}
		}
		else if(_videoStatus == Para::STOP)
		{

		}
		else if(_videoStatus == Para::CALIBRATE)            // add calibration code here ,    save image
		{		
			Frame * currentFrame = _optiCamera->GetOptitrackFrame();
			if(currentFrame != NULL)
			{
				_frameCount++;
				if(_frameCount > Para::maxFrame * Para::frameInterval)             // change to PLAY_LIVE mode when we have 500 frames
				{
					WriteCalibratedPoints();
					_videoStatus = Para::PLAY_LIVE;
					emit signalCalibrationReady(_cameraIndex);
				}
				vector<POI> newPOIs;
				int count = currentFrame->ObjectCount();
				for(int i = 0; i < count; i++)              // now we have only one calibration point
				{
					float area = currentFrame->Object(i)->Area();
					if(area > Para::markerFilterThreshold)
					{
						float x = currentFrame->Object(i)->X();
						float y = currentFrame->Object(i)->Y();
						POI temp(x, y);
						if(!ContainNoise(_noisyList, temp))
						{
							newPOIs.push_back(temp);
						}
					}

				}

				if(_frameCount % Para::frameInterval == 0)             // sample points each 3 frames
				{
					for(int i = 0; i < newPOIs.size(); i++)              // now we have only one calibration point
					{
						_calibratedPoints[_frameCount / Para::frameInterval] = Point2f(newPOIs[i]._coordinates2d.x, newPOIs[i]._coordinates2d.y);
					}
					if(newPOIs.size() == 0)
						_calibratedPoints[_frameCount / Para::frameInterval] = Point2f(-1.0, -1.0);
				}

				_optiCamera->SetPOIs(newPOIs);
				emit signalPOIsReady(_optiCamera->GetPOIs(), _cameraIndex);
				currentFrame->Release();
			}
		}
		else if(_videoStatus == Para::BREAK)
			break;
	}
	exec();
}


void VideoController::TrackNewPOIs(vector<POI> detectedPOIs, IplImage* currentFrame)
{

	/*	map<QString, POI> currentInitializedPOIs = _optiCamera->GetPOIs();

	int radius = 50;

	//--- Tracker refreshes map of current initialized POIs with newly detected ones.
	_tracker->RefreshPOIsPosition(currentInitializedPOIs, detectedPOIs, _frameWidth - 1, _frameHeight - 1, radius);

	//--- We must update cameras POIs
	_optiCamera->SetPOIs(currentInitializedPOIs);
	//map<QString, POI> temp_poi = _optiCamera->GetPOIs();
	//map<QString, POI>::const_iterator it = temp_poi.begin();
	//qDebug() << it->second._coordinates2d.x <<" " << it->second._coordinates2d.y;
	emit signalPOIsReady(_optiCamera->GetPOIs());
	//--- Builds display list
	vector<POI> POIsDisplayList = detectedPOIs;



	//---Insert initialized POIs into POIs display list
	for (map<QString, POI>::const_iterator it = currentInitializedPOIs.begin(); it != currentInitializedPOIs.end(); ++it)
	{
	POIsDisplayList.push_back(it->second);
	}

	//--- Updates image
	//emit signalShowPOIsImage(POIsDisplayList, currentFrame);
	emit signalShowPOIsImageWithoutImage(POIsDisplayList);
	int i;
	int size = POIsDisplayList.size();
	for(i = 0; i < size; i++)
	{
	outfile << POIsDisplayList[i]._coordinates2d.x << " " << POIsDisplayList[i]._coordinates2d.y <<endl;
	}*/
}


void VideoController::StopVideoCapture()
{
	_videoStatus = Para::STOP;
}

void VideoController::StartVideoCapture()
{
	_videoStatus = Para::PLAY_LIVE;
}

void VideoController::StartCalibration()
{
	_videoStatus = Para::CALIBRATE;
	_frameCount = 0;
	_calibratedPoints.clear();
}


// add denoise code here, need to add some structure to store the noise points then we can mask them, haven't done it yet... 
void VideoController::Denoising()
{
	_videoStatus = Para::DENOISE;
}


void VideoController::StopThread()
{
	_videoStatus = Para::BREAK;
}


void VideoController::InsertPOI(POI & POItoInsert)
{
	_optiCamera->InsertPOI(POItoInsert);
}


bool VideoController::ContainNoise(vector<POI>& noisyList, POI & noise)
{
	for(int i = 0; i < noisyList.size(); i++)
	{
		Point2f n1 = noisyList[i]._coordinates2d;
		Point2f n2 = noise._coordinates2d;

		if(sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y- n2.y) * (n1.y - n2.y)) < 1)
			return true;
	}
	return false;
}

void VideoController::PlayLive()
{
	_videoStatus = Para::PLAY_LIVE;
}

void VideoController::WriteCalibratedPoints()
{
	QString fileName = "../matlab/CalibrationPoints/CalibrationPoint-";
	fileName += QString::number(_cameraIndex);
	fileName += ".txt";
	ofstream calibratedPointFile(fileName.toStdString().c_str());
	if(!calibratedPointFile.is_open())
		qDebug() << "create calibration file failed...";

	for(map<int ,Point2f>::const_iterator it = _calibratedPoints.begin(); it != _calibratedPoints.end(); it++)
	{
		calibratedPointFile << it->first << " " << it->second.x << " " <<  it->second.y << endl; 
	}
}