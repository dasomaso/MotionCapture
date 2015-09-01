#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QGLWidget>
#include <opencv2/opencv.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ui_ImageWidget.h"

class ImageWidget : public QGLWidget
{
	Q_OBJECT

public:
	ImageWidget(QWidget *parent = 0,  int frameWidth = 1280, int frameHeight = 1024);
	~ImageWidget();

protected:
	IplImage *_imageRef;
	/*!
	 * Resizes the viewport.
	 *
	 * @param width Viewport width.
	 * @param height Viewport height.
	 */
	void resizeGL(int width, int height);

	/*!
	 * Image widget paint event handler.
	 *
	 * @param paintEvent The event to be handled.
	 */
	virtual void paintEvent(QPaintEvent *paintEvent);

	/*!
	 * Sets the viewport up.
	 *
	 * @param width Viewport width.
	 * @param height Viewport height.
	 */
	void setupViewPort(int width, int height);

	/*!
	 * Draws the background image.
	 */
	void drawBackgroundImage();

private:
	Ui::ImageWidget ui;



};

#endif // IMAGEWIDGET_H
