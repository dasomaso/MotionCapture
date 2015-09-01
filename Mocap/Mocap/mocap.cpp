#include "mocap.h"
#define NAVIGATION_SCALE 0.25  // navigation tabwidget occupies 1/4 of the width of the screen
vector<vector<POI>> globalPOIsList;
Mocap::Mocap(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	this->showMaximized();
	_cameraModule = NULL;
	_reconstructionModule = NULL;
	_calibrationMessage = NULL;
	_mdiArea = NULL;
	_leftDock = NULL;
	_rightDock = NULL;
	_ribbon = NULL;
	_calibrationWidget = NULL;
	_reconstructionWidget = NULL;
	_postprocessWidget = NULL;
	_evaluationWidget = NULL;
	_navigation = NULL;
	_calibrationParaWidget = NULL;
	_cameraParaWidget = NULL;
	_reconstructionParaWidget = NULL;

	//	setCentralWidget(_midArea);
	_numCameras = 0;
	_frameHeight = 0;
	_frameWidth = 0;
	setWindowTitle(tr("人体运动捕获-虚拟现实课题组"));
	//	_calibrationResultLocation = "F:/workspace/Qt/Mocap/matlab/projectionmatrix.txt";
	_frameRate = 120;
	qRegisterMetaType<vector<vector<POI>>>("vector<vector<POI>>");

	//	CreateDock();
	CreateRibbon();
	CreateNavigation();
	_calibrationMessage = new QLabel(this);
	ui.statusBar->addWidget(_calibrationMessage);
	ui.statusBar->setStyleSheet("QLabel{border: 0px; color: red}");
	_cameraIntialized = false;
	_staticCalibrated = false;
	_dynamicCalibrated = false;
//	slotDynamicCalibrationSuccess();


}

Mocap::~Mocap()
{
	if(_cameraIntialized)
		ReleaseOptiTrackCameras();

	if(_cameraModule)
	{
		delete _cameraModule;
		_cameraModule = NULL;
	}

	if(_reconstructionModule)
	{
		delete _reconstructionModule;
		_reconstructionModule = NULL;
	}


	if(_calibrationMessage)
	{
		delete _calibrationMessage;
		_calibrationMessage = NULL;
	}

	if(_mdiArea)
	{
		delete _mdiArea;
		_mdiArea = NULL;
	}

	if(_leftDock)
	{
		delete _leftDock;
		_leftDock = NULL;
	}

	if(_rightDock)
	{
		delete _rightDock;
		_rightDock = NULL;
	}

	if(_ribbon)
	{
		delete _ribbon;
		_ribbon = NULL;
	}

	if(_navigation)
	{
		delete _navigation;
		_navigation = NULL;
	}


}


void Mocap::CreateSubWindows()
{
	//create 3D widget
	//	_mdiArea->tileSubWindows();
	_mdiArea = new QMdiArea(this);
	_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	_mdiArea->setGeometry(QRect(0, 90, this->width() - this->_navigation->width() - 5,this->statusBar()->geometry().y() - 90));

	QVBoxLayout *vLayout=new QVBoxLayout(_mdiArea);
	_reconstructionModule = new ThreeDWidget(this, _frameRate, _frameWidth, _frameHeight, _numCameras);

	connect(_reconstructionModule, SIGNAL(signalRefreshTime(QTime)), this, SLOT(RefreshTime(QTime)));
	connect(_reconstructionModule, SIGNAL(signalStaticCalibrationSuccess()), this, SLOT(slotStaticCalibrationSuccess()));
	connect(_reconstructionModule, SIGNAL(signalFloorCalibrationSuccess()), this, SLOT(slotFloorCalibrationSuccess()));
	connect(_reconstructionModule, SIGNAL(signalMarkerLoss()), this, SLOT(slotMarkerLoss()));
	QMdiSubWindow* modelVisualizationWindow = _mdiArea->addSubWindow(_reconstructionModule);
	vLayout->addWidget(modelVisualizationWindow);
	//	modelVisualizationWindow->resize(_frameWidth/SCALE, _frameHeight/SCALE);

	//modelVisualizationWindow->setWindowFlags(Qt::FramelessWindowHint);
	QSize s = _mdiArea->size();
	modelVisualizationWindow->resize(s.width(), s.height() * 3 / 5);
	modelVisualizationWindow->show();
	_subWindows.push_back(modelVisualizationWindow);
	globalPOIsList.resize(_numCameras);

	//create camera widget, one window show all camera points
	_cameraModule = new CameraWidget(this, _frameWidth, _frameHeight, _frameRate, _numCameras, _cameraNames);
	connect(_cameraModule, SIGNAL(signalDynamicCalibrationSuccess()), this, SLOT(slotDynamicCalibrationSuccess()));
	// i use the synthread to capture the group frames, so the thread in each cameraWidget will be enable
	QMdiSubWindow* cameraWindow = _mdiArea->addSubWindow(_cameraModule);
	vLayout->addWidget(cameraWindow);

	cameraWindow->resize(s.width(), s.height() * 2 / 5);
	cameraWindow->show();
	_cameraModule->SetWindowSizeAndStartTimer(cameraWindow->width(), cameraWindow->height()); // when we have the width and height, we can show the POIs.
	_subWindows.push_back(cameraWindow);
	_mdiArea->setLayout(vLayout);
	_mdiArea->show();
}


