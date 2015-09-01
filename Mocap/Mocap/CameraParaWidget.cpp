#include "CameraParaWidget.h"

CameraParaWidget::CameraParaWidget(QWidget *parent, int width, int height)
	: QWidget(parent)
{
	ui.setupUi(this);
	_width = width;
	_height = height;
	_cameraInfomation = NULL;
	_paraSet = NULL;
	Init();
}

CameraParaWidget::~CameraParaWidget()
{
	if(!_cameraInfomation)
		delete _cameraInfomation;
	if(!_paraSet)
		delete _paraSet;

}

void CameraParaWidget::Init()
{	
	//align group box
	_paraSet = new QGroupBox(tr("参数设置"), this);
	_paraSet->resize(_width * 0.9, _height / 2 - 20);
	_paraSet->move(_width * 0.05, 10);

	_cameraInfomation = new QGroupBox(tr("相机信息"),this);
	_cameraInfomation->resize(_width * 0.9, _height / 2 - 30);
	_cameraInfomation->move(_width * 0.05, _height / 2);

	int ctrlBtnWidth = _paraSet->width() * 0.35;
	int ctrlBtnHeight = _paraSet->height() * 0.5 * 0.25;
	
	//align para set group, when you move the slider or choose the combobox, you need to erase the information in the table
	_lblThreshhold1 = new QLabel(tr("marker检测阈值:"), _paraSet);
	_lblMarkerSize1 = new QLabel(tr("marker显示大小:"), _paraSet);
	_lblThreshhold2 = new QLabel(tr("200"), _paraSet);
	_lblMarkerSize2 = new QLabel(tr("15"), _paraSet);
	_lblVideoType = new QLabel(tr("图像采集模式:"), _paraSet);
	_threshhold = new QSlider(Qt::Horizontal, _paraSet);
	_markerSize = new QSlider(Qt::Horizontal, _paraSet);
	_videoType = new QComboBox(_paraSet);
	_btnApply = new QPushButton(tr("apply"),_paraSet);
	_btnReset = new QPushButton(tr("reset"),_paraSet);
	_threshhold->setMinimum(0);
	_threshhold->setMaximum(255);
	_threshhold->setValue(200);
	_markerSize->setMinimum(0);
	_markerSize->setMaximum(15);
	_markerSize->setValue(15);
	_videoType->insertItem(0, "Segment Mode");
	_videoType->insertItem(1, "Object Mode");
	_videoType->insertItem(2, "Precision Mode");
	_videoType->insertItem(3, "MJPEG Mode");

	connect(_threshhold, SIGNAL(valueChanged(int)), this, SLOT(setThreshholdValue(int))); 
	connect(_markerSize, SIGNAL(valueChanged(int)), this, SLOT(setMarkerValue(int))); 


	_lblThreshhold1->resize(ctrlBtnWidth, ctrlBtnHeight);
	_lblMarkerSize1->resize(ctrlBtnWidth, ctrlBtnHeight);
	_lblThreshhold2->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.6);
	_lblMarkerSize2->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.6);
	_lblVideoType->resize(ctrlBtnWidth, ctrlBtnHeight);
	_threshhold->resize(ctrlBtnWidth, ctrlBtnHeight * 0.6);
	_markerSize->resize(ctrlBtnWidth, ctrlBtnHeight * 0.6);
	_videoType->resize(ctrlBtnWidth, ctrlBtnHeight * 0.6);
	_btnApply->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.6);
	_btnReset->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.6);

	_lblThreshhold1->move(_paraSet->width() * 0.05, ctrlBtnHeight * 0.25);
	_lblMarkerSize1->move(_paraSet->width() * 0.05, ctrlBtnHeight * 0.5 + ctrlBtnHeight);
	_lblThreshhold2->move(_paraSet->width() * 0.05 + ctrlBtnWidth * 2, ctrlBtnHeight * 0.25 + 5);
	_lblMarkerSize2->move(_paraSet->width() * 0.05 + ctrlBtnWidth * 2, ctrlBtnHeight * 0.5 + ctrlBtnHeight + 5);
	_lblVideoType->move(_paraSet->width() * 0.05, ctrlBtnHeight * 0.75 + ctrlBtnHeight * 2);
	_threshhold->move(_paraSet->width() * 0.05 + ctrlBtnWidth, ctrlBtnHeight * 0.25 + 5);
	_markerSize->move(_paraSet->width() * 0.05 + ctrlBtnWidth, ctrlBtnHeight * 0.5 + ctrlBtnHeight + 5);
	_videoType->move(_paraSet->width() * 0.05 + ctrlBtnWidth, ctrlBtnHeight * 0.75 + ctrlBtnHeight * 2 + 5);
	_btnApply->move(_paraSet->width() * 0.05 + 1.5 * ctrlBtnWidth + 3, ctrlBtnHeight * 4);
	_btnReset->move(_paraSet->width() * 0.05 + ctrlBtnWidth - 3, ctrlBtnHeight * 4);

	//align camera info control button, you need to add all camera information in this table when init cameras
	_tableInfo = new QTableWidget(_cameraInfomation);
	_tableInfo->setColumnCount(6);
	_tableInfo->resize(_cameraInfomation->width() * 0.9, _cameraInfomation->height() * 0.9);
	_tableInfo->move(_cameraInfomation->width() * 0.05, _cameraInfomation->height() * 0.05);
	QStringList list;
	list << tr("相机名称") << tr("帧率") << tr("分辨率") <<tr("marker阈值") << tr("marker大小") << tr("相机模式");
	_tableInfo->setHorizontalHeaderLabels(list);
//	_tableInfo->setItem(0, 0, new QTableWidgetItem("zzz"));
	//_tableInfo

}

void CameraParaWidget::setThreshholdValue(int value)
{
	_lblThreshhold2->setText(QString::number(value, 10));
}

void CameraParaWidget::setMarkerValue(int value)
{
	_lblMarkerSize2->setText(QString::number(value, 10));
}


