#include "BasicReconstructor.h"
BasicReconstructor::BasicReconstructor(int frameWidth, int frameHeight, int numCameras)
{
	//file_3d.open("3dpoints.txt");
	_frameHeight = frameHeight;
	_frameWidth = frameWidth;
	_numCameras = numCameras;
	_floorCalibrated = false;
	_matchPoint = new Point2f*[Para::markerNum];
	for(int i = 0; i < Para::markerNum; i++)
		_matchPoint[i] = new Point2f[Para::markerNum];
	InitMatrix();
	LoadCalibrateData();
	// outfile.open("matrix.txt");

}

BasicReconstructor::~BasicReconstructor()
{
	for(int i = 0; i < Para::markerNum; i++)
		delete[] _matchPoint[i];
}


void BasicReconstructor::computePointArrays(map<QString, POI> firstCameraPOIs, map<QString, POI> secondCameraPOIs,
	CvMat* points1, CvMat* points2, int width, int height) 
{

	int i = 0;
	if(firstCameraPOIs.size() ==0 || firstCameraPOIs.size() ==0 ) return ; 
	for (map<QString, POI>::const_iterator it = firstCameraPOIs.begin(); it != firstCameraPOIs.end(); ++it) 
	{
		POI firstCameraPOI = it->second;

		//--- Image coordinates are upside down

		points1->data.fl[i * 2] = (width - 1) - firstCameraPOI._coordinates2d.x;
		points1->data.fl[i * 2 + 1] = (height - 1) - firstCameraPOI._coordinates2d.y;

		//POI secondCameraPOI = secondCameraPOIs[it->second.getSemantic().toStdString()];
		POI secondCameraPOI = secondCameraPOIs[it->second._semantic];
		points2->data.fl[i * 2] = (width - 1) - secondCameraPOI._coordinates2d.x;
		points2->data.fl[i * 2 + 1] = (height - 1) - secondCameraPOI._coordinates2d.y;

		i++;
	}

}

void BasicReconstructor::computePointArrays(vector<map<QString, POI> >& CameraPOIs, vector<CvMat*>& points, int width, int height)
{

	int i = 0;
	POI tempPOI;

	for (map<QString, POI>::const_iterator it = CameraPOIs[0].begin(); it != CameraPOIs[0].end(); ++it)
	{
		//string namePOI = it->second.getSemantic().toStdString();
		QString namePOI = it->second._semantic;
		for (unsigned int cam = 0; cam < CameraPOIs.size(); cam++) {
			/* Reconstruction Model (0,0) = down-left
			* OpenCV Image (0,0) = up-left
			* Transforms OpenCV image coordinates into our reconstruction model image coordinates
			*/
			tempPOI = CameraPOIs[cam][namePOI];
			points[cam]->data.fl[i * 2] = (width - 1) - tempPOI._coordinates2d.x;
			points[cam]->data.fl[i * 2 + 1] = (height - 1) - tempPOI._coordinates2d.y;

		}
		i++;
	}

}

CvMat* BasicReconstructor::compute3dHomogeneousCoordinates(CvMat* projectionMatrix1, CvMat* projectionMatrix2,
	CvPoint2D32f point1, CvPoint2D32f point2)
{

	CvMat* A = cvCreateMat(4, 4, CV_32FC1);

	//---Linear LS Triangulation
	cvmSet(A, 0, 0, (point1.x * cvmGet(projectionMatrix1, 2, 0) - cvmGet(projectionMatrix1, 0, 0)));
	cvmSet(A, 0, 1, (point1.x * cvmGet(projectionMatrix1, 2, 1) - cvmGet(projectionMatrix1, 0, 1)));
	cvmSet(A, 0, 2, (point1.x * cvmGet(projectionMatrix1, 2, 2) - cvmGet(projectionMatrix1, 0, 2)));
	cvmSet(A, 0, 3, (point1.x * cvmGet(projectionMatrix1, 2, 3) - cvmGet(projectionMatrix1, 0, 3)));

	cvmSet(A, 1, 0, (point1.y * cvmGet(projectionMatrix1, 2, 0) - cvmGet(projectionMatrix1, 1, 0)));
	cvmSet(A, 1, 1, (point1.y * cvmGet(projectionMatrix1, 2, 1) - cvmGet(projectionMatrix1, 1, 1)));
	cvmSet(A, 1, 2, (point1.y * cvmGet(projectionMatrix1, 2, 2) - cvmGet(projectionMatrix1, 1, 2)));
	cvmSet(A, 1, 3, (point1.y * cvmGet(projectionMatrix1, 2, 3) - cvmGet(projectionMatrix1, 1, 3)));

	cvmSet(A, 2, 0, (point2.x * cvmGet(projectionMatrix2, 2, 0) - cvmGet(projectionMatrix2, 0, 0)));
	cvmSet(A, 2, 1, (point2.x * cvmGet(projectionMatrix2, 2, 1) - cvmGet(projectionMatrix2, 0, 1)));
	cvmSet(A, 2, 2, (point2.x * cvmGet(projectionMatrix2, 2, 2) - cvmGet(projectionMatrix2, 0, 2)));
	cvmSet(A, 2, 3, (point2.x * cvmGet(projectionMatrix2, 2, 3) - cvmGet(projectionMatrix2, 0, 3)));

	cvmSet(A, 3, 0, (point2.y * cvmGet(projectionMatrix2, 2, 0) - cvmGet(projectionMatrix2, 1, 0)));
	cvmSet(A, 3, 1, (point2.y * cvmGet(projectionMatrix2, 2, 1) - cvmGet(projectionMatrix2, 1, 1)));
	cvmSet(A, 3, 2, (point2.y * cvmGet(projectionMatrix2, 2, 2) - cvmGet(projectionMatrix2, 1, 2)));
	cvmSet(A, 3, 3, (point2.y * cvmGet(projectionMatrix2, 2, 3) - cvmGet(projectionMatrix2, 1, 3)));

	CvMat* U = cvCreateMat(4, 4, CV_32FC1);
	CvMat* W = cvCreateMat(4, 1, CV_32FC1);
	CvMat* V = cvCreateMat(4, 4, CV_32FC1);

	cvSVD(A, W, U, V, CV_SVD_V_T);

	CvMat* x = cvCreateMat(4, 1, CV_32FC1);
	cvmSet(x, 0, 0, V->data.fl[12] / V->data.fl[15]);
	cvmSet(x, 1, 0, V->data.fl[13] / V->data.fl[15]);
	cvmSet(x, 2, 0, V->data.fl[14] / V->data.fl[15]);
	cvmSet(x, 3, 0, 1.0f);

	cvReleaseMat(&W);
	cvReleaseMat(&U);
	cvReleaseMat(&V);
	cvReleaseMat(&A);

	return x;

}

