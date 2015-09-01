#pragma once
#include "POI.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include "Blob.h"
#include "Image.h"
using namespace std;
#define BACKGROUND_LABEL 0
class POIFinder
{
public:
	POIFinder(void);
	~POIFinder(void);

	vector<POI> GetPOIsInImage(IplImage *image);

/*!
	 * Creates the blobs.
	 *
	 * @param blobs A vector containing the blobs.
	 * @param nBlobs Number of blobs to be created.
	 */
	void CreateBlobs(vector<Blob>& blobs, const int nBlobs);

	/*!
	 * Fills the blobs with their labels.
	 *
	 * @param blobs The vector that contains the blobs.
	 * @param labelCorrespondence The label correspondence.
	 * @param labels The blobs labels.
	 */
	void FillBlobs(vector<Blob>& blobs, const vector<int>& labelCorrespondence, Image& labels);

	/*!
	 * Finds the blobs in an image
	 *
	 * @param image The image to be used.
	 *
	 * @return
	 */
	vector<Blob> FindBlobs(Image& image);

	/*!
	 * Removes the blobs outside the area limit.
	 *
	 * @param blobs the vector that contains the blobs.
	 * @param minNumPixels Minimum number of pixels.
	 * @param maxNumPixels Maximum number of pixels.
	 */
	void RemoveBlobsOutsideAreaLimit(vector<Blob>& blobs, const int minNumPixels, const int maxNumPixels);

private:
	

	//! Minimum percentage of image area occupied by the blobs.
	double _minPercArea;

	//! Initial value of _minPercArea.
	static   double MIN_PERC_AREA_INITIAL_VALUE; //0.00005

	//! Maximum percentage of image area occupied by the blobs.
	double _maxPercArea;

	//! Initial value of _maxPercArea.
	static   double MAX_PERC_AREA_INITIAL_VALUE;

	//! Threshold.
	int _threshold;

	//! Initial value of threshold.
	static  int THRESHOLD_INITIAL_VALUE ;
};

