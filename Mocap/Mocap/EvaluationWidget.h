#ifndef EVALUATIONWIDGET_H
#define EVALUATIONWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPixmap>
#include "Profile.h"
#include "ui_EvaluationWidget.h"

class EvaluationWidget : public QWidget
{
	Q_OBJECT

public:
	EvaluationWidget(QWidget *parent = 0, int width = 0);
	~EvaluationWidget();
	void Init();

	QToolButton * _accuracyBtn;
	QToolButton * _markerLossBtn;
	QToolButton * _aboutBtn;

private:
	Ui::EvaluationWidget ui;
	int _width;


public slots:
	/*********slot: handle calibration ribbon****************************************/
	// when you click the button, CalibrationWidget refer the action to mocap(upper level) to handle.


};

#endif // EVALUATIONWIDGET_H