CvMat* BasicReconstructor::compute3dHomogeneousCoordinates(vector<CvMat*>& projectionMatrix, vector<CvPoint2D32f>& points) 
{

	int numCam = projectionMatrix.size();
	int m = 2 * numCam;
	int n = 4;

	CvMat* A = cvCreateMat(m, n, CV_32FC1);

	for (int i = 0; i < numCam; i++) {
		cvmSet(A, 2 * i, 0, (points[i].x * cvmGet(projectionMatrix[i], 2, 0) - cvmGet(projectionMatrix[i], 0, 0)));
		cvmSet(A, 2 * i, 1, (points[i].x * cvmGet(projectionMatrix[i], 2, 1) - cvmGet(projectionMatrix[i], 0, 1)));
		cvmSet(A, 2 * i, 2, (points[i].x * cvmGet(projectionMatrix[i], 2, 2) - cvmGet(projectionMatrix[i], 0, 2)));
		cvmSet(A, 2 * i, 3, (points[i].x * cvmGet(projectionMatrix[i], 2, 3) - cvmGet(projectionMatrix[i], 0, 3)));

		cvmSet(A, (2 * i) + 1, 0, (points[i].y * cvmGet(projectionMatrix[i], 2, 0) - cvmGet(projectionMatrix[i], 1, 0)));
		cvmSet(A, (2 * i) + 1, 1, (points[i].y * cvmGet(projectionMatrix[i], 2, 1) - cvmGet(projectionMatrix[i], 1, 1)));
		cvmSet(A, (2 * i) + 1, 2, (points[i].y * cvmGet(projectionMatrix[i], 2, 2) - cvmGet(projectionMatrix[i], 1, 2)));
		cvmSet(A, (2 * i) + 1, 3, (points[i].y * cvmGet(projectionMatrix[i], 2, 3) - cvmGet(projectionMatrix[i], 1, 3)));
	}

	CvMat* W = cvCreateMat(n, 1, CV_32FC1);
	CvMat* V = cvCreateMat(n, n, CV_32FC1);

	cvSVD(A, W, NULL, V, CV_SVD_MODIFY_A | CV_SVD_V_T);

	CvMat* X = cvCreateMat(n, 1, CV_32FC1);
	cvmSet(X, 0, 0, V->data.fl[12] / V->data.fl[15]);
	cvmSet(X, 1, 0, V->data.fl[13] / V->data.fl[15]);
	cvmSet(X, 2, 0, V->data.fl[14] / V->data.fl[15]);
	cvmSet(X, 3, 0, 1.0f);

	cvReleaseMat(&W);
	cvReleaseMat(&V);
	cvReleaseMat(&A);

	return X;

}



vector<POI> BasicReconstructor::reconstructPOIs(map<QString, POI> firstCameraPOIs, map<QString, POI> secondCameraPOIs)
{
	vector<POI> POIs3d;

	int nPOIsFirstCamera = firstCameraPOIs.size();
	int nPOIsSecondCamera = secondCameraPOIs.size();

	//--- All points must have a correspondent.
	if( nPOIsFirstCamera > 0 && nPOIsFirstCamera == nPOIsSecondCamera)
	{

		CvMat* points1 = cvCreateMat(1, nPOIsFirstCamera, CV_32FC2);
		CvMat* points2 = cvCreateMat(1, nPOIsFirstCamera, CV_32FC2);
		computePointArrays(firstCameraPOIs, secondCameraPOIs, points1, points2, _frameWidth, _frameHeight);

		// CvMat* Q = camera1->getDisparityToDepth();
		//	//CvMat * Q = (CvMat*)cvLoad("Q.xml");
		CvMat * Q = _disparityToDepth;
		int i = 0;
		for (map<QString, POI>::const_iterator it = firstCameraPOIs.begin(); it != firstCameraPOIs.end(); ++it) 
		{

			POI tridimensionalPOI;
			//tridimensionalPOI.setSemantic(QString(it->first.c_str()));
			tridimensionalPOI._semantic = it->first;
			CvPoint2D32f pointRightImage = cvPoint2D32f(points1->data.fl[i * 2], points1->data.fl[i * 2 + 1]);
			CvPoint2D32f pointLeftImage = cvPoint2D32f(points2->data.fl[i * 2], points2->data.fl[i * 2 + 1]);

			float d = pointRightImage.x - pointLeftImage.x;
			float x = pointLeftImage.x * cvmGet(Q, 0, 0) + cvmGet(Q, 0, 3);
			float y = pointLeftImage.y * cvmGet(Q, 1, 1) + cvmGet(Q, 1, 3);
			float z = cvmGet(Q, 2, 3);
			float w = d * cvmGet(Q, 3, 2) + cvmGet(Q, 3, 3);

			tridimensionalPOI._coordinates3d = cvPoint3D32f( x/w, y/w, z/w );
			POIs3d.push_back(tridimensionalPOI);
			i++;
			//	logINFORMATIONAL("name = %s, 3d coordinate = %f, %f, %f", it->second.getSemantic().toStdString().c_str(), x/w, y/w, z/w);
		}

		//--- Clear heap
		cvReleaseMat(&points1);
		cvReleaseMat(&points2);
		//cvReleaseMat(&Q);

	} 
	else
	{
		//qDebug()<<"Number of points between cameras do not match!!!";

	}
	return POIs3d;
}

