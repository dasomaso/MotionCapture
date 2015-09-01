#pragma once

//#ifndef PROFILE_H
//#define PROFILE_H
#include <opencv2/opencv.hpp>


namespace Para
{
	extern int markerNum;   //marker数量，用来在匹配的时候构造表
	extern int scale;
	extern int frameInterval;  // 重建、计算精确度、丢点率的时候，采样间隔
	extern int maxFrame; //采样800帧结束
	extern int  navigationScale;  // navigation tabwidget occupies 1/4 of the width of the screen
	extern int toolBtnSize;  // the ribbon button size = 64*64     , the ribbon height = 90, pixmap size = 36*36
	extern int wandLength;  //wand length = 250mm 
	extern int markerFilterThreshold; // <=20px, we use this to filter noise of  2d points 
	extern int markerOnLineThreshold;  //<=3px , point on line
	extern int reprojectionThreshold; //  <= 3px


	typedef enum VideoStatus
	{
		PLAY_LIVE, //real time capture
		STOP,//stop capture
		CALIBRATE,
		BREAK,  //break the run loop
		DENOISE
	}VideoStatus;

	typedef enum CaptureStatus
	{
		RECONSTRUCTION,
		NON_START,
		STATIC_CALIBRATION,
		FLOOR_CALIBRATION,
		ACCURACY,
		MARKER_LOSS
	}CaptureStatus; 

	typedef struct ACCURACY_TWO_POINTS
	{
		cv::Point3f left;
		cv::Point3f right;
	}STATIC_CALIBRATION_POINTS; 
}


//#define MARKERNUM 20
////#define MAXCAMREAS 4
//#define SCALE 2
////#define EUCLIDEAN_SCALE 103.4255
//#define FRAME_INTERVAL 8
//#define MAX_FRAME 800
//#define toolBtnSize   60   // the ribbon button size = 64*64     , the ribbon height = 90, pixmap size = 36*36
//
//#define CALIBRATION_LENGTH 250   //wand length = 250mm 
//#define MARKER_FILTER_THREHOLD 20   // we use this to filter noise of  2d points 
////#define MAXFUNDAMENTALNUM MAXCAMREAS*MAXCAMREAS
//#define MARKER_ON_LINE_THRESHOLD 3 // the threshold to judge whether a point is locate on a line
//#define REPROJECTION_THRESHOLD 3  // the threshold when the reconstructed 3d point or two epiploar lines project to other cameras to judge if it is the right match
//typedef enum VideoStatus
//{
//	PLAY_LIVE, //real time capture
//	STOP,//stop capture
//	CALIBRATE,
//	BREAK,  //break the run loop
//	DENOISE
//}VideoStatus;
//
//typedef enum CaptureStatus
//{
//	RECONSTRUCTION,
//	NON_START,
//	STATIC_CALIBRATION,
//	ACCURACY,
//	MARKER_LOSS
//}CaptureStatus; 
//
//typedef struct ACCURACY_TWO_POINTS
//{
//	cv::Point3f left;
//	cv::Point3f right;
//}STATIC_CALIBRATION_POINTS; 

//#endif
