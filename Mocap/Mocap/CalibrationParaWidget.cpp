#include "CalibrationParaWidget.h"

CalibrationParaWidget::CalibrationParaWidget(QWidget *parent, int width, int height)
	: QWidget(parent)
{
	ui.setupUi(this);
	_width = width;
	_height = height;
	Init();

}

CalibrationParaWidget::~CalibrationParaWidget()
{

}

void CalibrationParaWidget::Init()
{
	//align group box
	_paraSet = new QGroupBox(tr("参数设置"), this);
	_paraSet->resize(_width * 0.9, _height / 5);
	_paraSet->move(_width * 0.05, 10);

	_dynamicCalibration = new QGroupBox(tr("动态标定"),this);
	_dynamicCalibration->resize(_width * 0.9, _height / 5);
	_dynamicCalibration->move(_width * 0.05, _height / 5 * 1.2);

	_staticCalibration = new QGroupBox(tr("静态标定"),this);
	_staticCalibration->resize(_width * 0.9, _height / 5);
	_staticCalibration->move(_width * 0.05, _height / 5 * 2.2);

	_planeCalibration = new QGroupBox(tr("地板标定"),this);
	_planeCalibration->resize(_width * 0.9, _height / 5);
	_planeCalibration->move(_width * 0.05, _height / 5 * 3.2);

	//align para set group
	_lblFrameInterval = new QLabel(tr("帧间距:"), _paraSet);
	_lblSampleFrames = new QLabel(tr("采样帧数量:"), _paraSet);
	_frameInterval = new QLineEdit(_paraSet);
	_sampleFrames = new QLineEdit(_paraSet);
	_btnLoadResult = new QPushButton(tr("加载标定结果"),_paraSet);
	_btnApply = new QPushButton(tr("apply"),_paraSet);
	_btnReset = new QPushButton(tr("reset"),_paraSet);

	int ctrlBtnWidth = _paraSet->width() * 0.35;
	int ctrlBtnHeight = _paraSet->height() * 0.25;

	_lblFrameInterval->resize(ctrlBtnWidth, ctrlBtnHeight);
	_lblSampleFrames->resize(ctrlBtnWidth, ctrlBtnHeight);
	_frameInterval->resize(ctrlBtnWidth, ctrlBtnHeight * 0.6);
	_sampleFrames->resize(ctrlBtnWidth, ctrlBtnHeight * 0.6);
	_btnLoadResult->resize(ctrlBtnWidth * 0.8, ctrlBtnHeight * 0.8);
	_btnApply->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.8);
	_btnReset->resize(ctrlBtnWidth * 0.5, ctrlBtnHeight * 0.8);

	_lblFrameInterval->move(_paraSet->width() * 0.05, ctrlBtnHeight * 0.25);
	_lblSampleFrames->move(_paraSet->width() * 0.05, ctrlBtnHeight * 0.5 + ctrlBtnHeight);
	_frameInterval->move(_paraSet->width() * 0.05 + ctrlBtnWidth, ctrlBtnHeight * 0.45);
	_sampleFrames->move(_paraSet->width() * 0.05 + ctrlBtnWidth, ctrlBtnHeight * 0.7 + ctrlBtnHeight);

	_btnLoadResult->move(_paraSet->width() * 0.05, ctrlBtnHeight * 2.5);
	_btnApply->move(_paraSet->width() * 0.05 + 1.5 * ctrlBtnWidth + 3, ctrlBtnHeight * 2.5);
	_btnReset->move(_paraSet->width() * 0.05 + ctrlBtnWidth - 3, ctrlBtnHeight * 2.5);

}