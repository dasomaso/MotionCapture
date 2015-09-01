#include "OptiTrackCamera.h"


OptiTrackCamera::OptiTrackCamera(int cameraIndex, int frameWidth, int frameHeight)
{
	CameraList list;
	_camera = NULL;
	_frameHeight = frameHeight;
	_frameWidth = frameWidth;
	_camera = CameraManager::X().GetCamera(list[cameraIndex].UID());
	if(_camera != NULL)
	{
		_camera->SetVideoType(Core::SegmentMode);
		_camera->Start();
	}
	//_frame = cvCreateImage(cvSize(_frameWidth, _frameHeight), 8, 1);
	_frame = new Image(_frameWidth, _frameHeight, 1);	
}


OptiTrackCamera::~OptiTrackCamera(void)
{

}

IplImage* OptiTrackCamera::GetCameraFrame()
{
	Frame * cameraFrame = _camera->GetFrame();
	if (cameraFrame) 
	{
		cameraFrame->Rasterize(_frameWidth,_frameHeight,_frameWidth, 1 * 8 , _frame->getImageDataAsUnsigned());
		cameraFrame->Release();
		return _frame->getIplImage();
	}
	return NULL;		
}


Frame * OptiTrackCamera::GetOptitrackFrame()
{
	return _camera->GetFrame();
}