void BasicReconstructor::computeFundamentalMatrix(CvMat* fundamentalMatrix, CvMat* p1, CvMat* p2, int nPOIs)
{

	//--- OpenCV Approach
	//	CvMat* status = cvCreateMat(1, nPOIs, CV_8UC1);
	//	int fmCount = cvFindFundamentalMat(points1, points2, fundamentalMatrix, CV_FM_8POINT);
	//
	//	if (fmCount != 1) {
	//		cout << "[ERROR] Could not find fundamental matrix or found more than one " << endl;
	//	} else {
	//		Utils::cvPrintMat(fundamentalMatrix, 3, 3);
	//	}
	//
	//	cvReleaseMat(&status);

	//--- Based on Andrew Zisserman Matlab code


	CvMat *normalizationTransform1 = cvCreateMat(3, 3, CV_32FC1);
	CvMat *normalizedPoints1 = computeNormalizedPoints(p1, nPOIs, normalizationTransform1);

	CvMat *normalizationTransform2 = cvCreateMat(3, 3, CV_32FC1);
	CvMat *normalizedPoints2 = computeNormalizedPoints(p2, nPOIs, normalizationTransform2);

	// Build the constraint matrix
	CvMat* constraintMatrix = cvCreateMat(nPOIs, 9, CV_32FC1);
	for (int i = 0; i < nPOIs; i++)
	{
		for (int j = 0; j < 9; j++)
		{

			switch (j) {

			case 0:
				//--- p2.x * p1.x
				cvmSet(constraintMatrix, i, j, normalizedPoints2->data.fl[i * 2] * normalizedPoints1->data.fl[i * 2]);
				break;
			case 1:
				//--- p2.x * p1.y
				cvmSet(constraintMatrix, i, j, normalizedPoints2->data.fl[i * 2]
				* normalizedPoints1->data.fl[i * 2 + 1]);
				break;
			case 2:
				//--- p2.x
				cvmSet(constraintMatrix, i, j, normalizedPoints2->data.fl[i * 2]);
				break;
			case 3:
				//--- p2.y * p1.x
				cvmSet(constraintMatrix, i, j, normalizedPoints2->data.fl[i * 2 + 1]
				* normalizedPoints1->data.fl[i * 2]);
				break;
			case 4:
				//--- p2.y * p1.y
				cvmSet(constraintMatrix, i, j, normalizedPoints2->data.fl[i * 2 + 1] * normalizedPoints1->data.fl[i * 2
					+ 1]);
				break;
			case 5:
				//--- p2.y
				cvmSet(constraintMatrix, i, j, normalizedPoints2->data.fl[i * 2 + 1]);
				break;
			case 6:
				//--- p1.x
				cvmSet(constraintMatrix, i, j, normalizedPoints1->data.fl[i * 2]);
				break;
			case 7:
				//--- p1.y
				cvmSet(constraintMatrix, i, j, normalizedPoints1->data.fl[i * 2 + 1]);
				break;
			default:
				cvmSet(constraintMatrix, i, j, 1);
			}

		}
	}

	cvReleaseMat(&normalizedPoints1);
	cvReleaseMat(&normalizedPoints2);

	CvMat* u = cvCreateMat(nPOIs, 9, CV_32FC1);
	CvMat* d = cvCreateMat(nPOIs, 9, CV_32FC1);
	CvMat* v = cvCreateMat(nPOIs, 9, CV_32FC1);
	cvSVD(constraintMatrix, d, u, v);

	cvReleaseMat(&constraintMatrix);
	cvReleaseMat(&d);
	cvReleaseMat(&u);

	//--- Extract fundamental matrix from the column of V corresponding to smallest singular value.
	cvmSet(fundamentalMatrix, 0, 0, cvmGet(v, 0, 8));
	cvmSet(fundamentalMatrix, 0, 1, cvmGet(v, 1, 8));
	cvmSet(fundamentalMatrix, 0, 2, cvmGet(v, 2, 8));
	cvmSet(fundamentalMatrix, 1, 0, cvmGet(v, 3, 8));
	cvmSet(fundamentalMatrix, 1, 1, cvmGet(v, 4, 8));
	cvmSet(fundamentalMatrix, 1, 2, cvmGet(v, 5, 8));
	cvmSet(fundamentalMatrix, 2, 0, cvmGet(v, 6, 8));
	cvmSet(fundamentalMatrix, 2, 1, cvmGet(v, 7, 8));
	cvmSet(fundamentalMatrix, 2, 2, cvmGet(v, 8, 8));

	cvReleaseMat(&v);

	//--- Enforce constraint that fundamental matrix has rank 2 by performing a svd and then reconstructing with the two largest singular values.
	CvMat* uF = cvCreateMat(3, 3, CV_32FC1);
	CvMat* dF = cvCreateMat(3, 3, CV_32FC1);
	CvMat* vF = cvCreateMat(3, 3, CV_32FC1);
	cvSVD(fundamentalMatrix, dF, uF, vF);

	//--- Diagonal dF
	CvMat* diagDF = cvCreateMat(3, 3, CV_32FC1);
	cvConvertScale(diagDF, diagDF, 0);
	cvmSet(diagDF, 0, 0, cvmGet(dF, 0, 0));
	cvmSet(diagDF, 1, 1, cvmGet(dF, 1, 1));

	cvReleaseMat(&dF);

	//--- Transpose vF
	CvMat* transposeVF = cvCreateMat(3, 3, CV_32FC1);
	cvTranspose(vF, transposeVF);

	cvReleaseMat(&vF);

	// F = U*diag([D(1,1) D(2,2) 0])*V'
	cvMatMul(uF, diagDF, uF);
	cvMatMul(uF, transposeVF, fundamentalMatrix);

	cvReleaseMat(&diagDF);
	cvReleaseMat(&uF);
	cvReleaseMat(&transposeVF);

	CvMat* normalizationTransform2Transpose = cvCreateMat(3, 3, CV_32FC1);
	cvTranspose(normalizationTransform2, normalizationTransform2Transpose);

	cvReleaseMat(&normalizationTransform2);

	cvMatMul(normalizationTransform2Transpose, fundamentalMatrix, fundamentalMatrix);
	cvMatMul(fundamentalMatrix, normalizationTransform1, fundamentalMatrix);
	cvReleaseMat(&normalizationTransform1);

}

void BasicReconstructor::computeCameraMatrices(CvMat* p1, CvMat* p2, CvMat* fundamentalMatrix)
{

	//--- First camera matrix
	cvSetIdentity(p1);

	//--- Second camera matrix
	CvMat* s = cvCreateMat(3, 3, CV_32FC1);
	CvMat* u = cvCreateMat(3, 3, CV_32FC1);
	CvMat* v = cvCreateMat(3, 3, CV_32FC1);
	cvSVD(fundamentalMatrix, s, u, v);

	//--- Get epipole
	CvMat* eColumnVector = cvCreateMat(3, 1, CV_32FC1);
	cvGetCol(u, eColumnVector, 2);

	CvMat* eContrEps = computeContractionByEpsilonTensor(eColumnVector, 3, 1);

	CvMat* fMultByEContrEps = cvCreateMat(3, 3, CV_32FC1);
	cvMatMul(eContrEps, fundamentalMatrix, fMultByEContrEps);

	for (int i = 0; i < 3; i++)
	{

		cvmSet(p2, i, 0, -cvmGet(fMultByEContrEps, i, 0));
		cvmSet(p2, i, 1, -cvmGet(fMultByEContrEps, i, 1));
		cvmSet(p2, i, 2, -cvmGet(fMultByEContrEps, i, 2));
		cvmSet(p2, i, 3, cvmGet(u, i, 2));

	}

	//--- Matlab is giving positive values for last column, while openCV gives negative ones.
	//--- So we multiply p2 by -1;

	cvConvertScale(p2, p2, -1);

	cvReleaseMat(&s);
	cvReleaseMat(&u);
	cvReleaseMat(&v);

	cvReleaseMat(&eColumnVector);
	cvReleaseMat(&eContrEps);
	cvReleaseMat(&fMultByEContrEps);

}

