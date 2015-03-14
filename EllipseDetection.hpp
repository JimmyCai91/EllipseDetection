#ifndef __ELLIPSEDETECTION_H__
#define __ELLIPSEDETECTION_H__

#include <opencv2/opencv.hpp>

using namespace cv;

class JimEllipse{
public:
	CvPoint center;	// center of ellipse
	double majoraxis; // major axis of ellipse
    double minoraxis; // minor axis of ellipse	
	double angle; // orientation of ellipse	
};

#endif
