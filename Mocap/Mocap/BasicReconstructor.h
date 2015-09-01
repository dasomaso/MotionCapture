#pragma once
#include <QDebug>
#include "POI.h"
#include <map>
#include <vector>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <fstream>

#include "Profile.h"
#include "AbstractCamera.h"

using namespace std;
using namespace Eigen;
using namespace cv;
typedef struct LINE
{
	float a;
	float b;
	float c;
}LINE;

// KR from projection matrix P
typedef struct KR
{
	Matrix3f  K;
	Matrix3f  R;
}KR;

typedef Matrix<float, 1, 5> RowVector5f;
class BasicReconstructor
{
public:

		BasicReconstructor(int frameWidth, int frameHeight, int numCamreas);


	// open mocap original function

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


	void computeFundamentalMatrix(CvMat* fundamentalMatrix, CvMat* points1, CvMat* points2, int nPOIs);

	void computeCameraMatrices(CvMat* p1, CvMat* p2, CvMat* fundamentalMatrix);

	vector<POI> computeLinearEstimationOf3dCoordinates(CvMat* p1, CvMat* p2, CvMat* points1, CvMat* points2,
		int cameraWidth, int cameraHeight, map<QString, POI> firstCameraPOIs);

	CvMat* computeContractionByEpsilonTensor(CvMat* mat, int rows, int columns);

	CvMat* computeNormalizedPoints(CvMat *points, int nPoints, CvMat* normalizationTransform);
	//upper  are original function of open mocap

	void LoadProjectionMatrix(QString calibrationResultLocation);
	void CalculateFundamentalMatrix();
//	cv::Mat GetMatrix(int index);
	void ProjectionToFundamentalMatrix(const MatrixXf& P1, const MatrixXf& P2, Matrix3f& F);
	LINE CalculateEpipolarLine(const MatrixXf& F, const cv::Point2f pLeft);
	void Find2DMarkerMatching(vector<vector<POI>>& POIsList);
	
	virtual ~BasicReconstructor();

	vector<POI> reconstructPOIs(map<QString, POI> firstCameraPOIs, map<QString, POI> secondCameraPOIs);
	void LoadCalibrateData();
	bool IsMatch(LINE &line, Point2f & marker);
	void ClearMatchPoint();
	Point2f CalculateIntersection(LINE &line1, LINE &line2);
	//currentHandleIndex : current handle index of the maxSize cameras. the row index of matchPoint[][]
	void FindOtherMatchMarker(const Point2f& p1, const Point2f & p2, int index1, int index2, int currentHandleIndex,vector<vector<POI>>& POIsList);
	bool CameraContainPoint(Point2f& intersect, vector<POI>& POIs);
	vector<POI> Reconstruction();
	void FloorRotationTranslation(vector<POI>& POIList);
	void CalculateAntisymmetricMatrix(const Vector3f & t, Matrix3f& antisymmetricMatrix);
	int FindCandidateMarkersInOneCamera(LINE& line, vector<POI> & POIs, vector<Point2f> & matchedList);
	void PrintMatrix(const MatrixXf & mat);
	void InitMatrix();
	void UnDistorted(vector<vector<POI>>& POIsList);
	Point2f RetifyLenDistortion(const Matrix3f& inv_k, const Point2f& distortedPoint, const RowVector5f & distortion);

	KR KRTFromProjectionMatrix(const MatrixXf& P);
	void CalculateIntrinsicPara();
	void SetDistortionModel();
	Vector3f* GetCameraCenters();
	
//	vector<POI> test();

	// open mocap original function

private:

	int _frameWidth;
	int _frameHeight;
	CvMat* _disparityToDepth;
//	cv::Mat  _projectionMatrix;
//	cv::Mat **_fundamentalMatrix;
	MatrixXf _projectionMatrix;
	Matrix3f **_fundamentalMatrix;
	RowVector5f * _distortionFactor;             // 1 * 5 [k1, k2, k3, k4 ,k5].   [k1,k2,k5] == radial  distortion , [k3,k4] ==  tangential distortion
	Matrix3f *	_intrinsicPara;
	Matrix3f _floorRotation;
	Vector3f _floorTranslation;
	Matrix3f _floorTurnOver;
	Vector3f _central;
	Vector3f * _cameraCenters;
	Core::DistortionModel * _distortionModelList;
	bool _floorCalibrated;

	
	int _numCameras;
//	Point2f _matchPoint[MARKER_NUM][MARKER_NUM];
	Point2f **_matchPoint;
	ofstream outfile;
		
};

	