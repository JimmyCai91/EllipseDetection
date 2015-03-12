#include "EllipseDetection.hpp"
#include "preprocessing.hpp"
#include "findedgepoints.hpp"
#include "fastpdist.hpp"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	
	Mat image = imread("./data/bin_im_for_count14.bmp", 0);
	
	// get preprocessed image
	Mat edgemap = preprocessing( image );
	namedWindow( "Edge_Map", CV_WINDOW_AUTOSIZE );
	imshow( "Edge_Map", edgemap );
	waitKey(0);
	
	// get edge points
	vector<CvPoint> edgepoints = findedgepoints( edgemap );
	cout << "Possible major axes: " << edgepoints.size() << " * " 
		<< edgepoints.size() << " = " << edgepoints.size()*edgepoints.size() << endl;

	JimEllipse ellipse;
	ellipse.center = cvPoint(0,0);
	ellipse.major_axis = 10;
	ellipse.minor_axis = 5;
	ellipse.orientation = 0;

	return 0;
}
