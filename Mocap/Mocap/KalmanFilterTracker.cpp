#include "KalmanFilterTracker.h"


KalmanFilterTracker::KalmanFilterTracker(void)
{
}


KalmanFilterTracker::~KalmanFilterTracker(void)
{
}



CvKalman* KalmanFilterTracker::InitKalman(CvPoint2D32f initCoord)
{

	// Kalman initiated with 4 state variables (x, y, velX, velY), 2 measurement or read (x, y) and 0 of control
	CvKalman* kalman = cvCreateKalman( 4, 2, 0 );

	const float dT = 1.0; //0.03; // Talvez devesse ser 1 mesmo, pois sempre ?a veloceidade de 1 quadro pro outro, n�o um tempo real, mas um discreto
	const float A[] = {1,0,dT,0, 0,1,0,dT, 0,0,1,0, 0,0,0,1}; // Transition Matrix (A) or phi
	memcpy( kalman->transition_matrix->data.fl, A, sizeof(A)); // Sets the A matrix

	const float H[] = {1,0,0,0, 0,1,0,0 }; // Measurement matrix, or of transition from measurement to state (H)
	memcpy( kalman->measurement_matrix->data.fl, H, sizeof(H)); // Sets the H matrix

	//Q[] = {0.0001,0,0,0, 0,0.0001,0,0, 0,0,0.0001,0, 0,0,0,0.0001}
	const float Q[] = {0,0,0,0, 0,0,0,0, 0,0,0.2,0, 0,0,0,0.2}; // Transition Error matrix, only to velocities (Q)
	memcpy( kalman->process_noise_cov->data.fl, Q, sizeof(Q)); // Sets the Q matrix

	//R[] = {0.0, 0.0, 0.0, 0.0 }
	const float R[] = {0.2845, 0.0045, 0.0045, 0.0455 }; // Measurement error matrix (R), must don't have
	memcpy( kalman->measurement_noise_cov->data.fl, R, sizeof(R)); // Sets the R matrix

	// Covariance error matrix of value estimation (P)
	float P[] = { 0,0,0,0, 0,0,0,0, 0,0,100,0, 0,0,0,100}; // Initial position error of 0 (sure about position), and a great error of velocity, because uncertainty
	memcpy( kalman->error_cov_post->data.fl, P, sizeof(P)); // Sets the P matrix

	// Sets the initial state of Kalman
	kalman->state_post->data.fl[0] = initCoord.x;
	kalman->state_post->data.fl[1] = initCoord.y;
	kalman->state_post->data.fl[2] = 0.0;
	kalman->state_post->data.fl[3] = 0.0;

	return kalman;
}

