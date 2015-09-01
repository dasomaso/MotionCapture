#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMetaType>
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>
#include <fstream>
#include "ui_CameraWidget.h"
#include "Threads/VideoController.h"
#include "POIsImageWidget.h"
#include "POISemanticSelectionDialog.h"
#include "SynCaptureThread.h"
using namespace std;
class CameraWidget : public QWidget
{
	Q_OBJECT

public:
	CameraWidget(QWidget *parent, int frameWidth, int frameHeight, int frameRate, int numCameras, QStringList cameraNames);
	~CameraWidget();
	void createMainLayout();

	bool eventFilter(QObject *target, QEvent *event);

	void StopThread();
	void Denoising();
	void StartCalibration();
	void PlayLive(); 
	void Init();
	void InitSync();

	void SetWindowSizeAndStartTimer(int w, int h);
private:
	Ui::CameraWidget ui;
	vector<VideoController*> _videoThreadList;
	SynCaptureThread * _synCaptureThread;
	
	POIsImageWidget* _POIsImageWidget;
	QVBoxLayout* _mainLayout;
	QTimer * _cameraTimer;
	int _frameWidth;
	int _frameHeight;
	int _frameRate;
	int _numCameras;
	QStringList _cameraNames;
//	vector<vector<POI>> _POIsList;
	bool * _calibratedList;
	ofstream outfile;

	public slots:
		
		void GetPOIsFromCamera(vector<POI> POIs, int cameraIndex);		
		void slotTimeout();
		void slotCalibrationReady(int cameraIndex);

// i use the synthread to capture the group frames, so there will be only one thread in camerawidget
		void GetPOIsListSync(vector<vector<POI>> POIsList);
		void slotCalibrationReadySync();

signals:
	//	void signalPOIsReady(vector<POI>, int );
		void signalDynamicCalibrationSuccess();

};

#endif // CAMERAWIDGET_H
