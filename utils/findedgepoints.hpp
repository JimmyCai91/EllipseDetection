#ifndef __FINDEDGEPOINTS_H__
#define __FINDEDGEPOINTS_H__

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<CvPoint> findedgepoints( Mat edgemap );

#endif
