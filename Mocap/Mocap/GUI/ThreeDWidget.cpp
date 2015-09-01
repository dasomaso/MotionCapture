#include "ThreeDWidget.h"

ThreeDWidget::ThreeDWidget(QWidget *parent, int frameRate, int frameWidth, int frameHeight, int numCamras)
	: QGLWidget(QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer), parent), _floorRows(20), _floorColumns(20), _squareSize(1.0),
	_rotationX(0.0), _rotationY(0.0)
{
	ui.setupUi(this);

	_frameHeight = frameHeight;
	_frameWidth = frameWidth;
	_frameRate = frameRate;
	_numCameras = numCamras;
	_eye.x = 0.0;
	_eye.y = 5.0;
	_eye.z = -5.0;

	_center.x = 0.0;
	_center.y = 0.0;
	_center.z = 0.0;

	_up.x = 0.0;
	_up.y = 1.0;
	_up.z = 0.0;
	//_cameraCenters = new Vector3f[_numCameras];

	QString windowTitle(tr("3D重建窗口"));
	setWindowTitle(windowTitle);

	_calibrated = false;

	//--- When clicked, get focus to receive keyboard events
	setFocusPolicy(Qt::ClickFocus);

	//Initialize mouse flag
	this->_firstPosition = true;

	_captureThread = new CaptureController(this, _frameRate, _frameWidth, _frameHeight, _numCameras);
	connect(_captureThread, SIGNAL(finished()), _captureThread, SLOT(deleteLater()));
	connect(_captureThread, SIGNAL(signalRefreshTime(QTime)), this, SLOT(RefreshTime(QTime)));
	connect(_captureThread, SIGNAL(signalPointCloud(vector<POI>)), this, SLOT(SetPointCloud(vector<POI>)));
	connect(_captureThread, SIGNAL(signalStaticCalibrationReady()), this, SLOT(slotStaticCalibrationSuccess()));
	connect(_captureThread, SIGNAL(signalFloorCalibrationReady()), this, SLOT(slotFloorCalibrationSuccess()));
	connect(_captureThread, SIGNAL(signalMarkerLoss()), this, SLOT(slotMarkerLoss()));

	connect(_captureThread, SIGNAL(signalCameraCenters(Vector3f*)), this, SLOT(slotCameraCenters(Vector3f*)));
	_captureThread->start();

}

ThreeDWidget::~ThreeDWidget()
{
	//delete capture thread
	//	_captureThread->terminate();

	if(_captureThread->isRunning())
	{
		_captureThread->quit();
		_captureThread->wait();
		_captureThread->deleteLater();
	}
	//delete _captureThread;
	//_captureThread = NULL;
}

void ThreeDWidget::RefreshTime(QTime _captureTime)
{
	emit signalRefreshTime(_captureTime);
}

void ThreeDWidget::StartReconstruction()
{
	_captureThread->StartReconstruction();
}

void ThreeDWidget::SetPointCloud(vector<POI> pointCloud)
{
	_pointCloud = pointCloud;
	update();
}

void ThreeDWidget::initializeGL() 
{

	qglClearColor(Qt::black);
	glEnable(GL_DEPTH_TEST);

}


void ThreeDWidget::resizeGL(int width, int height)
{

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//--- Don't allow division by zero!!!
	if (height <= 0) {
		height = 1;
	}

	GLfloat fAspect = GLfloat(width) / GLfloat(height);
	gluPerspective(60.0f, fAspect, 1.0, 200.0);

}

void ThreeDWidget::paintGL() 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	drawView();
	drawFloor();
	drawOriginal();
	//	drawSkeleton();
	drawPointCloud();
	if(_calibrated)
		drawCameras();
}

void ThreeDWidget::drawView() 
{

	glLoadIdentity();

	//--- Set view matrix; MODELVIEW matrix is altered but still centered at (0,0,0)
	gluLookAt(_eye.x, _eye.y, _eye.z, _center.x, _center.y, _center.z, _up.x,
		_up.y, _up.z);

	glRotatef(_rotationY, 0.0, 1.0, 0.0);
	glRotatef(_rotationX, 1.0, 0.0, 0.0);
	//--- Push matrix into the stack
	glPushMatrix();
}


