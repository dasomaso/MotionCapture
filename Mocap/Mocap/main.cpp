#include "mocap.h"
#include <QTextCodec>
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	Mocap w;
//	w.setStyleSheet("QDockWidget{ border :6px}");
	w.show();
//	w.setStyleSheet("QDockWidget{ border :3px}");
//	w.setStyleSheet("QPushButton{  background-color: red}");
	return a.exec();
}
