#include "PostprocessWidget.h"

PostprocessWidget::PostprocessWidget(QWidget *parent, int width)
	: QWidget(parent)
{
	ui.setupUi(this);
	_width = width;

	//init all ribbon buttons
	Init();
}

PostprocessWidget::~PostprocessWidget()
{

}

void PostprocessWidget::Init()
{
	// create ribbon button
	_importSkeletonBtn = new QToolButton(this);
	_defineSkeletonBtn = new QToolButton(this);
	_exportMocapDataBtn = new QToolButton(this);
	_calculateJointBtn = new QToolButton(this);
	_labelBtn = new QToolButton(this);
	_retargetBtn = new QToolButton(this);

	//resize btns
	int toolBtnSize = Para::toolBtnSize;
	_importSkeletonBtn->resize(toolBtnSize, toolBtnSize);
	_defineSkeletonBtn->resize(toolBtnSize, toolBtnSize);
	_exportMocapDataBtn->resize(toolBtnSize, toolBtnSize);
	_calculateJointBtn->resize(toolBtnSize, toolBtnSize);
	_labelBtn->resize(toolBtnSize, toolBtnSize);
	_retargetBtn->resize(toolBtnSize, toolBtnSize);

	// put images and text on btns
	QFont font;
	font.setPointSize(9);

	QPixmap p1(":/36images/img/36/import.png");
	_importSkeletonBtn->setFont(font);
	_importSkeletonBtn->setIcon(p1);
	_importSkeletonBtn->setIconSize(p1.size());
	_importSkeletonBtn->setText(tr("导入骨架"));
	_importSkeletonBtn->setAutoRaise(true);
	_importSkeletonBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_importSkeletonBtn->setToolTip(tr("导入骨架"));

	QPixmap p2(":/36images/img/36/skeleton.png");
	_defineSkeletonBtn->setFont(font);
	_defineSkeletonBtn->setIcon(p2);
	_defineSkeletonBtn->setIconSize(p2.size());
	_defineSkeletonBtn->setText(tr("定义骨架"));
	_defineSkeletonBtn->setAutoRaise(true);
	_defineSkeletonBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_defineSkeletonBtn->setToolTip(tr("定义骨架"));

	QPixmap p3(":/36images/img/36/export.png");
	_exportMocapDataBtn->setFont(font);
	_exportMocapDataBtn->setIcon(p3);
	_exportMocapDataBtn->setIconSize(p3.size());
	_exportMocapDataBtn->setText(tr("导出数据"));
	_exportMocapDataBtn->setAutoRaise(true);
	_exportMocapDataBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_exportMocapDataBtn->setToolTip(tr("导出数据"));

	QPixmap p4(":/36images/img/36/joint.png");
	_calculateJointBtn->setFont(font);
	_calculateJointBtn->setIcon(p4);
	_calculateJointBtn->setIconSize(p4.size());
	_calculateJointBtn->setText(tr("计算关节"));
	_calculateJointBtn->setAutoRaise(true);
	_calculateJointBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_calculateJointBtn->setToolTip(tr("计算关节"));

	QPixmap p5(":/36images/img/36/label.png");
	_labelBtn->setFont(font);
	_labelBtn->setIcon(p5);
	_labelBtn->setIconSize(p5.size());
	_labelBtn->setText(tr("标注数据"));
	_labelBtn->setAutoRaise(true);
	_labelBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_labelBtn->setToolTip(tr("标注数据"));

	QPixmap p6(":/36images/img/36/retarget.png");
	_retargetBtn->setFont(font);
	_retargetBtn->setIcon(p6);
	_retargetBtn->setIconSize(p6.size());
	_retargetBtn->setText(tr("重定向"));
	_retargetBtn->setAutoRaise(true);
	_retargetBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_retargetBtn->setToolTip(tr("重定向"));

	//layout
	_defineSkeletonBtn->move(0, 0);
	_importSkeletonBtn->move(0 + toolBtnSize, 0);
	_calculateJointBtn->move(0 + toolBtnSize * 2, 0);
	_labelBtn->move(0 + toolBtnSize * 3, 0);
	_retargetBtn->move(0 + toolBtnSize * 4, 0);
	_exportMocapDataBtn->move(0 + toolBtnSize * 5, 0);

}
