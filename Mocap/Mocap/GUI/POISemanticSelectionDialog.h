#ifndef POISEMANTICSELECTIONDIALOG_H
#define POISEMANTICSELECTIONDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QStringList>
#include <QComboBox>
#include <QPushButton>
#include <QDesktopWidget>
#include <QLabel>
#include "ui_POISemanticSelectionDialog.h"
#include "POI.h"

class POISemanticSelectionDialog : public QDialog
{
	Q_OBJECT

public:
	POISemanticSelectionDialog(QWidget *parent = 0, POI *poi = NULL, QPoint mouseEventPosition = QPoint(0, 0));
	~POISemanticSelectionDialog();
	
	/*!
	 * Creates the main layout of the "POI" semantic selection dialog.
	 *
	 * @param poiSemanticTypes A list with the "POI" semantic types.
	 */
	void CreateMainLayout();

private:
	Ui::POISemanticSelectionDialog ui;

	//! Point of interest.
	POI* _POI;
	//! Form layout.
	QFormLayout* _mainLayout;

	//! Combobox with the "POI" semantics.
	QComboBox* _POISemanticsCombo;
	
	//! OK button.
	QPushButton* _okButton;

	QStringList _semanticList;
	protected:
	/*!
	 * The widget show event handler.
	 *
	 * @param event The event to be handled.
	 */
	void showEvent(QShowEvent * event );

private slots:

	/*!
	 * Slot to refresh POI Semantic
	 */
	void RefreshPOISemantic();
};

#endif // POISEMANTICSELECTIONDIALOG_H
