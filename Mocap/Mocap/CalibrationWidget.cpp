#include "CalibrationWidget.h"

CalibrationWidget::CalibrationWidget(QWidget *parent, int width )
	: QWidget(parent)
{
	ui.setupUi(this);
	_width = width;
	
	//init all ribbon buttons
	Init();
}

CalibrationWidget::~CalibrationWidget()
{

}



void CalibrationWidget::Init()
{
	// create ribbon button
	_cameraBtn = new QToolButton(this);
	_denoiseBtn = new QToolButton(this);
	_captureBtn = new QToolButton(this);
	_stopBtn = new QToolButton(this);
	_dynamicCalibrationBtn = new QToolButton(this);
	_matlabBtn = new QToolButton(this);
	_staticCalibrationBtn = new QToolButton(this);
	_floorCalibrationBtn = new QToolButton(this);
	_loadCalibrationResBtn = new QToolButton(this);

	//resize btns
	int tootBtnSize = Para::toolBtnSize;
	_cameraBtn->resize(tootBtnSize, tootBtnSize);
	_denoiseBtn->resize(tootBtnSize, tootBtnSize);
	_captureBtn->resize(tootBtnSize, tootBtnSize);
	_stopBtn->resize(tootBtnSize, tootBtnSize);
	_dynamicCalibrationBtn->resize(tootBtnSize, tootBtnSize);
	_matlabBtn->resize(tootBtnSize, tootBtnSize);
	_staticCalibrationBtn->resize(tootBtnSize, tootBtnSize);
	_floorCalibrationBtn->resize(tootBtnSize, tootBtnSize);
	_loadCalibrationResBtn->resize(tootBtnSize, tootBtnSize);

	// put images and text on btns
	QFont font;
	font.setPointSize(9);

	QPixmap p1(":/36images/img/36/camera.png");
	_cameraBtn->setFont(font);
	_cameraBtn->setIcon(p1);
	_cameraBtn->setIconSize(p1.size());
	_cameraBtn->setText(tr("初始相机"));
	_cameraBtn->setAutoRaise(true);
	_cameraBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_cameraBtn->setToolTip(tr("初始相机"));

	QPixmap p2(":/36images/img/36/denoise.png");
	_denoiseBtn->setFont(font);
	_denoiseBtn->setIcon(p2);
	_denoiseBtn->setIconSize(p2.size());
	_denoiseBtn->setText(tr("去除噪声"));
	_denoiseBtn->setAutoRaise(true);
	_denoiseBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_denoiseBtn->setToolTip(tr("去除噪声"));


	QPixmap p3(":/36images/img/36/play.png");
	_captureBtn->setFont(font);
	_captureBtn->setIcon(p3);
	_captureBtn->setIconSize(p3.size());
	_captureBtn->setText(tr("采集图像"));
	_captureBtn->setAutoRaise(true);
	_captureBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_captureBtn->setToolTip(tr("采集图像"));

	QPixmap p4(":/36images/img/36/stop.png");
	_stopBtn->setFont(font);
	_stopBtn->setIcon(p4);
	_stopBtn->setIconSize(p4.size());
	_stopBtn->setText(tr("停止采集"));
	_stopBtn->setAutoRaise(true);
	_stopBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_stopBtn->setToolTip(tr("停止采集"));

	QPixmap p5(":/36images/img/36/dynamiccalibration.png");
	_dynamicCalibrationBtn->setFont(font);
	_dynamicCalibrationBtn->setIcon(p5);
	_dynamicCalibrationBtn->setIconSize(p5.size());
	_dynamicCalibrationBtn->setText(tr("动态标定"));
	_dynamicCalibrationBtn->setAutoRaise(true);
	_dynamicCalibrationBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_dynamicCalibrationBtn->setToolTip(tr("动态标定"));

	QPixmap p6(":/36images/img/36/staticcalibration.png");
	_staticCalibrationBtn->setFont(font);
	_staticCalibrationBtn->setIcon(p6);
	_staticCalibrationBtn->setIconSize(p6.size());
	_staticCalibrationBtn->setText(tr("静态标定"));
	_staticCalibrationBtn->setAutoRaise(true);
	_staticCalibrationBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_staticCalibrationBtn->setToolTip(tr("静态标定"));

	QPixmap p7(":/36images/img/36/folder.png");
	_loadCalibrationResBtn->setFont(font);
	_loadCalibrationResBtn->setIcon(p7);
	_loadCalibrationResBtn->setIconSize(p7.size());
	_loadCalibrationResBtn->setText(tr("加载结果"));
	_loadCalibrationResBtn->setAutoRaise(true);
	_loadCalibrationResBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_loadCalibrationResBtn->setToolTip(tr("加载结果"));

	QPixmap p8(":/36images/img/36/calculator.png");
	_matlabBtn->setFont(font);
	_matlabBtn->setIcon(p8);
	_matlabBtn->setIconSize(p8.size());
	_matlabBtn->setText(tr("计算矩阵"));
	_matlabBtn->setAutoRaise(true);
	_matlabBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_matlabBtn->setToolTip(tr("计算矩阵"));

	QPixmap p9(":/36images/img/36/floor.png");
	_floorCalibrationBtn->setFont(font);
	_floorCalibrationBtn->setIcon(p9);
	_floorCalibrationBtn->setIconSize(p9.size());
	_floorCalibrationBtn->setText(tr("地板标定"));
	_floorCalibrationBtn->setAutoRaise(true);
	_floorCalibrationBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_floorCalibrationBtn->setToolTip(tr("地板标定"));


	//layout
	_cameraBtn->move(0, 0);
	_denoiseBtn->move(0 + tootBtnSize, 0);
	_captureBtn->move(0 + tootBtnSize * 2, 0);
	_stopBtn->move(0 + tootBtnSize * 3, 0);
	_dynamicCalibrationBtn->move(0 + tootBtnSize * 4, 0);
	_matlabBtn->move(0 + tootBtnSize * 5, 0);
	_staticCalibrationBtn->move(0 + tootBtnSize * 6, 0);
	_floorCalibrationBtn->move(0 + tootBtnSize * 7, 0);
	_loadCalibrationResBtn->move(0 + tootBtnSize * 8, 0);
}