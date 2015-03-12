#include "preprocessing.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 *  * @function CannyThreshold
 *   * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 *    */
void CannyThreshold(int, void*)
{
	/// Reduce noise with a kernel 3x3
	blur( src_gray, detected_edges, Size(3,3) );
	 
	/// Canny detector
	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

        /// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	detected_edges.copyTo( dst );
	imshow( window_name, dst );
}

Mat preprocessing( Mat inMap )
{
	Mat src;
	src.create( inMap.size(), inMap.type() );
	inMap.copyTo( src );
	
	/// Convert the image to grayscale
	if( src.dims == 3 ) 
		cvtColor( src, src_gray, CV_BGR2GRAY );
	else
	{
		src_gray.create( src.size(), src.type() );
		src.copyTo( src_gray );
	}


	/// Creat a window
	namedWindow( window_name, CV_WINDOW_AUTOSIZE );

	/// Create a Trackbar for user to enter threshold
	createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

	/// Show the image
	CannyThreshold(0,0);

	/// Wait until user exit program by pressing a key
	waitKey(0);

	return dst;
}
