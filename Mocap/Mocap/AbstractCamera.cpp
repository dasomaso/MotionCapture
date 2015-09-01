#include "AbstractCamera.h"


AbstractCamera::AbstractCamera(void)
{
}


AbstractCamera::~AbstractCamera(void)
{
}


vector<POI> AbstractCamera::GetPOIs() 
{
	return _POIs;
}

void AbstractCamera::SetPOIs(vector<POI> POIs)
{

	_POIs = POIs;
}

void AbstractCamera::InsertPOI(POI& POItoInsert)
{

	// TODO: Here we need to know if the tracker is kalman, to only in this case initialize kalman, how?
	// Initialze Kalman
	//KalmanFilter kalman;
	//POItoInsert.setKalman( kalman.initKalman(POItoInsert.getPredictedPosition()) );
	
	//_POIs[POItoInsert._semantic] = POItoInsert;
	_POIs.push_back(POItoInsert);
}
