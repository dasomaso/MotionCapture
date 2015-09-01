#ifndef CAMERAPARAWIDGET_H
#define CAMERAPARAWIDGET_H

#include <QWidget>
#include<QGroupBox>
#include <QTableWidget>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QTableWidgetItem>
#include "ui_CameraParaWidget.h"

class CameraParaWidget : public QWidget
{
	Q_OBJECT

public:
	CameraParaWidget(QWidget *parent = 0, int width = 400, int height = 600);
	~CameraParaWidget();

	void Init();

	QGroupBox * _cameraInfomation;
	QGroupBox * _paraSet;

	// para set group control buttons
	QSlider * _threshhold;
	QSlider * _markerSize;
	QComboBox * _videoType;
	QLabel * _lblThreshhold1;
	QLabel* _lblMarkerSize1;
	QLabel * _lblThreshhold2;
	QLabel* _lblMarkerSize2;
	QLabel* _lblVideoType;
	QPushButton * _btnApply;
	QPushButton * _btnReset;

	// camera info control buttons
	QTableWidget * _tableInfo;

public slots:
	void setThreshholdValue(int value);
	void setMarkerValue(int value);

private:
	Ui::CameraParaWidget ui;
	int _width;
	int _height;
};

#endif // CAMERAPARAWIDGET_H