void ThreeDWidget::drawFloor()
{

	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	glTranslatef((_floorColumns / 2) * (-_squareSize), ((_floorRows / 2)
		* _squareSize) - _squareSize, 0.0);

	for (int col = 0; col < _floorColumns; col++)
	{
		for (int row = 0; row < _floorRows; row++)
		{
			//---Light grey
			glColor3ub(133, 133, 133);
			glBegin(GL_LINE_LOOP);
			glVertex2f(0.0, 0.0);
			glVertex2f(_squareSize, 0.0);
			glVertex2f(_squareSize, _squareSize);
			glVertex2f(0.0, _squareSize);
			glEnd();

			glTranslatef(0.0, -_squareSize, 0.0);
		}
		glTranslatef(_squareSize, _floorRows * _squareSize, 0.0);
	}

}

void ThreeDWidget::drawOriginal()
{
	glPopMatrix();
	GLUquadric* quadric = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3ub(0, 255, 0);
	gluSphere(quadric, 0.07f, 10, 10);
	glPopMatrix();
	gluDeleteQuadric(quadric);
}


void ThreeDWidget::drawPointCloud()
{
	glPopMatrix();
	GLUquadric* quadric = gluNewQuadric();
	for (unsigned int i = 0; i < _pointCloud.size(); i++)
	{
		glPushMatrix();
		CvPoint3D32f coords = _pointCloud[i]._coordinates3d;
		//	glTranslatef(coords.x/10, coords.y/10, coords.z/10);
		glTranslatef(coords.x * 2, coords.y * 2, coords.z * 2);
		glColor3ub(255, 0, 0);
		gluSphere(quadric, 0.07f, 10, 10);
		glPopMatrix();
	}
	/*	if(_pointCloud.size() == 2)
	{
	CvPoint3D32f coords1 = _pointCloud[0].getCoordinates3d();
	CvPoint3D32f coords2 = _pointCloud[1].getCoordinates3d();
	//	qDebug()<<sqrt((coords1.x - coords2.x)*(coords1.x - coords2.x)+(coords1.y - coords2.y)*(coords1.y - coords2.y)+(coords1.z - coords2.z)*(coords1.z - coords2.z));
	}*/
	/*	glPushMatrix();
	glTranslatef(1, 1, 1);
	glColor3ub(0, 255, 0);
	gluSphere(quadric, 0.03f, 20, 20);
	glPopMatrix();*/

	gluDeleteQuadric(quadric);
}


