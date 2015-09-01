#pragma once
#include "abstractcamera.h"
#include <cameralibrary.h>
#include <opencv2/opencv.hpp>
#include "Image.h"
using namespace CameraLibrary;
class OptiTrackCamera :
	public AbstractCamera
{
public:
	OptiTrackCamera(int cameraIndex, int frameWidth, int frameHeight);
	~OptiTrackCamera(void);
	IplImage* GetCameraFrame();
	//Frame * GetCameraFrame2();
	Frame * GetOptitrackFrame();
private:
	Camera * _camera;
	int _frameWidth;
	int _frameHeight;
	
};