bool Mocap::InitializeOptiTrackCameras()
{
	CameraLibrary_EnableDevelopment();
	CameraManager::X().WaitForInitialization();
	CameraList cameraList;
	_numCameras = cameraList.Count();
	if(_numCameras == 0)
		return false;
	Camera * tempCamera = CameraManager::X().GetCamera();
	_frameWidth = tempCamera->Width();
	_frameHeight = tempCamera->Height();
	_frameRate = tempCamera->FrameRate();
	for(int i = 0; i < _numCameras; i++)
		_cameraNames.append(cameraList[i].Name());
	return true;
}


void Mocap::ReleaseOptiTrackCameras()
{
	CameraManager::X().Shutdown();
}

void Mocap::closeEvent(QCloseEvent *event)
{
	//stop video thread in camerawidget when closing the app
	if(_cameraIntialized)
	{
		if(_cameraModule)
			_cameraModule->StopThread();
	}
}


void Mocap::RefreshTime(QTime)
{
	//这里更新一下录像的时间
}


void Mocap::GetInfo(vector<vector<POI>> POIsList)
{

	//	emit signalInfo(POIsList);
}

// i was supposed to create 2 docks in left and right side of the UI, to store the camera para and calibration/reconstruction para,
// but now i use a tabwidget instead of them for simplicity.
void Mocap::CreateDock()
{
	_leftDock = new QDockWidget(tr("相机属性"),this);
	_rightDock = new QDockWidget(tr("标定-重建参数"),this);
	addDockWidget(Qt::LeftDockWidgetArea, _leftDock);
	addDockWidget(Qt::RightDockWidgetArea, _rightDock);
}

void Mocap::slotDynamicCalibrationSuccess()
{
	_calibrationMessage->setText("dynamic calibration already!!!"); 
}

void Mocap::slotStaticCalibrationSuccess()
{
	_calibrationMessage->setText("static calibration already!!!");  
}

void Mocap::slotFloorCalibrationSuccess()
{
	_calibrationMessage->setText("floor calibration already!!!");  
}


void Mocap::slotMarkerLoss()
{
	_calibrationMessage->setText("Calculate Marker Loss successfully!!!"); 
}

