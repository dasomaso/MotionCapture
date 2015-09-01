#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPixmap>
#include "Profile.h"
#include "ui_CalibrationWidget.h"

class CalibrationWidget : public QWidget
{
	Q_OBJECT

public:
	CalibrationWidget(QWidget *parent = 0, int width = 0);
	~CalibrationWidget();
	void Init();

	// you can add your ribbon button here. i make it public because i want to interact with them directly in UI. 
	QToolButton * _cameraBtn;
	QToolButton * _denoiseBtn;
	QToolButton * _captureBtn;
	QToolButton * _stopBtn;
	QToolButton * _dynamicCalibrationBtn;
	QToolButton * _matlabBtn;
	QToolButton * _staticCalibrationBtn;
	QToolButton * _loadCalibrationResBtn;
	QToolButton * _floorCalibrationBtn;

private:
	Ui::CalibrationWidget ui;
	int _width;

public slots:
	/*********slot: handle calibration ribbon****************************************/
// when you click the button, CalibrationWidget refer the action to mocap(upper level) to handle.



};

#endif // CALIBRATIONWIDGET_H
