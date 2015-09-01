#include "CameraWidget.h"

extern vector<vector<POI>> globalPOIsList;

CameraWidget::CameraWidget(QWidget *parent, int frameWidth, int frameHeight, int frameRate, int numCameras, QStringList cameraNames)
	: QWidget(parent)
{
	ui.setupUi(this);
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	_frameRate = frameRate;
	_numCameras = numCameras;
	_cameraNames = cameraNames;

	QString windowTitle(tr("2D相机采集窗口"));
	setWindowTitle(windowTitle);
	createMainLayout();
#ifdef USE_SYNC_THREAD
	InitSync();
#else
	Init();
#endif
}

CameraWidget::~CameraWidget()
{
#ifdef USE_SYNC_THREAD
	if(_synCaptureThread->isRunning())
	{
		_synCaptureThread->quit();
		_synCaptureThread->wait();
		_synCaptureThread->deleteLater();
	}

#else
	for(int i = 0; i < _numCameras; i++)
	{
		if(_videoThreadList[i]->isRunning())
		{
			_videoThreadList[i]->quit();
			_videoThreadList[i]->wait();
			_videoThreadList[i]->deleteLater();
		}
	}

#endif


}

void CameraWidget::createMainLayout()
{
	//_mainLayout = new QVBoxLayout(this);
	//_mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	//	int frameWidth = _videoThread->getCamera()->getWidth();
	//	int frameHeight = _videoController->getCamera()->getHeight();

	_POIsImageWidget = new POIsImageWidget(this, _frameWidth, _frameHeight, _numCameras);
	_POIsImageWidget->installEventFilter(this);

	//_mainLayout->addWidget(_POIsImageWidget);
	_POIsImageWidget->show();
	//setLayout(_mainLayout);
}


bool CameraWidget::eventFilter(QObject *target, QEvent *event) 
{

	if(target == _POIsImageWidget)
	{
		int a = event->type();
		//	qDebug()<<a;
		if(event->type() == QEvent::MouseButtonPress)
		{
			if (target == _POIsImageWidget && event->type() == QEvent::MouseButtonPress) 
			{
				QMouseEvent *mouseEvent = static_cast<QMouseEvent *> (event);

				//--- Pauses Video Capture
				//	_videoThread->StopVideoCapture();
				int x = mouseEvent->x() * Para::scale;
				int y = mouseEvent->y() * Para::scale;
				POI selectedPOI = _POIsImageWidget->getPOIAtPosition(x, y);
				//--- Valid POI must have coordinates > 0
				if (selectedPOI._coordinates2d.x > 0)
				{

					//--- Removes old POI if it already has semantic
					if (selectedPOI.isInitialized()) 
					{
						//	_videoThread->getCamera()->removePOI(selectedPOI.getSemantic());
					}

					QPoint dialogPosition(mouseEvent->globalX(), mouseEvent->globalY());
					POISemanticSelectionDialog POISemanticDialog(this, &selectedPOI, dialogPosition);

					//--- POI semantic selection
					POISemanticDialog.exec();

					//--- Predicted position now should be the observed position
					//selectedPOI.setPredictedPosition(selectedPOI.getCoordinates2d());
					selectedPOI._predictedPosition = selectedPOI._coordinates2d;

					//--- Inserts POI with updated semantic
					//	_videoThread->InsertPOI(selectedPOI);

				}

				//		_videoThread->StartVideoCapture();
			}

		}
	}

	return QWidget::eventFilter(target, event);

}

void CameraWidget::StopThread()
{
#ifdef USE_SYNC_THREAD
	_synCaptureThread->StopThread();
#else
	for(int i = 0; i < _numCameras; i++)
	{
		_videoThreadList[i]->StopThread();
	}
#endif
	
}

void CameraWidget::GetPOIsFromCamera(vector<POI> POIs, int cameraIndex)
{
	globalPOIsList[cameraIndex] = POIs;
}



void CameraWidget::StartCalibration()
{
#ifdef USE_SYNC_THREAD
	_synCaptureThread->StartCalibration();
#else
	for(int i = 0; i < _numCameras; i++)
	{
		_videoThreadList[i]->StartCalibration();
	}
#endif
	

}

