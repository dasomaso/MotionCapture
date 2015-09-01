#include "POISemanticSelectionDialog.h"

POISemanticSelectionDialog::POISemanticSelectionDialog(QWidget *parent, POI *POI, QPoint mouseEventPosition)
	: QDialog(parent,Qt::Tool)
{
	ui.setupUi(this);
	_semanticList.append("Hips");
	_semanticList.append("Chest");
	_semanticList.append("Neck");
	_semanticList.append("Head");
	_semanticList.append("Head.end");
	_semanticList.append("LeftCollar");
	_semanticList.append("LeftUpArm");
	_semanticList.append("LeftLowArm");
	_semanticList.append("LeftHand");
	_semanticList.append("LeftHand.end");
	_semanticList.append("RightCollar");
	_semanticList.append("RightUpArm");
	_semanticList.append("RightLowArm");
	_semanticList.append("RightHand");
	_semanticList.append("RightHand.end");
	_semanticList.append("LeftUpLeg");
	_semanticList.append("LeftLowLeg");
	_semanticList.append("LeftFoot");
	_semanticList.append("LeftFoot.end");
	_semanticList.append("RightUpLeg");
	_semanticList.append("RightLowLeg");
	_semanticList.append("RightFoot");
	_semanticList.append("RightFoot.end");

	_POI = POI;
	CreateMainLayout();

	if (!POI->isInitialized())
	{
		//--- First Semantic selected
		_POISemanticsCombo->setCurrentIndex(0);
		RefreshPOISemantic();
	}
	else
	{
		//int index = _POISemanticsCombo->findText(POI->getSemantic());
		//_POISemanticsCombo->setCurrentIndex(index);
		_POISemanticsCombo->setCurrentIndex(0);
	}

	move(mouseEventPosition);
	
}

POISemanticSelectionDialog::~POISemanticSelectionDialog()
{

}

void POISemanticSelectionDialog::CreateMainLayout()
{

	QString POIDesc = QString("POI at (%1, %2)").arg(_POI->_coordinates2d.x).arg(_POI->_coordinates2d.y);
	setWindowTitle(POIDesc);

	_POISemanticsCombo = new QComboBox();
	_POISemanticsCombo->addItems(_semanticList);
	connect(_POISemanticsCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(RefreshPOISemantic()));

	_okButton = new QPushButton("Ok");
	connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));

	_mainLayout = new QFormLayout();
	_mainLayout->addRow(new QLabel("Semantic:"), _POISemanticsCombo);
	_mainLayout->addRow(_okButton);
	_mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	setLayout(_mainLayout);
}


void POISemanticSelectionDialog::showEvent(QShowEvent * event) {

	//---Where should we put the dialog?
	QDesktopWidget* desktopWidget = QApplication::desktop();
	int screenNumber = desktopWidget->primaryScreen();
	int ScreenCenterX = desktopWidget->screenGeometry(screenNumber).width() / 2;
	int ScreenCenterY = desktopWidget->screenGeometry(screenNumber).height() / 2;

	if (x() > ScreenCenterX) {
		move(x() - frameGeometry().width(), y());
	}
	if (y() > ScreenCenterY) {
		move(x(), y() - frameGeometry().height());
	}
}

void POISemanticSelectionDialog::RefreshPOISemantic()
{
	_POI->_semantic = _POISemanticsCombo->currentText();
}