void Mocap::CreateRibbon()
{
	_ribbon = new QTabWidget(this);
	//	int x = ui.mainToolBar->geometry().x();
	//	int y = ui.mainToolBar->geometry().y();
	//	int toolBarHeight = ui.mainToolBar->height();

	int width = this->width();
	//	_ribbon->move(x, y + toolBarHeight);
	_ribbon->move(0, 0);
	_ribbon->resize(width, 90);

	_calibrationWidget = new CalibrationWidget(0, this->width());
	_reconstructionWidget = new ReconstructionWidget(0, this->width());
	_postprocessWidget = new PostprocessWidget(0, this->width());
	_evaluationWidget = new EvaluationWidget(0, this->width());
	QFont font;
	font.setPointSize(11);
	_ribbon->setFont(font);
	_ribbon->addTab(_calibrationWidget, tr("标定"));
	_ribbon->addTab(_reconstructionWidget, tr("重建"));
	_ribbon->addTab(_postprocessWidget, tr("后处理"));
	_ribbon->addTab(_evaluationWidget, "Evaluation");	

	// connect calibartion ribbon signal and slot
	connect(_calibrationWidget->_cameraBtn, SIGNAL(clicked()), this, SLOT(slotCameraClick()));
	connect(_calibrationWidget->_denoiseBtn, SIGNAL(clicked()), this, SLOT(slotDenoiseClick()));
	connect(_calibrationWidget->_captureBtn, SIGNAL(clicked()), this, SLOT(slotPlayClick()));
	connect(_calibrationWidget->_stopBtn, SIGNAL(clicked()), this, SLOT(slotStopClick()));
	connect(_calibrationWidget->_dynamicCalibrationBtn, SIGNAL(clicked()), this, SLOT(slotDynamicClick()));
//	connect(_calibrationWidget->_matlabBtn, SIGNAL(clicked()), this, SLOT(slotCalculatorClick()));
	connect(_calibrationWidget->_staticCalibrationBtn, SIGNAL(clicked()), this, SLOT(slotStaticClick()));
	connect(_calibrationWidget->_floorCalibrationBtn, SIGNAL(clicked()), this, SLOT(slotFloorClick()));
	connect(_calibrationWidget->_loadCalibrationResBtn, SIGNAL(clicked()), this, SLOT(slotLoadResClick()));
	connect(_calibrationWidget->_matlabBtn, SIGNAL(clicked()), this, SLOT(slotMatlabClick()));

	//connect reconstruction ribbon signal and slot
	connect(_reconstructionWidget->_startReconstructionBtn, SIGNAL(clicked()), this, SLOT(slotStartReconstructionClick()));
	connect(_reconstructionWidget->_stopReconstructionBtn, SIGNAL(clicked()), this, SLOT(slotStopReconstructionClick()));
	connect(_reconstructionWidget->_exportPointCloudBtn, SIGNAL(clicked()), this, SLOT(slotExportPointCloudClick()));

	//connect post process ribbon signal and slot
	connect(_postprocessWidget->_defineSkeletonBtn, SIGNAL(clicked()), this, SLOT(slotDefineSkeletonClick()));
	connect(_postprocessWidget->_importSkeletonBtn, SIGNAL(clicked()), this, SLOT(slotImportSkeletonClick()));
	connect(_postprocessWidget->_calculateJointBtn, SIGNAL(clicked()), this, SLOT(slotCalculateJointClick()));
	connect(_postprocessWidget->_exportMocapDataBtn, SIGNAL(clicked()), this, SLOT(slotExportMocapDataClick()));
	connect(_postprocessWidget->_retargetBtn, SIGNAL(clicked()), this, SLOT(slotRetargetClick()));

	//connect evaluation ribbon signal and slot
	connect(_evaluationWidget->_accuracyBtn, SIGNAL(clicked()), this, SLOT(slotAccuracyClick()));
	connect(_evaluationWidget->_markerLossBtn, SIGNAL(clicked()), this, SLOT(slotMarkerLossClick()));
	connect(_evaluationWidget->_aboutBtn, SIGNAL(clicked()), this, SLOT(slotAboutClick()));

	_ribbon->show();
}


void Mocap::CreateNavigation()
{
	_navigation = new QTabWidget(this);
	int x = _ribbon->geometry().x();
	int y = _ribbon->geometry().y();
	int ribbonHeight = _ribbon->height();
	int width = this->width();
	_navigation->move(width - width * NAVIGATION_SCALE, y + ribbonHeight);
	int height = ui.statusBar->geometry().y();
	_navigation->resize(width * NAVIGATION_SCALE, height - y - ribbonHeight - 5);

	_calibrationParaWidget = new CalibrationParaWidget(0, _navigation->width(), _navigation->height());
	_reconstructionParaWidget = new ReconstructionParaWidget(0, _navigation->width(), _navigation->height());
	_cameraParaWidget = new CameraParaWidget(0, _navigation->width(),  _navigation->height());
	QFont font;
	font.setPointSize(10);
	_navigation->setFont(font);

	_navigation->addTab(_cameraParaWidget, tr("相机"));
	_navigation->addTab(_calibrationParaWidget, tr("标定"));
	_navigation->addTab(_reconstructionParaWidget, tr("重建"));
	_navigation->show();
}


