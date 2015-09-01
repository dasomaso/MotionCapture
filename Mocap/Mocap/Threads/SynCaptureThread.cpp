#include "SynCaptureThread.h"

SynCaptureThread::SynCaptureThread(QObject *parent, int frameWidth, int frameHeight, int numCameras)
	: QThread(parent)
{
	_videoStatus = Para::PLAY_LIVE;
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	_numCameras = numCameras;
	_POIsList.resize(_numCameras);
	_noisyList.resize(_numCameras);
//	qRegisterMetaType<vector<vector<POI>>>("vector<vector<POI>>");
}

SynCaptureThread::~SynCaptureThread()
{

}


void SynCaptureThread::run()
{
	Camera **cameras = new Camera*[_numCameras];
	CameraList list;
	
	for(int i=0; i<list.Count(); i++)
	{

		cameras[i] = CameraManager::X().GetCamera(list[i].UID());

	}
	//== Create and attach frame synchronizer ==--

	cModuleSync * sync = cModuleSync::Create();
	for(int i=0; i<_numCameras; i++)
	{
		sync->AddCamera(cameras[i]);
	}

	for(int i=0; i<_numCameras; i++)
	{
		cameras[i]->Start();
		cameras[i]->SetVideoType(Core::SegmentMode);
	}

	while(1)
	{
		if(_videoStatus == Para::PLAY_LIVE)
		{
			FrameGroup *frameGroup = sync->GetFrameGroup();
			if(frameGroup)
			{
				for(int i = 0; i < _POIsList.size(); i++)
					_POIsList[i].clear();
				for(int i = 0; i<frameGroup->Count(); i++)
				{
					Frame * frame = frameGroup->GetFrame(i);
					vector<POI> newPOIs;
					for(int j = 0; j < frame->ObjectCount(); j++)
					{				
						float area = frame->Object(j)->Area();
						if(area > Para::markerFilterThreshold)
						{
							float x = frame->Object(j)->X();
							float y = frame->Object(j)->Y();
							POI temp(x, y);
							if(!ContainNoise(_noisyList[i], temp))         // if temp is not in the nosiyList, which means temp is not a noise
								newPOIs.push_back(temp);
						}										
					}

					frame->Release();
					_POIsList[i] = newPOIs;
				}
				frameGroup->Release();
				emit signalPOIsListReady(_POIsList);
			}
		}
		else if( _videoStatus == Para::CALIBRATE)
		{
			FrameGroup *frameGroup = sync->GetFrameGroup();
			if(frameGroup)
			{
				for(int i = 0; i < _POIsList.size(); i++)
					_POIsList[i].clear();
				_frameCount++;
				if(_frameCount > Para::maxFrame * Para::frameInterval)             // change to PLAY_LIVE mode when we have 500 frames
				{
					WriteCalibratedPoints();
					_videoStatus = Para::PLAY_LIVE;
					emit signalCalibrationReady();
				}
				for(int i = 0; i<frameGroup->Count(); i++)
				{
					Frame * frame = frameGroup->GetFrame(i);
					vector<POI> newPOIs;
					for(int j = 0; j < frame->ObjectCount(); j++)
					{				
						float area = frame->Object(j)->Area();
						if(area > Para::markerFilterThreshold)
						{
							float x = frame->Object(j)->X();
							float y = frame->Object(j)->Y();
							POI temp(x, y);
							if(!ContainNoise(_noisyList[i], temp))         // if temp is not in the nosiyList, which means temp is not a noise
								newPOIs.push_back(temp);
						}										
					}

					frame->Release();
					_POIsList[i] = newPOIs;
				}

				if(_frameCount % Para::frameInterval == 0)             // sample points each 3 frames
				{
					for(int i = 0; i < _POIsList.size(); i++)  
					{
						if(_POIsList[i].size() == 0 || _POIsList[i].size() > 1)
						{
							_calibratedPoints[_frameCount / Para::frameInterval].push_back(Point2f(-1.0,-1.0));
							continue;
						}
						for(int j = 0; j < _POIsList[i].size(); j++)     // now we have only one calibration point
						{
							_calibratedPoints[_frameCount / Para::frameInterval].push_back(Point2f(_POIsList[i][j]._coordinates2d.x, _POIsList[i][j]._coordinates2d.y));
						}			
					}			
				}

				frameGroup->Release();
				emit signalPOIsListReady(_POIsList);
			}
		}
		else if(_videoStatus == Para::DENOISE)
		{
			FrameGroup *frameGroup = sync->GetFrameGroup();
			if(frameGroup)
			{
				for(int i = 0; i < _POIsList.size(); i++)
					_POIsList[i].clear();
				for(int i = 0; i < frameGroup->Count(); i++)
				{
					Frame * frame = frameGroup->GetFrame(i);
					for(int j = 0; j < frame->ObjectCount(); j++)
					{				
						float area = frame->Object(j)->Area();
						if(area > Para::markerFilterThreshold)
						{
							float x = frame->Object(j)->X();
							float y = frame->Object(j)->Y();
							POI temp(x, y);
							if(!ContainNoise(_noisyList[i], temp))         // if temp is not in the nosiyList, which means temp is not a noise
								_noisyList[i].push_back(temp);
						}										
					}
					frame->Release();
				}

				frameGroup->Release();
			}
		}
		else if(_videoStatus == Para::STOP)
		{

		}
		else if(_videoStatus == Para::BREAK)
			break;
	}
	delete[] cameras;
	exec();
}

void SynCaptureThread::StartSynCapture()
{
	_videoStatus = Para::PLAY_LIVE;
}

void SynCaptureThread::StopSynCapture()
{
	_videoStatus = Para::STOP;
}

void SynCaptureThread::StopThread()
{
	_videoStatus = Para::BREAK;
}

void SynCaptureThread::StartCalibration()
{
	_videoStatus = Para::CALIBRATE;
	_frameCount = 0;
	_calibratedPoints.clear();
}

void SynCaptureThread::Denoising()
{
	_videoStatus = Para::DENOISE;
	_frameCount = 0;
}

void SynCaptureThread::PlayLive()
{
	_videoStatus = Para::PLAY_LIVE;
}

bool SynCaptureThread::ContainNoise(vector<POI>& noisyList, POI & noise)
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

void SynCaptureThread::WriteCalibratedPoints()
{
	//QString fileName = "../matlab/CalibrationPoints/CalibrationPoints.txt";
	QString fileName = "CalibrationPoints.txt";
	ofstream calibratedPointFile(fileName.toStdString().c_str());
	if(!calibratedPointFile.is_open())
		qDebug() << "create calibration file failed...";

	for(map<int ,vector<Point2f>>::const_iterator it = _calibratedPoints.begin(); it != _calibratedPoints.end(); it++)
	{
		
		calibratedPointFile << it->first << " ";
		for(int j = 0; j < it->second.size(); j++)
		{
			calibratedPointFile << it->second[j].x << " " << it->second[j].y;
			if(j < it->second.size() - 1)
				calibratedPointFile << " ";
		}
		calibratedPointFile << endl;
	}
}