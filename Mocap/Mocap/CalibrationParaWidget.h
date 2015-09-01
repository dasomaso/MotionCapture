#ifndef CALIBRATIONPARAWIDGET_H
#define CALIBRATIONPARAWIDGET_H

#include <QWidget>
#include<QGroupBox>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "ui_CalibrationParaWidget.h"

class CalibrationParaWidget : public QWidget
{
	Q_OBJECT

public:
	CalibrationParaWidget(QWidget *parent = 0, int width = 400, int height = 600);
	~CalibrationParaWidget();
	void Init();

	QGroupBox * _paraSet;
	QGroupBox * _dynamicCalibration;
	QGroupBox * _staticCalibration;
	QGroupBox * _planeCalibration;

	// para set group box control button
	QLabel * _lblFrameInterval;
	QLabel* _lblSampleFrames;
	QLineEdit * _frameInterval;
	QLineEdit* _sampleFrames;
	QPushButton * _btnLoadResult;
	QPushButton * _btnApply;
	QPushButton * _btnReset;
	QPushButton * _btnPlaneCalibration;


private:
	Ui::CalibrationParaWidget ui;
	int _width;
	int _height;
};

#endif // CALIBRATIONPARAWIDGET_H
