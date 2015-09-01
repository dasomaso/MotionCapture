#include "POIFinder.h"

double POIFinder::MAX_PERC_AREA_INITIAL_VALUE = 0.00400;
double POIFinder::MIN_PERC_AREA_INITIAL_VALUE = 0.00005;
int POIFinder::THRESHOLD_INITIAL_VALUE = 230;
POIFinder::POIFinder(void)
{
	_minPercArea = MIN_PERC_AREA_INITIAL_VALUE;
	_maxPercArea = MAX_PERC_AREA_INITIAL_VALUE;
	_threshold = THRESHOLD_INITIAL_VALUE;

//	int c = _threshold;
}


POIFinder::~POIFinder(void)
{
}



void POIFinder::CreateBlobs(vector<Blob>& blobs, int nBlobs) 
{
	for (int i = 0; i < nBlobs; i++) {

		Blob b;
		blobs.push_back(b);
	}
}

void POIFinder::FillBlobs(vector<Blob>& blobs, const vector<int>& labelCorrespondence, Image& labels) 
{

	for (int y = 1; y < labels.getHeight() - 1; y++)
	{
		for (int x = 1; x < labels.getWidth() - 1; x++)
		{

			int currentLabel = labels(x, y);
			if (currentLabel > 0) {

				blobs[labelCorrespondence[currentLabel] - 1].AddPoint(x, y);
			}
		}
	}
}

void POIFinder::RemoveBlobsOutsideAreaLimit(vector<Blob>& blobs, const int minNumPixels, const int maxNumPixels)
{

	vector<Blob>::iterator iter;

	for (iter = blobs.begin(); iter != blobs.end();)
	{
		int blobArea = iter->GetArea();
		if (blobArea < minNumPixels || blobArea > maxNumPixels)
		{

			iter = blobs.erase(iter);
		}
		else 
		{
			++iter;
		}
	}
}

vector<Blob> POIFinder::FindBlobs(Image& im)
{

	//--- Allow padding of 1 pixel, limited to 255 labels!!!

	Image labels(im.getWidth() + 1, im.getHeight() + 1);

	vector<Blob> blobs;
	int blobIndex = 1;

	vector<int> labelCorrespondence;
	//Dummy label; index 1 indicates label 1
	labelCorrespondence.push_back(0);
	for (int y = 1; y < im.getHeight(); y++)
	{
		for (int x = 1; x < im.getWidth(); x++) 
		{

			if (im(x,y) >= _threshold) 
			{

				int leftPixel = labels(x - 1, y);
				int upPixel = labels(x, y - 1);
				int upLeftPixel = labels(x - 1, y - 1);

				if (upLeftPixel != BACKGROUND_LABEL)
				{

					labels(x, y) = upLeftPixel;

				} 
				else if (leftPixel == BACKGROUND_LABEL)
				{

					if (upPixel == BACKGROUND_LABEL)
					{

						labels(x, y) = blobIndex;
						labelCorrespondence.push_back(blobIndex);
						blobIndex++;
					}
					else 
					{

						labels(x, y) = upPixel;
					}

				} 
				else if (leftPixel != BACKGROUND_LABEL)
				{

					labels(x, y) = leftPixel;

					//Refresh label correspondence
					if (upPixel != BACKGROUND_LABEL && leftPixel != BACKGROUND_LABEL && leftPixel != upPixel) {

						int labelMax = max(upPixel, leftPixel);
						int labelMin = min(upPixel, leftPixel);

						//If the label doesn't correspond to itself, search for the "root" label
						if (labelCorrespondence[labelMin] != labelMin) {

							labelCorrespondence[labelMax] = labelCorrespondence[labelMin];
						} else {

							labelCorrespondence[labelMax] = labelMin;
						}

					}

				}

			}
		}
	}

	CreateBlobs(blobs, blobIndex);
	FillBlobs(blobs, labelCorrespondence, labels);
	RemoveBlobsOutsideAreaLimit(blobs, _minPercArea * im.getNumberOfPixels(), _maxPercArea * im.getNumberOfPixels());

	return blobs;
}


vector<POI> POIFinder::GetPOIsInImage(IplImage *cv_image)
{

	//Pre-processing
//	Image originalImage(cv_image);
//	Image grayImage = originalImage.getGrayScale();
/*	IplImage *gray_image  = cvCreateImage(cvGetSize(cv_image),cv_image->depth, 1);
	if(cv_image->nChannels == 3)
	{
		cvCvtColor(cv_image, gray_image,CV_BGR2GRAY);

	}
	else
		cvCopyImage(cv_image, gray_image);
	Image grayImage(gray_image);*/
	Image grayImage(cv_image);
	//Core algorithm
	vector<Blob> detectedBlobs = FindBlobs(grayImage);
	
	vector<POI> newCoordinates;
	for (unsigned int i = 0; i < detectedBlobs.size(); i++)
	{
		newCoordinates.push_back(POI(detectedBlobs[i].GetCentroid()));
	
		//cout << "Novo POI: " << endl;
		//Debug::printCvPoint2D32f(newCoordinates[newCoordinates.size()-1].getCoordinates2d());
	};
	return newCoordinates;
}