void CameraWidget::Denoising()
{
#ifdef USE_SYNC_THREAD
	_synCaptureThread->Denoising();
#else
	for(int i = 0; i < _numCameras; i++)
	{
		_videoThreadList[i]->Denoising();
	}
#endif	
	

}

void CameraWidget::PlayLive()
{
#ifdef USE_SYNC_THREAD
	_synCaptureThread->PlayLive();
#else
	for(int i = 0; i < _numCameras; i++)
	{
		_videoThreadList[i]->PlayLive();
	}
#endif
	
}

void CameraWidget::Init()
{
	_POIsImageWidget->SetCameraNames(_cameraNames);
	_calibratedList = new bool[_numCameras];
	for(int i = 0; i < _numCameras; i++)
		_calibratedList[i] = false;
	_videoThreadList.resize(_numCameras);
	for(int i = 0;i < _numCameras; i++)
	{		
		_videoThreadList[i] = new VideoController(this, i, _frameWidth, _frameHeight);
		connect(_videoThreadList[i], SIGNAL(finished()), _videoThreadList[i], SLOT(deleteLater()));
		qRegisterMetaType<vector<POI>>("vector<POI>");
		//	connect(_videoThread, SIGNAL(signalShowPOIsImageWithoutImage(vector<POI>)), _POIsImageWidget, SLOT(RefreshImageWithoutImage(vector<POI>)));
		connect(_videoThreadList[i], SIGNAL(signalPOIsReady(vector<POI>, int)), this, SLOT(GetPOIsFromCamera(vector<POI>, int)));
		connect(_videoThreadList[i], SIGNAL(signalCalibrationReady(int)), this, SLOT(slotCalibrationReady(int)));

		_videoThreadList[i]->start();	
	}
	
}

// using a sync thread instead of multiple threads
void CameraWidget::InitSync()
{
	qRegisterMetaType<vector<vector<POI>>>("vector<vector<POI>>");
	_POIsImageWidget->SetCameraNames(_cameraNames);
	_synCaptureThread = new SynCaptureThread(this, _frameWidth, _frameHeight, _numCameras);
	connect(_synCaptureThread, SIGNAL(finished()), _synCaptureThread, SLOT(deleteLater()));
	connect(_synCaptureThread, SIGNAL(signalPOIsListReady(vector<vector<POI>>)), this, SLOT(GetPOIsListSync(vector<vector<POI>>)));
	connect(_synCaptureThread, SIGNAL(signalCalibrationReady()), this, SLOT(slotCalibrationReadySync()));
	_synCaptureThread->start();	
}
void CameraWidget::slotCalibrationReadySync()
{
	emit signalDynamicCalibrationSuccess();  // all cameras has calibrated.
}


void CameraWidget::GetPOIsListSync(vector<vector<POI>> POIsList)
{
	_POIsImageWidget->ShowAllCameraPOIs(POIsList);
	globalPOIsList = POIsList;
	
}

// show all POIs when Timer out
void CameraWidget::slotTimeout()
{

	_POIsImageWidget->ShowAllCameraPOIs(globalPOIsList);
}


void CameraWidget::SetWindowSizeAndStartTimer(int w, int h)
{
	_POIsImageWidget->SetShowRange(w, h);  // set the drawing range
/*********
If we use sync thread , then we call  ShowAllCameraPOIs actively;
If we don't use sync thread, which means use _videoThreadList, we need to use a Timer to call ShowAllCameraPOIs passive every 100/_frameRate ms.
************/
#ifdef USE_SYNC_THREAD
#else
	_cameraTimer = new QTimer();
	_cameraTimer->start(1000/_frameRate);
	connect(_cameraTimer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
#endif

}

void CameraWidget::slotCalibrationReady(int cameraIndex)
{
	_calibratedList[cameraIndex] = true;
	for(int i = 0; i < _numCameras; i++)
	{
		if(_calibratedList[i] == false)return ;  // if there exist one camera has not calibrated. wait...
	}

	emit signalDynamicCalibrationSuccess();  // all cameras has calibrated.
}


