#include "EllipseDetection.hpp"
#include "preprocessing.hpp"
#include "findedgepoints.hpp"
#include "fastpdist.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

#define least_distance 20
#define least_number 6

using namespace std;
using namespace cv;

double pointdist( CvPoint point1, CvPoint point2 );

int main() {
	
//	Mat image = imread("./data/bin_im_for_count14.bmp", 0);
//	
//	// get preprocessed image
//	Mat edgemap = preprocessing( image );
        Mat edgemap = imread("./data/bin_im_for_count14_edgemap_2.png", 0);
//	namedWindow( "Edge_Map", CV_WINDOW_AUTOSIZE );
//	imshow( "Edge_Map", edgemap );
//	waitKey(0);

	// get edge points
	vector<CvPoint> edgepoints = findedgepoints( edgemap );
	cout << "Possible major axes: " << edgepoints.size() << " * " 
		<< edgepoints.size() << " = " << edgepoints.size()*edgepoints.size() << endl;
	
	// get pairwise point distance
	Mat dist = fastpdist( edgepoints );
	cout << "distance Mat row: " << dist.rows << " and column: " << dist.cols << endl;

	vector<JimEllipse> ellipses;
	JimEllipse ellipse;
	vector<int> accumulator;

	for(int i=0; i<edgepoints.size(); i++)
	{
		for(int j=0; j<edgepoints.size(); j++)
		{
			if( dist.at<double>(i,j) > least_distance )
			{
				CvPoint centerpoint = cvPoint((edgepoints[i].x+edgepoints[j].x)/2,(edgepoints[i].y+edgepoints[j].y)/2); 	
				double majoraxis = dist.at<double>(i,j)/2;
				accumulator.resize(ceil(majoraxis));

				for( int k=0; k<edgepoints.size(); k++)
				{
					double d = pointdist(centerpoint,edgepoints[k]);
					double f = min(pointdist(edgepoints[i],edgepoints[k]),pointdist(edgepoints[j],edgepoints[k]));
					if( min(d,f) > least_distance && max(d,f) < majoraxis )
					{
						double costau = (majoraxis*majoraxis + d*d - f*f)/(2*majoraxis*d);
						double costau2 = costau*costau;
						double sintau2 = 1 - costau2;
						double minoraxis = (majoraxis*majoraxis*d*d*sintau2)/(majoraxis*majoraxis-d*d*costau2);
						if( sqrt(minoraxis) < majoraxis )
							accumulator[round(sqrt(minoraxis))]++;						
					}
				}
				if (*max_element(accumulator.begin(),accumulator.end()) > least_number)
				{
					ellipse.center = centerpoint;
					ellipse.majorpoint1 = edgepoints[i];
					ellipse.majorpoint2 = edgepoints[j];
					ellipse.majoraxis = majoraxis;
                    ellipses.push_back(ellipse);
				}
			}
		}
	}

	cout << "found ellipse: " << ellipsesize() << endl;

	return 0;
}

double pointdist( CvPoint point1, CvPoint point2 )
{
	double dist;
	double p1x, p1y, p2x, p2y;
	p1x = point1.x; p1y = point1.y;
	p2x = point2.x; p2y = point2.y;

	dist = sqrt((p1x-p2x)*(p1x-p2x) + (p1y-p2y)*(p1y-p2y));

	return dist;
}
