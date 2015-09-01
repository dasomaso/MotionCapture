#ifndef RECONSTRUCTIONWIDGET_H
#define RECONSTRUCTIONWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPixmap>
#include "Profile.h"
#include "ui_ReconstructionWidget.h"

class ReconstructionWidget : public QWidget
{
	Q_OBJECT

public:
	ReconstructionWidget(QWidget *parent = 0, int width = 0);
	~ReconstructionWidget();

	void Init();

	QToolButton * _startReconstructionBtn;
	QToolButton * _stopReconstructionBtn;
	QToolButton * _exportPointCloudBtn;

private:
	Ui::ReconstructionWidget ui;
	int _width;

public slots:
	/*********slot: handle calibration ribbon****************************************/
	// when you click the button, CalibrationWidget refer the action to mocap(upper level) to handle.
};

#endif // RECONSTRUCTIONWIDGET_H
