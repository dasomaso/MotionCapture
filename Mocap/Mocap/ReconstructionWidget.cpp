#include "ReconstructionWidget.h"

ReconstructionWidget::ReconstructionWidget(QWidget *parent, int width)
	: QWidget(parent)
{
	ui.setupUi(this);
	_width = width;
	
	//init all ribbon buttons
	Init();
}

ReconstructionWidget::~ReconstructionWidget()
{

}

void ReconstructionWidget::Init()
{
	// create ribbon button
	_startReconstructionBtn = new QToolButton(this);
	_stopReconstructionBtn = new QToolButton(this);
	_exportPointCloudBtn = new QToolButton(this);
	//resize btns
	int toolBtnSize = Para::toolBtnSize;
	_startReconstructionBtn->resize(toolBtnSize, toolBtnSize);
	_stopReconstructionBtn->resize(toolBtnSize, toolBtnSize);
	_exportPointCloudBtn->resize(toolBtnSize, toolBtnSize);

	// put images and text on btns
	QFont font;
	font.setPointSize(9);

	QPixmap p1(":/36images/img/36/play.png");
	_startReconstructionBtn->setFont(font);
	_startReconstructionBtn->setIcon(p1);
	_startReconstructionBtn->setIconSize(p1.size());
	_startReconstructionBtn->setText(tr("开始重建"));
	_startReconstructionBtn->setAutoRaise(true);
	_startReconstructionBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_startReconstructionBtn->setToolTip(tr("开始重建"));

	QPixmap p2(":/36images/img/36/stop.png");
	_stopReconstructionBtn->setFont(font);
	_stopReconstructionBtn->setIcon(p2);
	_stopReconstructionBtn->setIconSize(p2.size());
	_stopReconstructionBtn->setText(tr("停止重建"));
	_stopReconstructionBtn->setAutoRaise(true);
	_stopReconstructionBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_stopReconstructionBtn->setToolTip(tr("停止重建"));

	QPixmap p3(":/36images/img/36/export.png");
	_exportPointCloudBtn->setFont(font);
	_exportPointCloudBtn->setIcon(p3);
	_exportPointCloudBtn->setIconSize(p3.size());
	_exportPointCloudBtn->setText(tr("导出点云"));
	_exportPointCloudBtn->setAutoRaise(true);
	_exportPointCloudBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_exportPointCloudBtn->setToolTip(tr("导出点云"));

	//layout
	_startReconstructionBtn->move(0, 0);
	_stopReconstructionBtn->move(0 + toolBtnSize, 0);
	_exportPointCloudBtn->move(0 + toolBtnSize * 2, 0);



}