vector<POI> BasicReconstructor::computeLinearEstimationOf3dCoordinates(CvMat* p1, CvMat* p2, CvMat* points1,
	CvMat* points2, int cameraWidth, int cameraHeight, map<QString, POI> firstCameraPOIs)
{

	vector<POI> POIs3d;

	CvMat* h = cvCreateMat(3, 3, CV_32FC1);
	cvConvertScale(h, h, 0);
	cvmSet(h, 0, 0, 2.0f / cameraWidth);
	cvmSet(h, 1, 1, 2.0f / cameraHeight);
	cvmSet(h, 0, 2, -1.0f);
	cvmSet(h, 1, 2, -1.0f);
	cvmSet(h, 2, 2, 1.0f);

	CvMat* p1Norm = cvCreateMat(3, 4, CV_32FC1);
	cvMatMul(h, p1, p1Norm);

	CvMat* p2Norm = cvCreateMat(3, 4, CV_32FC1);
	cvMatMul(h, p2, p2Norm);

	CvMat* u = cvCreateMat(2, 2, CV_32FC1);

	int i = 0;
	for (map<QString, POI>::const_iterator it = firstCameraPOIs.begin(); it != firstCameraPOIs.end(); ++it)
	{

		POI firstCameraPOI = it->second;

		//--- Build u (point matrix)
		cvmSet(u, 0, 0, points1->data.fl[i * 2]);
		cvmSet(u, 1, 0, points1->data.fl[i * 2 + 1]);
		cvmSet(u, 0, 1, points2->data.fl[i * 2]);
		cvmSet(u, 1, 1, points2->data.fl[i * 2 + 1]);

		//--- Normalize u
		float u00 = cvmGet(h, 0, 0) * cvmGet(u, 0, 0) + cvmGet(h, 0, 1) * cvmGet(u, 1, 0) + cvmGet(h, 0, 2);
		float u10 = cvmGet(h, 1, 0) * cvmGet(u, 0, 0) + cvmGet(h, 1, 1) * cvmGet(u, 1, 0) + cvmGet(h, 1, 2);
		float u01 = cvmGet(h, 0, 0) * cvmGet(u, 0, 1) + cvmGet(h, 0, 1) * cvmGet(u, 1, 1) + cvmGet(h, 0, 2);
		float u11 = cvmGet(h, 1, 0) * cvmGet(u, 0, 1) + cvmGet(h, 1, 1) * cvmGet(u, 1, 1) + cvmGet(h, 1, 2);

		CvMat* point1Homogeneous = cvCreateMat(3, 1, CV_32FC1);
		cvmSet(point1Homogeneous, 0, 0, u00);
		cvmSet(point1Homogeneous, 1, 0, u10);
		cvmSet(point1Homogeneous, 2, 0, 1);

		CvMat* point2Homogeneous = cvCreateMat(3, 1, CV_32FC1);
		cvmSet(point2Homogeneous, 0, 0, u01);
		cvmSet(point2Homogeneous, 1, 0, u11);
		cvmSet(point2Homogeneous, 2, 0, 1);

		CvMat* point1HomogeneousContrByEps = computeContractionByEpsilonTensor(point1Homogeneous, 3, 1);
		CvMat* point2HomogeneousContrByEps = computeContractionByEpsilonTensor(point2Homogeneous, 3, 1);

		CvMat* a1 = cvCreateMat(3, 4, CV_32FC1);
		cvMatMul(point1HomogeneousContrByEps, p1Norm, a1);

		CvMat* a2 = cvCreateMat(3, 4, CV_32FC1);
		cvMatMul(point2HomogeneousContrByEps, p2Norm, a2);

		CvMat* a1a2 = cvCreateMat(6, 4, CV_32FC1);
		for (int row = 0; row < 6; row++) 
		{
			for (int column = 0; column < 4; column++)
			{

				float value = 0.0f;
				if (row < 3)
				{
					value = cvmGet(a1, row, column);
				} 
				else 
				{
					value = cvmGet(a2, row - 3, column);
				}
				cvmSet(a1a2, row, column, value);
			}
		}

		CvMat* dummyA = cvCreateMat(4, 4, CV_32FC1);
		CvMat* dummyB = cvCreateMat(6, 4, CV_32FC1);
		CvMat* x = cvCreateMat(4, 4, CV_32FC1);
		cvSVD(a1a2, dummyA, dummyB, x);

		CvMat* homogeneous3dCoordinates = cvCreateMat(4, 1, CV_32FC1);
		cvmSet(homogeneous3dCoordinates, 0, 0, cvmGet(x, 0, 3));
		cvmSet(homogeneous3dCoordinates, 1, 0, cvmGet(x, 1, 3));
		cvmSet(homogeneous3dCoordinates, 2, 0, cvmGet(x, 2, 3));
		cvmSet(homogeneous3dCoordinates, 3, 0, cvmGet(x, 3, 3));

		//--- Lets get scale parameter to 1
		cvConvertScale(homogeneous3dCoordinates, homogeneous3dCoordinates, 1.0f
			/ cvmGet(homogeneous3dCoordinates, 3, 0));

		//--- Do we need to multiply coordinates by - 1?
		firstCameraPOI._coordinates3d.x = cvmGet(homogeneous3dCoordinates, 0, 0);
		firstCameraPOI._coordinates3d.y = cvmGet(homogeneous3dCoordinates, 1, 0);
		firstCameraPOI._coordinates3d.z = cvmGet(homogeneous3dCoordinates, 2, 0);


		//	firstCameraPOI.getInfo3d();

		POIs3d.push_back(firstCameraPOI);

		i++;

		cvReleaseMat(&point1Homogeneous);
		cvReleaseMat(&point2Homogeneous);
		cvReleaseMat(&point1HomogeneousContrByEps);
		cvReleaseMat(&point2HomogeneousContrByEps);
		cvReleaseMat(&a1);
		cvReleaseMat(&a2);
		cvReleaseMat(&a1a2);
		cvReleaseMat(&dummyA);
		cvReleaseMat(&dummyB);
		cvReleaseMat(&x);
		cvReleaseMat(&homogeneous3dCoordinates);

	}

	cvReleaseMat(&h);
	cvReleaseMat(&p1Norm);
	cvReleaseMat(&p2Norm);
	cvReleaseMat(&u);

	return POIs3d;
}

CvMat* BasicReconstructor::computeContractionByEpsilonTensor(CvMat* mat, int rows, int columns) 
{

	CvMat* result = NULL;

	if ((rows == 3 && columns == 1) || (rows == 1 && columns == 3)) 
	{

		bool rowVector = false;
		if (rows == 3)
		{
			rowVector = true;
		}

		result = cvCreateMat(3, 3, CV_32FC1);
		cvSet(result, cvScalar(0));

		float element1 = 0.0f;
		float element2 = 0.0f;
		float element3 = 0.0f;

		if (rowVector) 
		{
			element1 = cvmGet(mat, 0, 0);
			element2 = cvmGet(mat, 1, 0);
			element3 = cvmGet(mat, 2, 0);
		} 
		else
		{
			element1 = cvmGet(mat, 0, 0);
			element2 = cvmGet(mat, 0, 1);
			element3 = cvmGet(mat, 0, 2);
		}

		//--- First Line
		cvmSet(result, 0, 1, element3);
		cvmSet(result, 0, 2, -element2);

		//--- Second Line
		cvmSet(result, 1, 0, -element3);
		cvmSet(result, 1, 2, element1);

		//--- Third Line
		cvmSet(result, 2, 0, element2);
		cvmSet(result, 2, 1, -element1);

	} 
	else
	{
		qDebug()<<"Unrecognized contraction by epsilon tensor!";
	}

	return result;
}

CvMat* BasicReconstructor::computeNormalizedPoints(CvMat *points, int nPoints, CvMat* normalizationTransform) 
{

	CvMat* normalizedPoints = cvCreateMat(1, nPoints, CV_32FC2);

	float meanX = 0;
	float meanY = 0;

	for (int i = 0; i < nPoints; i++)
	{
		meanX += points->data.fl[i * 2];
		meanY += points->data.fl[i * 2 + 1];

	}
	meanX /= nPoints;
	meanY /= nPoints;

	float meanDist = 0;
	for (int i = 0; i < nPoints; i++) 
	{
		normalizedPoints->data.fl[i * 2] = points->data.fl[i * 2] - meanX;
		normalizedPoints->data.fl[i * 2 + 1] = points->data.fl[i * 2 + 1] - meanY;
		meanDist
			+= cvSqrt(powf(normalizedPoints->data.fl[i * 2], 2.0f) + powf(normalizedPoints->data.fl[i * 2 + 1], 2.0f));
	}
	meanDist /= nPoints;

	float scale = cvSqrt(2.0f) / meanDist;
	for (int i = 0; i < nPoints; i++) {
		normalizedPoints->data.fl[i * 2] = scale * points->data.fl[i * 2] - (scale * meanX);
		normalizedPoints->data.fl[i * 2 + 1] = scale * points->data.fl[i * 2 + 1] - (scale * meanY);
	}

	cvConvertScale(normalizationTransform, normalizationTransform, 0.0f);
	cvmSet(normalizationTransform, 0, 0, scale);
	cvmSet(normalizationTransform, 0, 2, -(scale * meanX));
	cvmSet(normalizationTransform, 1, 1, scale);
	cvmSet(normalizationTransform, 1, 2, -(scale * meanY));
	cvmSet(normalizationTransform, 2, 2, 1.0f);
	return normalizedPoints;
}



