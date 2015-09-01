#include "EvaluationWidget.h"

EvaluationWidget::EvaluationWidget(QWidget *parent, int width)
	: QWidget(parent)
{
	ui.setupUi(this);
	_width = width;

	//init all ribbon buttons
	Init();
}

EvaluationWidget::~EvaluationWidget()
{

}


void EvaluationWidget::Init()
{
	// create ribbon button
	_accuracyBtn = new QToolButton(this);
	_markerLossBtn = new QToolButton(this);
	_aboutBtn = new QToolButton(this);

	//resize btns
	int toolBtnSize = Para::toolBtnSize;
	_accuracyBtn->resize(toolBtnSize, toolBtnSize);
	_markerLossBtn->resize(toolBtnSize, toolBtnSize);
	_aboutBtn->resize(toolBtnSize, toolBtnSize);

	// put images and text on btns
	QFont font;
	font.setPointSize(9);

	QPixmap p1(":/36images/img/36/accuracy.png");
	_accuracyBtn->setFont(font);
	_accuracyBtn->setIcon(p1);
	_accuracyBtn->setIconSize(p1.size());
	_accuracyBtn->setText(tr("精确度"));
	_accuracyBtn->setAutoRaise(true);
	_accuracyBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_accuracyBtn->setToolTip(tr("精确度"));

	QPixmap p2(":/36images/img/36/markerloss.png");
	_markerLossBtn->setFont(font);
	_markerLossBtn->setIcon(p2);
	_markerLossBtn->setIconSize(p2.size());
	_markerLossBtn->setText(tr("丢点率"));
	_markerLossBtn->setAutoRaise(true);
	_markerLossBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_markerLossBtn->setToolTip(tr("丢点率"));


	QPixmap p3(":/36images/img/36/about.png");
	_aboutBtn->setFont(font);
	_aboutBtn->setIcon(p3);
	_aboutBtn->setIconSize(p3.size());
	_aboutBtn->setText(tr("关于我们"));
	_aboutBtn->setAutoRaise(true);
	_aboutBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_aboutBtn->setToolTip(tr("关于我们"));

	//layout
	_accuracyBtn->move(0, 0);
	_markerLossBtn->move(0 + toolBtnSize, 0);
	_aboutBtn->move(0 + toolBtnSize * 2, 0);

}
