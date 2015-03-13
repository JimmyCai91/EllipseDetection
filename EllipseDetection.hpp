#ifndef __ELLIPSEDETECTION_H__
#define __ELLIPSEDETECTION_H__

#include <opencv2/opencv.hpp>

using namespace cv;

class JimEllipse{
public:
	CvPoint center;	// center of ellipse
	
	CvPoint majorpoint1;
	CvPoint majorpoint2;

	double majoraxis; // major axis of ellipse
//	double orientation; // orientation of ellipse	
};

#endif