void BasicReconstructor::LoadCalibrateData()
{
	CvMat* disparityToDepth = (CvMat*)cvLoad("Q.xml");
	_disparityToDepth = disparityToDepth;
}



void BasicReconstructor::LoadProjectionMatrix(QString calibrationResultLocation)
{

	//_projectionMatrix = (CvMat *)cvLoad(calibrationResultLocation.toStdString().c_str());
	ifstream infile(calibrationResultLocation.toStdString().c_str());
	if(infile.is_open())qDebug()<<"open success...";
	else qDebug()<<"open failed...";
	int i;
	float val[5];
	//load projection matrix
	for( i = 0; i < 3 * _numCameras; i++)
	{
		infile >> val[0] >> val[1] >> val[2] >> val[3];
		_projectionMatrix(i,0) = val[0];
		_projectionMatrix(i,1) = val[1];
		_projectionMatrix(i,2) = val[2];
		_projectionMatrix(i,3) = val[3];
	}

	string str = "";
	infile >> str;
	//load distortion kc
	if(str == "DistortionExist")
	{
		for(int i = 0; i < _numCameras; i++)
		{
			infile >> val[0] >> val[1] >> val[2] >> val[3];
			_distortionFactor[i](0) = val[0];
			_distortionFactor[i](1) = val[1];
			_distortionFactor[i](2) = val[2];
			_distortionFactor[i](3) = val[3];
			_distortionFactor[i](4) = 0.0;
		}
	}
	else
	{
		for(int i = 0; i < _numCameras; i++)
		{
			_distortionFactor[i](0) = 0;
			_distortionFactor[i](1) = 0;
			_distortionFactor[i](2) = 0;
			_distortionFactor[i](3) = 0;
			_distortionFactor[i](4) = 0;
		}
	}
	// load camera center
	infile >> str;
	if(str == "CameraCenter")
	{
		for(int i = 0; i < _numCameras; i++)
		{
			infile >> val[0] >> val[1] >> val[2];
			_cameraCenters[i](0) = val[0];
			_cameraCenters[i](1) = val[1];
			_cameraCenters[i](2) = val[2];
		}
	}
	

	infile.close();
//	PrintMatrix(_projectionMatrix); // print to show whether load success
	CalculateIntrinsicPara();
	SetDistortionModel();
	CalculateFundamentalMatrix();
	//	PrintMatrix(_fundamentalMatrix[0][1]);
	//	PrintMatrix(_fundamentalMatrix[0][2]);
	//	PrintMatrix(_fundamentalMatrix[0][3]);
}

void BasicReconstructor::CalculateFundamentalMatrix()
{
	int i, j;
	for(i = 0; i < _numCameras; i++)
	{
		for(j = i + 1; j < _numCameras; j++)
		{
			MatrixXf P1 = _projectionMatrix.block<3, 4>(i * 3, 0);
			MatrixXf P2 = _projectionMatrix.block<3, 4>(j * 3, 0);
			ProjectionToFundamentalMatrix(P1, P2, _fundamentalMatrix[i][j]);
			_fundamentalMatrix[j][i] = _fundamentalMatrix[i][j].transpose();
		}
	}
	//PrintMatrix(_fundamentalMatrix[0][1]);

}


/**************************************************
matlab resouce:http://www.robots.ox.ac.uk/~vgg/hzbook/code/
vgg_F_from_P.m
*****************************************************/
void BasicReconstructor::ProjectionToFundamentalMatrix(const MatrixXf& P1, const MatrixXf& P2, Matrix3f& F)
{
	MatrixXf X1(2, 4);
	MatrixXf X2(2, 4);
	MatrixXf X3(2, 4);
	MatrixXf Y1(2, 4);
	MatrixXf Y2(2, 4);
	MatrixXf Y3(2, 4);

	//P1([1,2],:)  copy to X1
	X1 = P1.block<2,4>(1,0);

	//P1([2,0],:)  copy to X2
	X2.row(0) = P1.row(2);
	X2.row(1) = P1.row(0);

	//P1([0,1],:)  copy to X3
	X3.row(0) = P1.row(0);
	X3.row(1) = P1.row(1);

	//P2([1,2],:)  copy to Y1
	Y1 = P2.block<2,4>(1,0);

	//P2([2,0],:)  copy to Y2
	Y2.row(0) = P2.row(2);
	Y2.row(1) = P2.row(0);

	//P1([0,1],:)  copy to Y3
	Y3.row(0) = P2.row(0);
	Y3.row(1) = P2.row(1);

	Matrix4f temp;
	//calculate result[0,0]
	temp.row(0) = X1.row(0);
	temp.row(1) = X1.row(1);
	temp.row(2) = Y1.row(0);
	temp.row(3) = Y1.row(1);
	F(0, 0) = temp.determinant();

	//calculate result[0,1]
	temp.row(0) = X2.row(0);
	temp.row(1) = X2.row(1);
	temp.row(2) = Y1.row(0);
	temp.row(3) = Y1.row(1);
	F(0, 1) = temp.determinant();

	//calculate result[0,2]
	temp.row(0) = X3.row(0);
	temp.row(1) = X3.row(1);
	temp.row(2) = Y1.row(0);
	temp.row(3) = Y1.row(1);
	F(0, 2) = temp.determinant();

	//calculate result[1,0]
	temp.row(0) = X1.row(0);
	temp.row(1) = X1.row(1);
	temp.row(2) = Y2.row(0);
	temp.row(3) = Y2.row(1);
	F(1, 0) = temp.determinant();

	//calculate result[1,1]
	temp.row(0) = X2.row(0);
	temp.row(1) = X2.row(1);
	temp.row(2) = Y2.row(0);
	temp.row(3) = Y2.row(1);
	F(1, 1) = temp.determinant();

	//calculate result[1,2]
	temp.row(0) = X3.row(0);
	temp.row(1) = X3.row(1);
	temp.row(2) = Y2.row(0);
	temp.row(3) = Y2.row(1);
	F(1, 2) = temp.determinant();

	//calculate result[2,0]
	temp.row(0) = X1.row(0);
	temp.row(1) = X1.row(1);
	temp.row(2) = Y3.row(0);
	temp.row(3) = Y3.row(1);
	F(2, 0) = temp.determinant();

	//calculate result[2,1]
	temp.row(0) = X2.row(0);
	temp.row(1) = X2.row(1);
	temp.row(2) = Y3.row(0);
	temp.row(3) = Y3.row(1);
	F(2, 1) = temp.determinant();

	//calculate result[2,2]
	temp.row(0) = X3.row(0);
	temp.row(1) = X3.row(1);
	temp.row(2) = Y3.row(0);
	temp.row(3) = Y3.row(1);
	F(2, 2) = temp.determinant();
	return ;
}


