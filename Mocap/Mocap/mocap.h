#ifndef MOCAP_H
#define MOCAP_H

#include <QtGui/QMainWindow>
#include <QMdiArea>
#include <vector>
#include <QMdiSubWindow>
#include <QStringList>
#include <QFileDialog>
#include <cameralibrary.h>
#include <QDockWidget>
#include <QMetaType>
#include <QTabWidget>
#include <QToolButton>
#include <QLabel>
#include "CameraWidget.h"
#include "GUI/ThreeDWidget.h"
#include "AbstractCamera.h"
#include "OptiTrackCamera.h"
#include "SynCaptureThread.h"

#include "CalibrationWidget.h"
#include "ReconstructionWidget.h"
#include "PostprocessWidget.h"
#include "EvaluationWidget.h"

#include "CalibrationParaWidget.h"
#include "CameraParaWidget.h"
#include "ReconstructionParaWidget.h"

#include "Profile.h"
#include "ui_mocap.h"
using namespace std;
using namespace CameraLibrary;
class Mocap : public QMainWindow
{
	Q_OBJECT

public:
	Mocap(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Mocap();
	
	void CreateSubWindows();
	bool InitializeOptiTrackCameras();
	void ReleaseOptiTrackCameras();
	void InitializeSkeleton();
	void LoadProjectionMatrix(QString);
	void CreateDock();
	void CreateRibbon();
	void CreateNavigation();
	
private:
	Ui::MocapClass ui;

	QMdiArea* _mdiArea;
	QDockWidget * _leftDock;
	QDockWidget * _rightDock;
	QLabel * _calibrationMessage;

	/*********ribbon area****************/
	QTabWidget * _ribbon;
	CalibrationWidget * _calibrationWidget;
	ReconstructionWidget * _reconstructionWidget;
	PostprocessWidget * _postprocessWidget;
	EvaluationWidget * _evaluationWidget;

	/*********navigation area****************/
	QTabWidget * _navigation;
	CalibrationParaWidget * _calibrationParaWidget;
	CameraParaWidget * _cameraParaWidget;
	ReconstructionParaWidget * _reconstructionParaWidget;


	//! Vector of cameras.
	vector<AbstractCamera*> _cameras;
	vector<QMdiSubWindow*> _subWindows;
	QStringList _cameraNames;
	int _numCameras;
	ThreeDWidget* _reconstructionModule;
	CameraWidget * _cameraModule;
	SynCaptureThread * _synCaptureThread;
	int _frameRate;
	int _frameWidth;
	int _frameHeight;
	bool _cameraIntialized; // intialize all cameras
	bool _staticCalibrated;
	bool _dynamicCalibrated;
	QString _calibrationResultLocation;
	CvMat * _projectionMatrix;

	//! Clean application before closing
	void closeEvent(QCloseEvent *event);

protected slots:
	
	void  RefreshTime(QTime);
	void GetInfo(vector<vector<POI>>);

	//show message in status bar when get signal(static/dynamic calibration / calculate marker loss compeleted) 
	void slotMarkerLoss();
	void slotDynamicCalibrationSuccess();
	void slotStaticCalibrationSuccess();
	void slotFloorCalibrationSuccess();

	/*********slot: handle calibration ribbon****************************************/
	void slotCameraClick();
	void slotDenoiseClick();  // denoising during the Initilazation phase
	void slotPlayClick();
	void slotStopClick();
	void slotDynamicClick();
	void slotStaticClick();
	void slotFloorClick();
	void slotLoadResClick();
	void slotMatlabClick();

	/*********slot: handle reconstruction ribbon****************************************/
	void slotStartReconstructionClick();
	void slotStopReconstructionClick();
	void slotExportPointCloudClick();

	/*********slot: handle post process ribbon****************************************/
	void slotImportSkeletonClick();
	void slotDefineSkeletonClick();
	void slotExportMocapDataClick();
	void slotCalculateJointClick();
	void slotRetargetClick();

	/*********slot: handle evaluation ribbon****************************************/
	void slotAccuracyClick();
	void slotMarkerLossClick();
	void slotAboutClick();


signals:
//	void signalStopThread();
//	void signalInfo(vector<vector<POI>>);
	void signalInfo(int);
	
};

#endif // MOCAP_H
