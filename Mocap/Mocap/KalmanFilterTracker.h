#pragma once
#include "abstracttracker.h"
class KalmanFilterTracker :
	public AbstractTracker
{
public:
	KalmanFilterTracker(void);
	~KalmanFilterTracker(void);

	CvKalman* InitKalman(CvPoint2D32f initCoord);

	/*!
	* \see AbstractTracker::refreshPOIsPosition
	*/
	void RefreshPOIsPosition(map<QString, POI>& currentPOIs, vector<POI>& detectedPOIs, int maxCoordX, int maxCoordY, int &radius);

		/*!
	 * Returns distance between two bidimensional coordinates
	 * @param p1 first point
	 * @param p2 second point
	 * @return
	 */
	 float Calculate2DPointDist(CvPoint2D32f& p1, CvPoint2D32f& p2);

};

