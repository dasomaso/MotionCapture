#ifndef THREEDWIDGET_H
#define THREEDWIDGET_H


/***********************************
zengjing note:
we need to add drawskeleton and drawjoint function to draw the skeleton.
this version contains none of theies.
And we also has not draw cameras yet.
************************************/
#include <QGLWidget>
#include <gl/GLU.h>
#include <QKeyEvent>
#include <QTime>
#include "ui_ThreeDWidget.h"
#include "Threads/CaptureController.h"
class ThreeDWidget : public QGLWidget
{
	Q_OBJECT

public:
	ThreeDWidget(QWidget *parent = 0, int frameRate = 120, int frameWidth = 1280, int frameHeight = 1024, int numCamreas = 2);
	~ThreeDWidget();
	void StartReconstruction();

		/*!
	 * Handle zoom, rotation and translation
	 */
	void keyPressEvent(QKeyEvent *event);

	/*!
	 * Handle zoom, rotation and translation
	 */
	void mouseMoveEvent(QMouseEvent *event);

	/*!
	 * Handle the button clicked
	 */
	void mousePressEvent(QMouseEvent *event);


		/*!
	 * Initializes OpenGL, just called once, before paintGL
	 */
	void initializeGL();

	/*!
	 * Draws everything, called every refresh
	 */
	void paintGL();

	/*!
	 * Resizes viewport if needed, called every refresh
	 */
	void resizeGL(int width, int height);

	/*!
	 * Draws main view
	 */
	void drawView();

	/*!
	 * Draws ambient floor, chess pattern
	 */
	void drawFloor();

	// draw original point
	void drawOriginal();

	/*!
	 * Draws skeleton; will recursively call drawJoint to complete skeleton
	 */
//	void drawSkeleton();

	/*!
	 * Draws joints recursively.
	 */
//	void drawJoint(Joint& joint);

	/*!
	 * Draws point cloud
	 */
	void drawPointCloud();

	/*!
	 * Draws cameras
	 */
	void drawCameras();
	void LoadProjectionMatrix(QString calibrationResultLocation);

	void StaticCalibration();
	void FloorCalibration();
	void CalculateAccuracy();
	void CalculateMarkerLoss();
	void UpdateView();
	

private:
	Ui::ThreeDWidget ui;
	CaptureController * _captureThread;
	int _frameRate;
	int _frameHeight;
	int _frameWidth;
	int _numCameras;
	vector<POI> _pointCloud;
	Vector3f * _cameraCenters;
	bool _calibrated;
	

	//! Number of rows present in the floor
	int _floorRows;
	//! Number of columns present in the floor
	int _floorColumns;
	//! Size of squares present in floor
	double _squareSize;
	//! Skeleton model to be used
	//Skeleton _skeleton;
	//! Viewer parameter - eye
	CvPoint3D64f _eye;
	//! Viewer parameter - center
	CvPoint3D64f _center;
	//! Viewer parameter - up
	CvPoint3D64f _up;
	//! Rotation around 'X' axis
	double _rotationX;
	//! Rotation around 'Y' axis
	double _rotationY;

	//!Old value of x  of themouse position
	int _oldX;
	//!Old value of y of the mouse position
	int _oldY;
	//!Flag if the
	bool _firstPosition;
	//!Flag to left mouse click pressed
	bool _leftPressed;


signals:
	void signalRefreshTime(QTime);
	void signalStaticCalibrationSuccess();
	void signalFloorCalibrationSuccess();
	void signalMarkerLoss();
	

	protected slots:
		void RefreshTime(QTime);
		void SetPointCloud(vector<POI> pointCloud);
		void ReconstructionGetPOIs(vector<vector<POI>> POIsList);
		//void ReconstructionGetPOIs(int);
		/*!
	 * Widget to display images and points of interests
	 */
//	POIsImageWidget* _POIsImageWidget;
		void slotStaticCalibrationSuccess();
		void slotFloorCalibrationSuccess();
		void slotMarkerLoss();
		void slotCameraCenters(Vector3f* cameraCenters);
};

#endif // THREEDWIDGET_H
