#include "EllipseDetection.hpp"
#include "preprocessing.hpp"
#include "findedgepoints.hpp"
#include "fastpdist.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

#define min_majoraxis 20 
#define max_majoraxis 50
#define min_minoraxis 5
#define least_number 30 

using namespace std;
using namespace cv;

double pointdist( CvPoint point1, CvPoint point2 );

int main() {
	
    Mat image = imread("./data/bin_im_for_count14.bmp", 0);

	// get preprocessed image
	Mat edgemap = preprocessing( image );
    cvtColor(image, image, CV_GRAY2BGR);

    dilate(edgemap, edgemap, Mat());
    imshow("Edge Map", edgemap);
    cout << "Edge map dilation" << endl;
    waitKey(0);

    Mat mask = Mat::zeros(edgemap.rows+2, edgemap.cols+2, CV_8U);
    floodFill(edgemap, mask, Point(1,1), 255, 0, Scalar(), Scalar(), 4+(255<<8) + FLOODFILL_MASK_ONLY);
    dilate(mask, mask, Mat());
    erode(mask, mask, Mat());
    dilate(mask, edgemap, Mat());
    edgemap = edgemap - mask;

    imshow("Edge Map", edgemap);
    waitKey(0);

    Mat rgb;
    cvtColor(edgemap, rgb, CV_GRAY2BGR);

	// get edge points
	vector<CvPoint> edgepoints = findedgepoints( edgemap );

	// get pairwise point distance
	Mat dist = fastpdist( edgepoints );

	vector<int> accumulator, copy_accumulator;
	for(int i=0; i<edgepoints.size(); i++)
	{
        for(int j=0; j<edgepoints.size(); j++)
		{
            if(dist.at<double>(i,j) < min_majoraxis)
                continue;
            
            if(dist.at<double>(i,j) > max_majoraxis)
                continue;

            CvPoint centerpoint = cvPoint((edgepoints[i].x+edgepoints[j].x)/2,(edgepoints[i].y+edgepoints[j].y)/2); 	

            /// start voting 
            double majoraxis = pointdist(edgepoints[i],edgepoints[j])/2;
            double minoraxis;
            accumulator.resize(ceil(majoraxis));
			for( int k=0; k<edgepoints.size(); k++ )
			{
                if(pointdist(centerpoint,edgepoints[k]) >= majoraxis)
                    continue;
               
                double f = min(pointdist(edgepoints[i],edgepoints[k]),pointdist(edgepoints[j],edgepoints[k]));
                if(f < min_minoraxis)
                    continue;

                double d = pointdist(centerpoint,edgepoints[k]);

				double costau = (majoraxis*majoraxis+d*d-f*f)/(2*majoraxis*d);
                if(costau >= 1)
                    continue;

				double costau2 = costau*costau;

				double sintau2 = 1-costau2;

				minoraxis = sqrt((majoraxis*majoraxis*d*d*sintau2)/(majoraxis*majoraxis-d*d*costau2));
                if(minoraxis < min_minoraxis)
                    continue;

				if(minoraxis < majoraxis) accumulator[round(minoraxis)]++;						
			}
   
            if (*max_element(accumulator.begin(),accumulator.end()) > least_number)
			{
                cout << "accumulator's size is: " << accumulator.size() << endl;
                for(vector<int>::const_iterator p = accumulator.begin(); p != accumulator.end(); ++p)
                    cout << *p << ' ';
                cout << endl;
 
                double angle = atan2( (edgepoints[i].y - edgepoints[j].y),0.000001+(edgepoints[i].x - edgepoints[j].x) ) * 180 / 3.14;
                minoraxis = distance(accumulator.begin(), max_element(accumulator.begin(), accumulator.end()));
                cout << "end point " << i << " " << edgepoints[i].x << " " << edgepoints[i].y << endl;
                cout << "end point " << j << " " << edgepoints[j].x << " " << edgepoints[j].y << endl;
                cout << "majoraxis: " << majoraxis << ", minoraxis: " << minoraxis << ", angle: " 
                        << angle << ", match points: " << *max_element(accumulator.begin(), accumulator.end()) << endl;

                // mark end points
                circle(rgb, edgepoints[i], 5, Scalar(255,0,0));
                circle(rgb, edgepoints[j], 5, Scalar(255,0,0));
                ellipse(rgb, centerpoint, Size(majoraxis,minoraxis), angle, 0, 360, Scalar(0,255,0), 1);
                ellipse(image, centerpoint, Size(majoraxis,minoraxis), angle, 0, 360, Scalar(0,225,0), 2);
                imshow("Edge Map", rgb);
                waitKey(1);
                
                // clear out this ellipse
                vector<int> points2move;
                for(int k=0; k<edgepoints.size(); k++)
                    if(dist.at<double>(i,k) <= 1.5*majoraxis || dist.at<double>(j,k) <= 1.5*majoraxis)
                    {
                        dist.at<double>(i,k) = max_majoraxis+1;
                        dist.at<double>(j,k) = max_majoraxis+1;
                        points2move.push_back(k);
                    }
                cout<< points2move.size() << " points to move." << endl;
                for(int k=0; k<points2move.size(); k++)
                    for(int kk=0; kk<edgepoints.size(); kk++)
                        dist.at<double>(kk,points2move[k]) = max_majoraxis+1;

			}
            accumulator.clear();
        }
	}

    imshow("Edge Map", image);
    cout <<"Press any key to exit..."<< endl;
    waitKey(0);

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