/************************************************
Epipolar Line constraint:
transpose(pr) * F * pl = 0 
return the k and dist of the line
*************************************************/
LINE BasicReconstructor::CalculateEpipolarLine(const MatrixXf& F, const cv::Point2f pLeft)
{
	//PrintMatrix(F);
	LINE result;	
	Vector3f line;
	Vector3f mat_point;
	mat_point(0,0) = pLeft.x;
	mat_point(1,0) = pLeft.y;
	mat_point(2,0) = 1;
	line = F * mat_point;
	result.a = line(0, 0);
	result.b = line(1, 0);
	result.c = line(2, 0);
	return result;
}



/**********************************************************************
Note: Here is the most important part of the Mocap System.
First, i use >=3 cameras cross validation to validate all the correspondances, 
even if their is only one candicate lies on the epipoloy line, which makes the matching over-constraint,
as a result, we get great marker loss because we kill many valid matching when their are only two cameras can see.

***********************************************************************/

void BasicReconstructor::Find2DMarkerMatching(vector<vector<POI>>& POIsList)
{
	ClearMatchPoint();
	int i, j, k;
	int maxSize = -1;
	int maxIndex = -1;
	int size = POIsList.size();                 //           camera number
	for(i = 0; i < POIsList.size(); i++)
	{
		if((int)POIsList[i].size() > maxSize)
		{
			maxSize = POIsList[i].size();
			maxIndex = i;
		}
	}

	// find all match markers for all the markers in maxIndex
	for( i = 0; i < maxSize; i++)
	{
		Point2f currentMarker = POIsList[maxIndex][i]._coordinates2d;
		_matchPoint[i][maxIndex] = currentMarker;
		int matchedCount = 0;
		vector<Point2f> matchedList; //maybe there are several points lie on the epipolar line . candicate table
		// find all candidates in camrea j.        size == camera number
		for(j = 0; j < size; j++)
		{
			if(j == maxIndex)continue;
			int sub_size = POIsList[j].size();
			matchedCount = 0;
			matchedList.clear();
			// calculate epipolar line
			LINE currentLine = CalculateEpipolarLine(_fundamentalMatrix[maxIndex][j], currentMarker);
			// find all candidate markers
			matchedCount = FindCandidateMarkersInOneCamera(currentLine, POIsList[j], matchedList);
			if(matchedCount  >= 1)
				break;						
		}
		Point2f matchedPoint;
		// if there is only one matched point, we don't need to use cross validation.  because maybe there are only these two cameras can see.
		if(matchedCount == 1)
		{
			matchedPoint = matchedList[0];
			_matchPoint[i][j] = matchedPoint;
			FindOtherMatchMarker(currentMarker, matchedPoint, maxIndex, j, i , POIsList);
		}
		else if(matchedCount > 1)           // there are many markers lie on the epipolar line , need to validate through other camreas
		{
			int m;
			int count = 0;
			for(m = 0; m < matchedList.size(); m++)
			{
				Point2f p = matchedList[m];
				// traverse the other camreas ,validate it is a right match
				count = 0;
				for(int k = 0; k < size; k++)
				{
					if(k== maxIndex || k == j)continue;
					LINE line1 = CalculateEpipolarLine(_fundamentalMatrix[maxIndex][k], currentMarker);
					LINE line2 = CalculateEpipolarLine(_fundamentalMatrix[j][k], p);
					//calculate the intersect of 2 lines
					Point2f intersectPoint = CalculateIntersection(line1, line2);
					if(CameraContainPoint(intersectPoint, POIsList[k]))count++;
				}
				if(count >= 1)break; // if there exsit at least one marker in other cameras		
			}
			if(count >= 1)
			{
				// find matched points in other cameras because we already found the right match in camera : maxIndex, j 
				matchedPoint = matchedList[m];
				_matchPoint[i][j] = matchedPoint;
				FindOtherMatchMarker(currentMarker, matchedPoint, maxIndex, j, i , POIsList);
			}
		}
	}
}

//judge marker on line
bool BasicReconstructor::IsMatch(LINE &line, Point2f & marker)
{
	float dist = (line.a * marker.x + line.b * marker.y + line.c) / sqrt(line.a * line.a + line.b * line.b);
	if(fabs(dist) < Para::markerOnLineThreshold)
		return true;
	return false;

}

//judge the projected point exist in other cameras
bool BasicReconstructor::CameraContainPoint(Point2f& intersect, vector<POI>& POIs)
{
	for(int i = 0; i < POIs.size(); i++)
	{
		if(sqrt((POIs[i]._coordinates2d.x - intersect.x) * (POIs[i]._coordinates2d.x - intersect.x) + (POIs[i]._coordinates2d.y - intersect.y) * (POIs[i]._coordinates2d.y - intersect.y)) < Para::reprojectionThreshold)
			return true;
	}
	return false;
}

// clear the _matchPoint matrix
void BasicReconstructor::ClearMatchPoint()
{
	int i,j;
	for( i = 0; i < Para::markerNum; i++)
		for(j = 0; j < Para::markerNum; j++)

		{
			_matchPoint[i][j].x = -1;
			_matchPoint[i][j].y = -1;
		}
}


//
Point2f BasicReconstructor::CalculateIntersection(LINE &line1, LINE &line2)
{
	Point2f result;
	float a1 = line1.a;
	float b1 = line1.b;
	float c1 = line1.c;
	float a2 = line2.a;
	float b2 = line2.b;
	float c2 = line2.c;

	result.x = (b2 * c1 - b1 * c2)/(a2 * b1 - b2 * a1);
	result.y = (a2 * c1 - a1 * c2)/(b2 * a1 - a2 * b1);
	return result;
}

void BasicReconstructor::FindOtherMatchMarker(const Point2f& p1, const Point2f & p2, int index1, int index2, int currentHandleIndex,vector<vector<POI>>& POIsList)
{
	for(int i = 0; i < _numCameras; i++)
	{
		if(i == index1 || i == index2)continue;
		LINE line1 = CalculateEpipolarLine(_fundamentalMatrix[index1][i], p1);
		LINE line2 = CalculateEpipolarLine(_fundamentalMatrix[index2][i], p2);
		//calculate the intersect of 2 lines
		Point2f intersectPoint = CalculateIntersection(line1, line2);
		for(int j = 0; j < POIsList[i].size(); j++)
		{
			float dist =  sqrt((POIsList[i][j]._coordinates2d.x - intersectPoint.x) * (POIsList[i][j]._coordinates2d.x - intersectPoint.x) + (POIsList[i][j]._coordinates2d.y - intersectPoint.y) * (POIsList[i][j]._coordinates2d.y - intersectPoint.y));
			if(dist < Para::reprojectionThreshold)
			{
				_matchPoint[currentHandleIndex][i] = POIsList[i][j]._coordinates2d;
				break;
			}
		}
	}
}


/***************************************************
use _matchPoint to reconstruct the 3d points: 
p = MP  least square , SVD decomposition
=>  AP = 0, A = [p]x * M      AP = 0 ->   A(1:3)P = A(4);  non-Homogeneous equation system
build system Ax = b       
****************************************************/