/****************slot: handle calibration ribbon*********************/
// init camera
void Mocap::slotCameraClick()
{
	if(InitializeOptiTrackCameras())
	{
		qDebug()<<"init success...";
		_cameraIntialized = true;
		CreateSubWindows();
		//	_synCaptureThread = new SynCaptureThread(this, _frameWidth, _frameHeight, _numCameras);
		//	connect(_synCaptureThread, SIGNAL(finished()), _synCaptureThread, SLOT(deleteLater()));
		/*for(int i = 0; i < 3; i++)
		{
		connect(_synCaptureThread, SIGNAL(signalPOIsReady(vector<vector<POI>>)), _reconstructionModule, SLOT(ReconstructionGetPOIs(vector<vector<POI>>)));
		}*/
		//	connect(_synCaptureThread, SIGNAL(signalPOIsReady(vector<vector<POI>>)), _reconstructionModule, SLOT(ReconstructionGetPOIs(vector<vector<POI>>)));
		//	connect(_synCaptureThread, SIGNAL(signalPOIsReady(vector<vector<POI>>)), this, SLOT(GetInfo(vector<vector<POI>>)));
		//	connect(_synCaptureThread, SIGNAL(signalPOIsReady(int)), _reconstructionModule, SLOT(ReconstructionGetPOIs(int)));
		//	_synCaptureThread->start();
	}
	else qDebug()<<"init failed...";
}

// denoise
void Mocap::slotDenoiseClick()
{
	if(_cameraIntialized)
		_cameraModule->Denoising();
}

// play, start capture
void Mocap::slotPlayClick()
{
	if(_cameraIntialized)
		_cameraModule->PlayLive();
}


void Mocap::slotStopClick()
{

}

// dynamic calibration
void Mocap::slotDynamicClick()
{
	if(_cameraIntialized)
	{
		_cameraModule->StartCalibration();
		//_dynamicCalibrated = true;
	}
}

void Mocap::slotMatlabClick()
{
	if(_cameraIntialized)
	{
		QString cmd = "gocal.exe";
		system(cmd.toStdString().c_str());
		_dynamicCalibrated = true;
	}
}



/**************************************************
Note: static calibration after dynamic calibration
1:camera module performs dynamic calibration;
2:reconstruction module performs static calibration
they are different...
**************************************************/
void Mocap::slotStaticClick()
{
	if(_cameraIntialized && _dynamicCalibrated)
	{
		_reconstructionModule->StaticCalibration();
		_staticCalibrated = true;
	}
}

// calibrate the floor after dynamic calibration
void Mocap::slotFloorClick()
{
	if(_cameraIntialized && _dynamicCalibrated)
	{
		_reconstructionModule->FloorCalibration();
		_staticCalibrated = true;
	}
}



// load calibration result
void Mocap::slotLoadResClick()
{
	if(_cameraIntialized)
	{
		QString  calibrationResultLocation = QFileDialog::getOpenFileName(this, "choose Calibartion result", "");  
		if(!calibrationResultLocation.isEmpty())
		{
			_reconstructionModule->LoadProjectionMatrix(calibrationResultLocation);
			_dynamicCalibrated = true;
		}
	}
}


/*********slot: handle evaluation ribbon****************************************/
void Mocap::slotAccuracyClick()
{
	if(_cameraIntialized && _staticCalibrated)
		_reconstructionModule->CalculateAccuracy();
}


void Mocap::slotMarkerLossClick()
{
	_reconstructionModule->CalculateMarkerLoss();
}


void Mocap::slotAboutClick()
{

}


/*********slot: handle reconstruction ribbon****************************************/
void Mocap::slotStartReconstructionClick()
{
	if(_cameraIntialized && _dynamicCalibrated)
		_reconstructionModule->StartReconstruction();
}

void Mocap::slotStopReconstructionClick()
{

}

void Mocap::slotExportPointCloudClick()
{

}

/*********slot: handle post process ribbon****************************************/
void Mocap::slotImportSkeletonClick()
{

}


void Mocap::slotCalculateJointClick()
{

}


void Mocap::slotDefineSkeletonClick()
{

}


void Mocap::slotExportMocapDataClick()
{

}


void Mocap::slotRetargetClick()
{

}