void KalmanFilterTracker::RefreshPOIsPosition(map<QString, POI>& currentPOIs, vector<POI>& detectedPOIs, int maxCoordX, int maxCoordY, int &radius)
{

	CvMat* measurement = cvCreateMat(2,1, CV_32FC1);

	//--- For every initialized POI
	for (map<QString, POI>::const_iterator it = currentPOIs.begin(); it != currentPOIs.end(); ++it)
	{

		POI POIToTrack = it->second;

		if (POIToTrack._kalman == NULL)
		{
			POIToTrack._kalman = this->InitKalman(POIToTrack._coordinates2d);
		}

		CvKalman* kalman =  POIToTrack._kalman;

		//Kalman Predict
		const CvMat* predict = cvKalmanPredict(POIToTrack._kalman, 0);

		CvPoint2D32f predictedVelocity = POIToTrack._velocityVector2d;
		CvPoint2D32f predictedPosition; // = POIToTrack.getPredictedPosition();
		predictedPosition.x = (int)predict->data.fl[0];
		predictedPosition.y = (int)predict->data.fl[1];

		POIToTrack._predictedPosition = predictedPosition;

		//predictedVelocity.x = (int)predict->data.fl[2];
		//predictedVelocity.y = (int)predict->data.fl[3];

		if (predictedPosition.x < 0)
		{
			predictedPosition.x = 0;
		}
		else if (predictedPosition.x > maxCoordX)
		{
			predictedPosition.x = maxCoordX;
		}

		if (predictedPosition.y < 0)
		{
			predictedPosition.y = 0;
		}
		else if (predictedPosition.y > maxCoordY)
		{
			predictedPosition.y = maxCoordY;
		}

		//--- Based on predicted position, let's find the nearest detected POI without semantic
		double minDist = std::numeric_limits<double>::max();
		int minDistIndex = -1;

		CvPoint2D32f maxCoord = cvPoint2D32f(maxCoordX, maxCoordY);
		CvPoint2D32f origin = cvPoint2D32f(0.0f, 0.0f);

		//TODO: In kalman it could be extracted from the matrix P
		//TODO: Before the prediction we could dynamically change the matrix Q to vary the search area
		double percentMaxDist = 0.05;
		double maxDist = Calculate2DPointDist(origin, maxCoord) * percentMaxDist;

		// Ajuste da �rea de busca baseado no erro da velocidade
		/*float sum = kalman->error_cov_post->data.fl[0] + kalman->error_cov_post->data.fl[5] + kalman->error_cov_post->data.fl[10] +  kalman->error_cov_post->data.fl[15];
		if (sum > 0.0 && sum < 1.5)
		maxDist = radius = int(sum*100.0);*/

		/*		float muX = sqrt(kalman->error_cov_pre->data.fl[0]);
		float muY = sqrt(kalman->error_cov_pre->data.fl[5]);

		float sum = (muX + muY) / 2.0;
		maxDist = radius = int(sum*100.0);

		cout << "maxDist POSICAO: " << maxDist << endl;
		*/
		float muX = sqrt(kalman->error_cov_pre->data.fl[10]);
		float muY = sqrt(kalman->error_cov_pre->data.fl[15]);

		float sum = (muX + muY) / 2.0;
		maxDist = radius = int(sum*100.0);

		//cout << "maxDist VELOCIDADE: " << maxDist << endl << endl;

		// Ajuste do erro da velocidade X
		kalman->process_noise_cov->data.fl[10] = (abs(predictedVelocity.x)*0.013) + 0.06;
		// Ajuste do erro da velocidade Y
		kalman->process_noise_cov->data.fl[15] = (abs(predictedVelocity.y)*0.013) + 0.06;
		//cout << predictedVelocity.y << "test" << endl;

		//cout << "SUM: " << predictedVelocity.x << endl;

		for (unsigned int i = 0; i < detectedPOIs.size(); i++)
		{

			CvPoint2D32f newPosition = detectedPOIs[i]._coordinates2d;
			double distToNewPosition = Calculate2DPointDist(predictedPosition, newPosition);

			//Search region is the circle with radius maxDist
			if (distToNewPosition < minDist && distToNewPosition < maxDist) {

				minDist = distToNewPosition;
				minDistIndex = i;
			}

		}

		//logDEBUG("minDist: %d", minDist);

		//--- Found correspondence
		if (minDistIndex >= 0)
		{ // Founded a valid point

			CvPoint2D32f measuredPosition = detectedPOIs[minDistIndex]._coordinates2d;

			measurement->data.fl[0] = measuredPosition.x;
			measurement->data.fl[1] = measuredPosition.y;
			//Kalman Correct
			const CvMat* correct = cvKalmanCorrect(POIToTrack._kalman, measurement);

			// New velocity calculated by Kalman
			CvPoint2D32f newVelocity;
			newVelocity.x = correct->data.fl[2];
			newVelocity.y = correct->data.fl[3];
			POIToTrack._velocityVector2d = newVelocity;

			//--- Refreshes POI position
			POIToTrack._coordinates2d = measuredPosition;

			currentPOIs[POIToTrack._semantic] = POIToTrack;


			//--- Removes used detected POI
			std::swap(detectedPOIs[minDistIndex], detectedPOIs[detectedPOIs.size() - 1]);
			detectedPOIs.pop_back();

			//--- Inertia
		} else {

			measurement->data.fl[0] = predictedPosition.x;
			measurement->data.fl[1] = predictedPosition.y;

			//Kalman Correct
			const CvMat* correct = cvKalmanCorrect(POIToTrack._kalman, measurement);

			POIToTrack._coordinates2d = predictedPosition;
			POIToTrack._predictedPosition = predictedPosition;

			// New velocity calculated by Kalman
			CvPoint2D32f newVelocity;
			newVelocity.x = correct->data.fl[2];
			newVelocity.y = correct->data.fl[3];
			POIToTrack._velocityVector2d = newVelocity;
			currentPOIs[POIToTrack._semantic] = POIToTrack;

		}
	}

	cvReleaseMat(&measurement);
}


float KalmanFilterTracker::Calculate2DPointDist(CvPoint2D32f& p1, CvPoint2D32f& p2)
{

	float x = p2.x - p1.x;
	float y = p2.y - p1.y;

	return sqrt((x * x) + (y * y));
}