#ifndef RECONSTRUCTIONPARAWIDGET_H
#define RECONSTRUCTIONPARAWIDGET_H

#include <QWidget>
#include<QGroupBox>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "Profile.h"
#include "ui_ReconstructionParaWidget.h"

class ReconstructionParaWidget : public QWidget
{
	Q_OBJECT

public:
	ReconstructionParaWidget(QWidget *parent = 0, int width = 400, int height = 600);
	~ReconstructionParaWidget();
	void Init();

	QGroupBox * _paraSet;
	QGroupBox * _functionArea;

	// para set group box control button
	QLabel * _lblReprojectionThreshold; // 对应REPROJECTION_THRESHOLD
	QLabel* _lblMarkerOnLineThreshold;  // 对应MARKER_ON_LINE_THRESHOLD
	QLineEdit * _reprojectionThreshold;
	QLineEdit* _markerOnLineThreshold;
	QPushButton * _btnApply;
	QPushButton * _btnReset;

	// function group box control button
	QComboBox * _exportType;
	QPushButton * _btnExport;

	public slots:
		void ApplyThreshold();
		void ResetThreshold();


private:
	Ui::ReconstructionParaWidget ui;
	int _width;
	int _height;
};

#endif // RECONSTRUCTIONPARAWIDGET_H
