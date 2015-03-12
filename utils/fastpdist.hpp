#ifndef __FASTPDIST_H__
#define __FASTPDIST_H__

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat fastpdist( vector<Point>& xy );
/// fastpdist
// 2 points in xy;
// 		| x1-x1	x1-x2 x1-x3 |
// X.^2 =  	| x2-x1 x2-x2 x2-x3 | .^2
// 		| x3-x1 x3-x2 x3-x3 |
// 
//		| y1-y1 y1-y2 y1-y3 |
// Y.^2 = 	| y2-y1 y2-y2 y2-y3 | .^2
// 		| x3-x1 x3-x2 x3-x3 | 
//
// dist = sqrt( X.^2 + Y.^2 )
//
#endif