vector<POI> BasicReconstructor::Reconstruction()
{


	int i,j;
	vector<POI> result;
	for(i = 0; i < Para::markerNum; i++)
	{
		int count = 0;              //   2d point count used to reconstruct
		for(j = 0; j < Para::markerNum; j++)
		{
			if(_matchPoint[i][j] != Point2f(-1,-1))count++;
		}
		if(count < 2)continue;

		MatrixXf whole_A(3 * count, 4);
		VectorXf b(3 * count);
		MatrixXf A1to3(3 * count, 3);
		Vector3f x;
		count = 0;
		//static int control = 1;
		for(j = 0; j < Para::markerNum; j++)
		{

			if(_matchPoint[i][j] != Point2f(-1,-1))
			{		
				Vector3f point_vec;
				point_vec(0,0) = _matchPoint[i][j].x;
				point_vec(1,0) = _matchPoint[i][j].y;
				point_vec(2,0) = 1;
				Matrix3f antisymmetricMatrix;
				CalculateAntisymmetricMatrix(point_vec, antisymmetricMatrix);
				MatrixXf A(3, 4);
				A = antisymmetricMatrix * _projectionMatrix.block<3, 4>(j * 3, 0);
				//PrintMatrix(A);
				whole_A.block<3, 4>(count * 3 ,0) = A;
				count++;
			}			
		}
		//PrintMatrix(whole_A);
		b = whole_A.col(3);
		A1to3 = whole_A.block(0, 0, 3 * count, 3);
		b= - b;
		
		//	PrintMatrix(A1to3);
		//	PrintMatrix(b);
		long long start = clock();
		JacobiSVD<MatrixXf> svd(A1to3, ComputeThinU | ComputeThinV);
		x = svd.solve(b);
		Vector3f temp = (x - _central);  // using floor calibration
		if(_floorCalibrated)
		{
			temp = _floorRotation * (x - _central);
			temp =  _floorTurnOver * temp;
		}
	
	//	temp =  _floorTurnOver * temp;  // 
	//	solve(A1to3, b, x, DECOMP_SVD);
		long long end = clock();
		//	PrintMatrix(x);
		//	qDebug()<<"slove linear system cost : " << (end - start) /1000;
		POI current3dPoint;
		current3dPoint._coordinates3d.x = temp(0,0);
		current3dPoint._coordinates3d.y = temp(1,0);
		current3dPoint._coordinates3d.z = temp(2,0);	
		result.push_back(current3dPoint);

	}
	return result;
}

/**********************************************************************
floor calibration : calculate floor rotation matrix

tps://en.wikipedia.org/wiki/Rotation_matrix
https://en.wikipedia.org/wiki/Rotation_matrix

**********************************************************************/
void BasicReconstructor::FloorRotationTranslation(vector<POI>& POIList)
{
	if(POIList.size() == 3)
	{
		// calculate the floor normal vector
		CvPoint3D32f p1 = POIList[0]._coordinates3d;
		CvPoint3D32f p2 = POIList[1]._coordinates3d;
		CvPoint3D32f p3 = POIList[2]._coordinates3d;
		Vector3f temp1(p1.x, p1.y, p1.z);
		Vector3f temp2(p2.x, p2.y, p2.z);
		Vector3f temp3(p3.x, p3.y, p3.z);
		Vector3f a(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
		Vector3f b(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
		// floor normal
		Vector3f c(0, 1, 0);
		Vector3f normal = a.cross(b);

		normal = normal / normal.norm();
		Vector3f axis = normal.cross(c);
		axis = axis / axis.norm();
		float cosine = normal.dot(c) / normal.norm() * c.norm();
		float sine = sqrt(1 - cosine * cosine);
		float ux = axis(0, 0);
		float uy = axis(1, 0);
		float uz = axis(2, 0);

		// calculate the rotation from normal vector a to (0, 0, 1)
		_floorRotation(0, 0) = cosine + ux * ux * (1 - cosine);
		_floorRotation(0, 1) = ux * uy * (1 - cosine) - uz * sine;
		_floorRotation(0, 2) = ux * uz * (1 - cosine) + uy * sine;

		_floorRotation(1, 0) = ux * uy * (1 - cosine) + uz * sine;
		_floorRotation(1, 1) = cosine + uy * uy * (1 - cosine);
		_floorRotation(1, 2) = uy * uz * (1 - cosine) - ux * sine;

		_floorRotation(2, 0) = ux * uz * (1 - cosine) - uy * sine;
		_floorRotation(2, 1) = uy * uz * (1 - cosine) + ux * sine;
		_floorRotation(2, 2) = cosine + uz * uz * (1 - cosine);

		//test
		Vector3f xxx = _floorRotation * normal;
//		qDebug () << "normal after rotation:" << xxx(0, 0) << xxx(1, 0) << xxx(2, 0);

		// calculate the translation from central to original
		//_central = (_floorRotation * temp1 + _floorRotation * temp2 + _floorRotation * temp3) / 3;
		_central = temp1;

		Vector3f original(0, 0, 0);
		_floorTranslation = original - _central;

		xxx = _floorRotation * (temp2 - temp1);
		//qDebug () << "p1 after rotation:" << xxx(0, 0) << xxx(1, 0) << xxx(2, 0);

		xxx = _floorRotation * (temp2 - temp1) ;
		//qDebug () << "p2 after rotation:" << xxx(0, 0) << xxx(1, 0) << xxx(2, 0);
		qDebug() << "rotation = ";
		qDebug() << _floorRotation(0, 0) << _floorRotation(0, 1) << _floorRotation(0, 2);
		qDebug() << _floorRotation(1, 0) << _floorRotation(1, 1) << _floorRotation(1, 2);
		qDebug() << _floorRotation(2, 0) << _floorRotation(2, 1) << _floorRotation(2, 2);
		qDebug() << "3 points = ";
		qDebug() << temp1(0, 0) << temp1(1, 0) << temp1(2, 0);
		qDebug() << temp2(0, 0) << temp2(1, 0) << temp2(2, 0);
		qDebug() << temp3(0, 0) << temp3(1, 0) << temp3(2, 0);
		_floorCalibrated = true;
	//	std::cout << " _floorRotation= " << _floorRotation << endl; 
	//	xxx = _floorRotation * (temp1 - _central) + _floorTranslation;
	//	qDebug () << "p3 after rotation:" << xxx(0, 0) << xxx(1, 0) << xxx(2, 0);

	//	xxx = _floorRotation * (_central - _central) + _floorTranslation;
	//	qDebug () << "p3 after rotation:" << xxx(0, 0) << xxx(1, 0) << xxx(2, 0);
		
		//refine camrea centers with rotation and translation
		for(int i = 0; i < _numCameras; i++)
		{	
			_cameraCenters[i] =   _floorRotation * (_cameraCenters[i] - _central);
			_cameraCenters[i] = _floorTurnOver * _cameraCenters[i];
		}
	}
}


void BasicReconstructor::CalculateAntisymmetricMatrix(const Vector3f & t, Matrix3f& antisymmetricMatrix)
{
	antisymmetricMatrix(0,0) = 0;
	antisymmetricMatrix(0,1) = -t(2,0);
	antisymmetricMatrix(0,2) = t(1,0);
	antisymmetricMatrix(1,0) = t(2,0);
	antisymmetricMatrix(1,1) = 0;
	antisymmetricMatrix(1,2) = -t(0,0);
	antisymmetricMatrix(2,0) = -t(1,0);
	antisymmetricMatrix(2,1) = t(0,0);
	antisymmetricMatrix(2,2) = 0;
}

void BasicReconstructor::PrintMatrix(const MatrixXf & mat)
{
	int row = mat.rows();
	int col = mat.cols();
	outfile.open("matrix.txt", ios::app);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			outfile << mat(i,j) << "  ";
		}
		outfile << endl;
	}
	outfile << endl;
	outfile.close();
}

