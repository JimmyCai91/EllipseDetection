#include "EllipseDetection.hpp"
#include "preprocessing.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	
	Mat image = imread("./data/bin_im_for_count14.bmp", 0);
	
	// get preprocessed image
	Mat dst = preprocessing( image );

	namedWindow( "Edge Map", CV_WINDOW_AUTOSIZE );
	imshow( "Edge Map", dst );

	waitKey(0);

	JimEllipse ellipse;
	ellipse.center = cvPoint(0,0);
	ellipse.major_axis = 10;
	ellipse.minor_axis = 5;
	ellipse.orientation = 0;

	return 0;
}
