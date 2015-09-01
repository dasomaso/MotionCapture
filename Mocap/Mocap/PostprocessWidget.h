#ifndef POSTPROCESSWIDGET_H
#define POSTPROCESSWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPixmap>
#include "Profile.h"
#include "ui_PostprocessWidget.h"

class PostprocessWidget : public QWidget
{
	Q_OBJECT

public:
	PostprocessWidget(QWidget *parent = 0, int width = 0);
	~PostprocessWidget();

	void Init();

	QToolButton * _importSkeletonBtn;
	QToolButton * _defineSkeletonBtn;
	QToolButton * _exportMocapDataBtn;
	QToolButton * _calculateJointBtn;
	QToolButton * _labelBtn;
	QToolButton * _retargetBtn;
private:
	Ui::PostprocessWidget ui;
	int _width;


public slots:
	/*********slot: handle calibration ribbon****************************************/
	// when you click the button, CalibrationWidget refer the action to mocap(upper level) to handle.
	
};

#endif // POSTPROCESSWIDGET_H
