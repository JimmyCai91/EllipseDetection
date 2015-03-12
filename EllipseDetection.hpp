#ifndef __ELLIPSEDETECTION_H__
#define __ELLIPSEDETECTION_H__

#include <opencv2/opencv.hpp>

using namespace cv;

class JimEllipse{
public:
	CvPoint center;	// center of ellipse
	double major_axis; // major axis of ellipse
        double minor_axis; // minor axis of ellipse
	double orientation; // orientation of ellipse	
};

#endif