void ThreeDWidget::drawCameras() 
{

	GLUquadric* quadric = gluNewQuadric();
	for (unsigned int i = 0; i < _numCameras; i++)
	{

		glPushMatrix();
		//--- Euler angles as composition of extrinsic rotations
		//--- z = g, y = b, x = a
		glRotatef(0, 0.0f, 0.0f, 1.0f);
		glRotatef(0, 1.0f, 0.0f, 0.0f);
		glRotatef(0, 0.0f, 0.0f, 1.0f);
		glTranslatef(_cameraCenters[i](0) * 2, _cameraCenters[i](1) * 2, _cameraCenters[i](2) * 2);
	//	glTranslatef(camera->getTranslation().x, camera->getTranslation().y, camera->getTranslation().z);

		glColor3ub(0, 200, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glEnd();

		glColor3ub(0, 200, 0);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glEnd();

		glColor3ub(0, 200, 0);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glEnd();

		glColor3ub(0, 200, 0);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glEnd();

		glColor3ub(0, 200, 0);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glEnd();

		glPopMatrix();

	}
	gluDeleteQuadric(quadric);


}

void ThreeDWidget::keyPressEvent(QKeyEvent *event) 
{

	switch (event->key()) 
	{

	case Qt::Key_Left:
		_center.x-=1;
		break;
	case Qt::Key_Right:
		_center.x+=1;
		break;
	case Qt::Key_Up:
		_eye.z += 1;
		_eye.y -= 1;
		break;
	case Qt::Key_Down:
		_eye.z -= 1;
		_eye.y += 1;
		break;
	case Qt::Key_Backspace:
		//--- Reset to default view
		_rotationY = 0;
		_center.x = 0;
		_eye.z = -5.0;
		_eye.y = 5.0;
		break;
	}

	updateGL();

}


void ThreeDWidget::mouseMoveEvent(QMouseEvent *event)
{
	//Have position to compare
	if (this->_firstPosition)
	{
		this->_firstPosition = false;
	}
	else
	{
		//Button left
		if (this->_leftPressed)
		{
			//Rotate in Y axis
			if (this->_oldX - event->x() < 0)
			{
				_rotationY += 1;
			}
			else if (this->_oldX - event->x() > 0)
			{
				_rotationY -= 1;
			}

			//Rotate in X axis
			if (this->_oldY - event->y() < 0)
			{
				_rotationX += 1;
			}
			else if (this->_oldY - event->y() > 0)
			{
				_rotationX -= 1;
			}
		}
		else
		{
			//Right button
			if (this->_oldY - event->y() < 0)
			{
				_eye.z += 1;
				_eye.y -= 1;
			}
			else if (this->_oldY - event->y() > 0)
			{
				_eye.z -= 1;
				_eye.y += 1;
			}
		}
	}

	this->_oldX = event->x();
	this->_oldY = event->y();

	updateGL();
}

void ThreeDWidget::mousePressEvent(QMouseEvent *event)
{
	this->_leftPressed = event->button() == 1;
}


void ThreeDWidget::ReconstructionGetPOIs(vector<vector<POI>> POIsList)
{

}



void ThreeDWidget::LoadProjectionMatrix(QString calibrationResultLocation)
{
	_captureThread->LoadProjectionMatrix(calibrationResultLocation);
}

void ThreeDWidget::StaticCalibration()
{
	_captureThread->StaticCalibration();
}

void ThreeDWidget::FloorCalibration()
{
	_captureThread->FloorCalibration();
}

void ThreeDWidget::slotStaticCalibrationSuccess()
{
	emit signalStaticCalibrationSuccess();
}

void ThreeDWidget::slotFloorCalibrationSuccess()
{
	emit signalFloorCalibrationSuccess();
	UpdateView();
}



void ThreeDWidget::CalculateAccuracy()
{
	_captureThread->CalculateAccuracy();
}

void ThreeDWidget::CalculateMarkerLoss()
{
	_captureThread->CalculateMarkerLoss();
}

void ThreeDWidget::slotMarkerLoss()
{
	emit signalMarkerLoss();
}

void ThreeDWidget::slotCameraCenters(Vector3f* cameraCenters)
{
	_cameraCenters = cameraCenters;
	_calibrated = true;
	//UpdateView();
}

/**********************************
now i use the first 4 cameras to update the view, because these 4 cameras locate in the same side.  
void gluLookAt(	GLdouble eyeX,
GLdouble eyeY,
GLdouble eyeZ,
GLdouble centerX,
GLdouble centerY,
GLdouble centerZ,
GLdouble upX,
GLdouble upY,
GLdouble upZ);
第一组eyex, eyey,eyez 相机在世界坐标的位置
第二组centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
第三组upx,upy,upz 相机向上的方向在世界坐标中的方向
你把相机想象成为你自己的脑袋：
第一组数据就是脑袋的位置
第二组数据就是眼睛看的物体的位置
第三组就是头顶朝向的方向（因为你可以歪着头看同一个物体）。

**********************************/
void ThreeDWidget::UpdateView()
{
	int minCamera = _numCameras > 4 ? 4 : _numCameras;
	Vector3f newEye(0, 0, 0);
	Vector3f newCenter(0, 0, 0);
	for(int i = 0; i < minCamera; i++)
	{
		newEye += _cameraCenters[i];
	}
	newEye(0, 0) = newEye(0, 0) / minCamera * 3;
	newEye(1, 0) /= newEye(1, 0) / minCamera * 3;
	newEye(2, 0) = newEye(2, 0) / minCamera * 3;
	newCenter(1, 0) = newEye(1, 0) / 2;

	//set view
	_eye.x = newEye(0, 0);
	_eye.y = newEye(1, 0);
	_eye.z = newEye(2, 0);
	_center.x = newCenter(0, 0);
	_center.y = newCenter(1, 0);
	_center.z = newCenter(2, 0);
}