int BasicReconstructor::FindCandidateMarkersInOneCamera(LINE& line, vector<POI> & POIs, vector<Point2f> & matchedList)
{
	int matchedCount = 0;
	int i;
	int size = POIs.size();
	for(i = 0; i < size; i++)
	{
		if(IsMatch(line, POIs[i]._coordinates2d))
		{
			matchedCount++;
			matchedList.push_back(POIs[i]._coordinates2d);
		}
	}
	return matchedCount;
}

void BasicReconstructor::InitMatrix()
{
	//_projectionMatrix.create(3*_numCameras, 4, CV_32F);
	_projectionMatrix.resize(3 * _numCameras, 4);
	for(int i = 0; i < _numCameras; i++)
		_fundamentalMatrix = new Matrix3f*[_numCameras];
	for(int i = 0; i < _numCameras; i++)
		_fundamentalMatrix[i] = new Matrix3f[_numCameras];

	_intrinsicPara = new Matrix3f[_numCameras];
	_distortionFactor = new RowVector5f[_numCameras];
	_cameraCenters = new Vector3f[_numCameras];
	_floorRotation.setZero();
	_floorRotation(0, 0) = 1;
	_floorRotation(1, 1) = 1;
	_floorRotation(2, 2) = 1;

	_floorTurnOver.setZero();
	_floorTurnOver(0, 0) = -1;
	_floorTurnOver(1, 1) = -1;
	_floorTurnOver(2, 2) = -1;
	_floorTranslation.setZero();
	_central.setZero();

}

/******************************************
Note:
transpose(x',y',1) = K * distortion(x,y) * transpose(x, y, 1)
=>
inv(K) * transpose(x',y',1) = distortion(x,y) * transpose(x, y, 1)
*********************************************/ 
void BasicReconstructor::UnDistorted(vector<vector<POI>>& POIsList)
{
/*	for(int i = 0; i < POIsList.size(); i++)
	{
		Matrix3f inv_k = _intrinsicPara[i].inverse();
		for(int j = 0; j < POIsList[i].size(); j++)
		{
			
			POIsList[i][j]._coordinates2d = RetifyLenDistortion(inv_k, POIsList[i][j]._coordinates2d, _distortionFactor[i]);
		}
	}*/
	
	// use optirack API 

	for(int i = 0; i < POIsList.size(); i++)
	{
		for(int j = 0; j < POIsList[i].size(); j++)
		{
			Core::Undistort2DPoint(_distortionModelList[i], POIsList[i][j]._coordinates2d.x, POIsList[i][j]._coordinates2d.y);
		}
	}

}


// my own undistortion code. 
Point2f BasicReconstructor::RetifyLenDistortion(const Matrix3f & inv_k, const Point2f& distortedPoint, const RowVector5f & distortion)
{
	Point2f result;
	Vector3f temp;
	temp(0,0) = distortedPoint.x;
	temp(1,0) = distortedPoint.y;
	temp(2,0) = 1;


	//Mat left;
	Vector3f left;
	left = inv_k * temp;
	float factor = left(1,0) / left(0,0);   // factor == y/x
	float b = (1 + factor * factor);
	VectorXf  polyCoff(8);
	polyCoff(0,0) = distortion(0,4) * b * b * b;
	polyCoff(0,1) = 0;
	polyCoff(0,2) = distortion(0,1) * b * b;
	polyCoff(0,3) = 0;
	polyCoff(0,5) = distortion(0,0) * b;
	polyCoff(0,6) = 0;
	polyCoff(0,7) = -left(0,0);
	Mat root;
	Mat in;
	cv::eigen2cv(polyCoff, in);
	cv::solvePoly(in, root);            // how to!!!!!!!!!! when their are multi roots?

	int nChannels = root.channels();
	// assign the result
	return result;

}


/*****************************************************
Note:
K[R | t] = P
then KR = P(:,1:3)             kT = P(:,4)
K is a upper-triangular matrix
R is a orthogonal matrix
using RQ decomposition just like QR.
http://www.robots.ox.ac.uk/~vgg/hzbook/code/ 
vgg_KR_from_P.m
******************************************************/
KR BasicReconstructor::KRTFromProjectionMatrix(const MatrixXf& P)
{

	Matrix3f H;
	H = P.block<3,3>(0,0);
//	H.transpose();
//	H.reverse();

// QR decomposition
	HouseholderQR<Matrix3f> qr; 
	qr.compute(H.transpose().reverse());
	MatrixXf R = qr.matrixQR().triangularView<Upper>();
	MatrixXf Q = qr.householderQ();
	MatrixXf new_Q = Q.transpose().reverse();
	MatrixXf new_R = R.transpose().reverse();
	KR ans;
	if(new_Q.determinant() < 0 )
	{
		new_Q.col(0) = - new_Q.col(0);
		new_R.row(0) = - new_R.row(0);
	}
	ans.R = new_Q;
	ans.K = new_R;
	return ans;	
}

void BasicReconstructor::CalculateIntrinsicPara()
{
	for(int i = 0; i < _numCameras; i++)
	{
		KR res = KRTFromProjectionMatrix(_projectionMatrix.block<3, 4>(i * 3, 0));
		_intrinsicPara[i] = res.K;
		//PrintMatrix(_intrinsicPara[i]);
	}
}

/********************************
actually, using the default Distortion Model is bad for my reconstruction, because the accuracy is not that good;
so you can choose using the calibrated distortion model or use nothing.
************/
void BasicReconstructor::SetDistortionModel()
{
	_distortionModelList = new Core::DistortionModel[_numCameras];
/*	for(int i = 0; i < _numCameras; i++)
	{
		_distortionModelList[i].Distort = true;
		_distortionModelList[i].HorizontalFocalLength = _intrinsicPara[i](0, 0); // fx
		_distortionModelList[i].VerticalFocalLength = _intrinsicPara[i](1, 1); // fy
		_distortionModelList[i].LensCenterX = _intrinsicPara[i](0, 2); // cx
		_distortionModelList[i].LensCenterY = _intrinsicPara[i](1, 2); // cy
		_distortionModelList[i].KC1 = _distortionFactor[i](0);
		_distortionModelList[i].KC2 = _distortionFactor[i](1);
		_distortionModelList[i].KC3 = _distortionFactor[i](4);
		_distortionModelList[i].Tangential0 = _distortionFactor[i](2);
		_distortionModelList[i].Tangential1 = _distortionFactor[i](3);
	}*/


	// use the Optitrack API   camrea->GetDistortionModel(model)   use default distortion, you can use the calibrated para instead
	for(int i = 0; i < _numCameras; i++)
	{
		_distortionModelList[i].Distort = true;
		_distortionModelList[i].LensCenterX = 640.0;
		_distortionModelList[i].LensCenterY = 512.0;
		_distortionModelList[i].HorizontalFocalLength = 1206.0;
		_distortionModelList[i].VerticalFocalLength = 1206.0;
		_distortionModelList[i].KC1 = 0.1488530039;
		_distortionModelList[i].KC2 = -0.247609;
		_distortionModelList[i].KC3 = 0.1055240035;
		_distortionModelList[i].Tangential0 = 0;
		_distortionModelList[i].Tangential1 = 0;
	}

		
}

Vector3f* BasicReconstructor::GetCameraCenters()
{
	return _cameraCenters;
}