#include "Profile.h"



namespace Para
{
	 int markerNum = 40;   //marker������������ƥ���ʱ�����
	 int scale  = 2;
	 int frameInterval = 8;  // �ؽ������㾫ȷ�ȡ������ʵ�ʱ�򣬲������
	 int maxFrame = 800; //����800֡����
	 int  navigationScale = 0.25;  // navigation tabwidget occupies 1/4 of the width of the screen
	 int toolBtnSize = 60;  // the ribbon button size = 64*64     , the ribbon height = 90, pixmap size = 36*36
	 int wandLength = 250;  //wand length = 250mm 
	 int markerFilterThreshold = 20; // <=20px, we use this to filter noise of  2d points 
	 int markerOnLineThreshold = 3;  //<=3px , point on line
	 int reprojectionThreshold = 3; //  <= 3px
}