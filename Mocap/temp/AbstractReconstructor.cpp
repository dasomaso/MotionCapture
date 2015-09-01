/*!
 * Abstract class for reconstruction algorithms.
 *
 * \name AbstractReconstructor
 * \author David Lunardi Flam
 * \version
 * \since 03/14/2009
 */
#include "AbstractReconstructor.h"

AbstractReconstructor::AbstractReconstructor(int numCameras)
{
	_numCameras = numCameras;
	_projectionMatrix.create(3*_numCameras, 4, CV_32F);

}


void AbstractReconstructor::computePointArrays(map<QString, POI> firstCameraPOIs, map<QString, POI> secondCameraPOIs,
		CvMat* points1, CvMat* points2, int width, int height) {

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

void AbstractReconstructor::computePointArrays(vector<map<QString, POI> >& CameraPOIs, vector<CvMat*>& points, int width, int height)
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

CvMat* AbstractReconstructor::compute3dHomogeneousCoordinates(CvMat* projectionMatrix1, CvMat* projectionMatrix2,
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

CvMat* AbstractReconstructor::compute3dHomogeneousCoordinates(vector<CvMat*>& projectionMatrix, vector<CvPoint2D32f>& points) 
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

void AbstractReconstructor::LoadProjectionMatrix(QString calibrationResultLocation)
{
	
	//_projectionMatrix = (CvMat *)cvLoad(calibrationResultLocation.toStdString().c_str());
	ifstream infile(calibrationResultLocation.toStdString().c_str());
	if(infile.is_open())qDebug()<<"open success...";
	else qDebug()<<"open failed...";
	int i;
	float val[4];
	for( i = 0; i < _numCameras; i++)
	{
		infile >> val[0] >> val[1] >> val[2] >> val[3];
		_projectionMatrix.at<float>(i,0) = val[0];
		_projectionMatrix.at<float>(i,1) = val[1];
		_projectionMatrix.at<float>(i,2) = val[2];
		_projectionMatrix.at<float>(i,3) = val[3];

	}
	infile.close();
}

void AbstractReconstructor::CalculateFundamentalMatrix()
{
	int i, j;
	int size = _numCameras * (_numCameras - 1) / 2;
	for(i = 0; i < size; i++)
	{

		for(j = i + 1; j < size; j++)
		{
			
			_fundamentalMatrix[i][j].create(3, 3, CV_32F);
			cv::Mat mat1 = _projectionMatrix(cv::Rect(i * 3, 0, 4, 3));
			cv::Mat mat2 = _projectionMatrix(cv::Rect(j * 3, 0, 4, 3));
			ProjectionToFundamentalMatrix(mat1, mat2, _fundamentalMatrix[i][j]);
		}
	}

}


// i has not done the projection to fundamental yet

/**************************************************
matlab resouce:http://www.robots.ox.ac.uk/~vgg/hzbook/code/
vgg_F_from_P.m
*****************************************************/
void AbstractReconstructor::ProjectionToFundamentalMatrix(cv::Mat& mat1, cv::Mat& mat2, cv::Mat& result)
{
	cv::Mat X1,X2,X3,Y1,Y2,Y3;
	X1.create(2,4,CV_32F);
	X2.create(2,4,CV_32F);
	X3.create(2,4,CV_32F);
	Y1.create(2,4,CV_32F);
	Y2.create(2,4,CV_32F);
	Y3.create(2,4,CV_32F);
	//mat1(1,2)  copy to X1
	mat1.row(1).copyTo(X1.row(0));
	mat1.row(2).copyTo(X1.row(1));

	//mat1(2,0)  copy to X2
	mat1.row(2).copyTo(X2.row(0));
	mat1.row(0).copyTo(X2.row(1));

	//mat1(0,1)  copy to X2
	mat1.row(0).copyTo(X3.row(0));
	mat1.row(1).copyTo(X3.row(1));

	//mat2(1,2)  copy to Y1
	mat2.row(1).copyTo(Y1.row(0));
	mat2.row(2).copyTo(Y1.row(1));

	//mat2(2,0)  copy to Y2
	mat2.row(2).copyTo(Y2.row(0));
	mat2.row(0).copyTo(Y2.row(1));

	//mat2(0,1)  copy to Y2
	mat2.row(0).copyTo(Y3.row(0));
	mat2.row(1).copyTo(Y3.row(1));

	cv::Mat  temp;
	temp.create(4,4, CV_32F);

	//calculate result[0,0]
	temp.row(0) = X1.row(0);
	temp.row(1) = X1.row(1);
	temp.row(2) = Y1.row(0);
	temp.row(3) = Y1.row(1);
	result.at<float>(0, 0) = determinant(temp);

	//calculate result[0,1]
	temp.row(0) = X2.row(0);
	temp.row(1) = X2.row(1);
	temp.row(2) = Y1.row(0);
	temp.row(3) = Y1.row(1);
	result.at<float>(0, 1) = determinant(temp);

	//calculate result[0,2]
	temp.row(0) = X3.row(0);
	temp.row(1) = X3.row(1);
	temp.row(2) = Y1.row(0);
	temp.row(3) = Y1.row(1);
	result.at<float>(0, 2) = determinant(temp);

	//calculate result[1,0]
	temp.row(0) = X1.row(0);
	temp.row(1) = X1.row(1);
	temp.row(2) = Y2.row(0);
	temp.row(3) = Y2.row(1);
	result.at<float>(1, 0) = determinant(temp);

	//calculate result[1,1]
	temp.row(0) = X2.row(0);
	temp.row(1) = X2.row(1);
	temp.row(2) = Y2.row(0);
	temp.row(3) = Y2.row(1);
	result.at<float>(1, 1) = determinant(temp);

	//calculate result[1,2]
	temp.row(0) = X3.row(0);
	temp.row(1) = X3.row(1);
	temp.row(2) = Y2.row(0);
	temp.row(3) = Y2.row(1);
	result.at<float>(1, 2) = determinant(temp);

	//calculate result[2,0]
	temp.row(0) = X1.row(0);
	temp.row(1) = X1.row(1);
	temp.row(2) = Y3.row(0);
	temp.row(3) = Y3.row(1);
	result.at<float>(2, 0) = determinant(temp);

	//calculate result[2,1]
	temp.row(0) = X2.row(0);
	temp.row(1) = X2.row(1);
	temp.row(2) = Y3.row(0);
	temp.row(3) = Y3.row(1);
	result.at<float>(2, 1) = determinant(temp);

	//calculate result[2,2]
	temp.row(0) = X3.row(0);
	temp.row(1) = X3.row(1);
	temp.row(2) = Y3.row(0);
	temp.row(3) = Y3.row(1);
	result.at<float>(2, 2) = determinant(temp);

	return ;
	
}

/************************************************
Epipolar Line constraint:
transpose(pr) * F * pl = 0 
return the k and dist of the line
*************************************************/
LINE AbstractReconstructor::CalculateEpipolarLine(cv::Mat& F, cv::Point2f pLeft)
{
	LINE result;	
	Mat line;
	line.create(1, 3, CV_32F);
	Mat mat_point;
	mat_point.create(1, 3, CV_32F);
	mat_point.at<float>(0,0) = pLeft.x;
	mat_point.at<float>(0,1) = pLeft.y;
	mat_point.at<float>(0,2) = 1;
	cv::multiply(F, mat_point, line);
	float a = line.at<float>(0, 0);
	float b = line.at<float>(0, 1);
	float c = line.at<float>(0, 2);
	result.k = -a/(b+1e-6);
	result.dist = -c/(b+1e-6);
	return result;
}

