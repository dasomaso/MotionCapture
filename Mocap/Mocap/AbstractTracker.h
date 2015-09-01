#pragma once
#include <map>
#include <string>
#include "POIFinder.h"
class AbstractTracker
{
public:
	AbstractTracker(void);
	virtual ~AbstractTracker(void);


	/*!
	 * Refreshes tracked POIs positions. In order to create a Tracker, one must provide
	 * an implementation for this method. Every refreshed POI must be removed from detectedPOIs vector
	 *
	 * @param currentPOIs (reference to a map of initialized POIs in current frame)
	 * @param detectedPOIs (reference to a vector of detected POIs in next frame)
	 * @param maxCoordX maximum value for x coordinate
	 * @param maxCoordY maximum value for y coordinate
	 * @param radius return the radius of the area of search (necessary to tests)
	 */
	virtual void RefreshPOIsPosition(map<QString, POI>& currentPOIs, vector<POI>& detectedPOIs, int maxCoordX, int maxCoordY, int &radius) = 0;

	void RestartTracker();
};

