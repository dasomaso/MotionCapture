#include "ReconstructionParaWidget.h"

ReconstructionParaWidget::ReconstructionParaWidget(QWidget *parent, int width, int height )
	: QWidget(parent)
{
	ui.setupUi(this);
	_width = width;
	_height = height;
	Init();
}

ReconstructionParaWidget::~ReconstructionParaWidget()
{

}

void ReconstructionParaWidget::Init()
{
	// align all group boxes
	_paraSet = new QGroupBox(tr("参数设置"), this);
	_paraSet->resize(_width * 0.9, _height / 2 - 20);
	_paraSet->move(_width * 0.05, 10);

	_functionArea = new QGroupBox(tr("功能区域"),this);
	_functionArea->resize(_width * 0.9, _height / 2 - 30);
	_functionArea->move(_width * 0.05, _height / 2);


	//align para set group
	_lblReprojectionThreshold = new QLabel(tr("重投影阈值:"), _paraSet);
	_lblMarkerOnLineThreshold = new QLabel(tr("点线距阈值:"), _paraSet);
	_reprojectionThreshold = new QLineEdit(_paraSet);
	_markerOnLineThreshold = new QLineEdit(_paraSet);
	_btnApply = new QPushButton(tr("apply"),_paraSet);
	_btnReset = new QPushButton(tr("reset"),_paraSet);

	int ctrlBtnWidth = _paraSet->width() * 0.35;
	int ctrlBtnHeight = _paraSet->height() * 0.6 * 0.25;

	_lblReprojectionThreshold->resize(ctrlBtnWidth, ctrlBtnHeight);
	_lblMarkerOnLineThreshold->resize(ctrlBtnWidth, ctrlBtnHeight);
	_reprojectionThreshold->resize(ctrlBtnWidth, ctrlBtnHeight * 0.6);
	_markerOnLineThreshold->resize(ctrlBtnWidth, ctrlBtnHeight * 0.6);
	_btnApply->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.5);
	_btnReset->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.5);

	_lblReprojectionThreshold->move(_paraSet->width() * 0.05, ctrlBtnHeight * 0.25);
	_lblMarkerOnLineThreshold->move(_paraSet->width() * 0.05, ctrlBtnHeight * 0.5 + ctrlBtnHeight);
	_reprojectionThreshold->move(_paraSet->width() * 0.05 + ctrlBtnWidth, ctrlBtnHeight * 0.45);
	_markerOnLineThreshold->move(_paraSet->width() * 0.05 + ctrlBtnWidth, ctrlBtnHeight * 0.7 + ctrlBtnHeight);
	_btnApply->move(_paraSet->width() * 0.05 + 1.5 * ctrlBtnWidth + 3, ctrlBtnHeight * 2.5);
	_btnReset->move(_paraSet->width() * 0.05 + ctrlBtnWidth - 3, ctrlBtnHeight * 2.5);


	//align para set group
	_exportType = new QComboBox(_functionArea);
	_btnExport = new QPushButton(tr("导出"), _functionArea);
	_exportType->insertItem(0, "c3d");
	_exportType->insertItem(1, "txt");
	_exportType->insertItem(2, "excel");
	_exportType->insertItem(3, "fbx");

	_exportType->resize(ctrlBtnWidth, ctrlBtnHeight * 0.5);
	_btnExport->resize(ctrlBtnWidth, ctrlBtnHeight * 0.5);

	_exportType->move(_functionArea->width() * 0.05, ctrlBtnHeight * 0.3);
	_btnExport->move(_functionArea->width() * 0.05 + ctrlBtnWidth + 10, ctrlBtnHeight * 0.3);

	
	_markerOnLineThreshold->setText(QString::number(Para::markerOnLineThreshold));
	_reprojectionThreshold->setText(QString::number(Para::reprojectionThreshold));

	connect(_btnApply, SIGNAL(clicked()), this, SLOT(ApplyThreshold()));
	connect(_btnReset, SIGNAL(clicked()), this, SLOT(ResetThreshold()));
}

void ReconstructionParaWidget::ApplyThreshold()
{
	int threshold1 = _markerOnLineThreshold->text().toInt();
	int threshold2 = _reprojectionThreshold->text().toInt();
	Para::markerOnLineThreshold = threshold1;
	Para::reprojectionThreshold = threshold2;
}

void ReconstructionParaWidget::ResetThreshold()
{
	Para::markerOnLineThreshold = 3;
	Para::reprojectionThreshold = 3;
	_markerOnLineThreshold->setText(QString::number(Para::markerOnLineThreshold));
	_reprojectionThreshold->setText(QString::number(Para::reprojectionThreshold));
}


