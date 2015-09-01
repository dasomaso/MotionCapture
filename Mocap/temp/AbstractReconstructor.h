#ifndef ABSTRACTRECONSTRUCTOR_H_
#define ABSTRACTRECONSTRUCTOR_H_

#include <opencv2/opencv.hpp>
#include <map>
#include <vector>
#include <fstream>
#include "Profile.h"
#include <QDebug>
#include "POI.h"
#include "AbstractCamera.h"

using namespace std;
using namespace cv;


class AbstractReconstructor
{

public:
	/*!
	 * Using initialized POIs from two cameras reconstruct them, returning a vector containing all detected POIs
	 * with z coordinate
	 */
	virtual vector<POI> reconstructPOIs(map<QString, POI> firstCameraPOIs, map<QString, POI> secondCameraPOIs ) = 0;

	/*!
	 * Computes point arrays from cameras. Image coordinates are left-handed, we must use the original coordinates complement
	 * to turn it to right-handed system
	 */
	static void computePointArrays(map<QString, POI> firstCameraPOIs, map<QString, POI> secondCameraPOIs, CvMat* points1,
			CvMat* points2, int width, int height);

	static void computePointArrays(vector< map<QString, POI> >& CameraPOIs, vector<CvMat*>& points, int width, int height);


	/*!
	 * Triangulates two inhomogeneous points into a 3d homogeneous point (w = 1) with camera projection matrices
	 */
	static CvMat* compute3dHomogeneousCoordinates(CvMat* projectionMatrix1, CvMat* projectionMatrix2,
			CvPoint2D32f point1, CvPoint2D32f point2);

	/*!
	 * Triangulates two inhomogeneous points into a 3d homogeneous point (w = 1) with camera projection matrices
	 */
	static CvMat* compute3dHomogeneousCoordinates(vector<CvMat*>& projectionMatrix, vector<CvPoint2D32f>& point);
	//Cvat *¡¡_projectionMatrix;
	cv::Mat  _projectionMatrix;
	cv::Mat _fundamentalMatrix[MAXCAMREAS][MAXCAMREAS];
	int _numCameras;
	Point2f _matchPoint[MARKERNUM][MARKERNUM];
	void LoadProjectionMatrix(QString calibrationResultLocation);
	void CalculateFundamentalMatrix();
	cv::Mat GetMatrix(int index);
	void ProjectionToFundamentalMatrix(cv::Mat& mat1, cv::Mat& mat2, cv::Mat& result);
	LINE CalculateEpipolarLine(cv::Mat& F, cv::Point2f pLeft);
	void Find2DMarkerMatch();


protected:

	AbstractReconstructor(int numCameras);


};

#endif /* ABSTRACTRECONSTRUCTOR_H_ */
