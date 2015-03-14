#include "EllipseDetection.hpp"
#include "preprocessing.hpp"
#include "findedgepoints.hpp"
#include "fastpdist.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

#define min_majoraxis 15 
#define max_majoraxis 50
#define least_number 10 

using namespace std;
using namespace cv;

vector<double> pointPointsDist( CvPoint p, vector<CvPoint> pts );
double pointdist( CvPoint point1, CvPoint point2 );

int main() {
	
    Mat image = imread("./data/bin_im_for_count14.bmp", 0);

	// get preprocessed image
	Mat edgemap = preprocessing( image );
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
            /// might be slow
            vector<double> center2edges = pointPointsDist(centerpoint,edgepoints);
            double majoraxis = pointdist(edgepoints[i],edgepoints[j])/2;
            double minoraxis;
            vector<int> thirdPoints;
            for(int k=0; k<center2edges.size(); k++)
                if(center2edges[k] < majoraxis)
                    thirdPoints.push_back(k);
            /// start votion
            accumulator.resize(ceil(majoraxis));
			for( int k=0; k<thirdPoints.size(); k++ )
			{
				double d = center2edges[k];
                double f = pointdist(edgepoints[i],edgepoints[k]);
				{
					double costau = (majoraxis*majoraxis+d*d-f*f)/(2*majoraxis*d);
					double costau2 = costau*costau;
					double sintau2 = 1-costau2;
					minoraxis = sqrt((majoraxis*majoraxis*d*d*sintau2)/(majoraxis*majoraxis-d*d*costau2));
					if(minoraxis < majoraxis) accumulator[round(minoraxis)]++;						
				}
			}
            /// smooth accumulator
            copy_accumulator.resize(accumulator.size()+4);
            copy_accumulator[0]=accumulator[2]; copy_accumulator[1]=accumulator[1];
            copy_accumulator[accumulator.size()+2]=accumulator[accumulator.size()-2];
            copy_accumulator[accumulator.size()+3]=accumulator[accumulator.size()-3];
            for(int k = 0; k<accumulator.size(); k++) 
                accumulator[k] = 0.05*(double)copy_accumulator[k] + 0.2*(double)copy_accumulator[k+1] + 0.5*(double)copy_accumulator[k+2] +
                    0.2*(double)copy_accumulator[k+3] + 0.05*(double)copy_accumulator[k+4];

			if (*max_element(accumulator.begin(),accumulator.end()) > least_number)
			{
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
                imshow("Edge Map", rgb);
                waitKey(1);
                
                // clear out this ellipse
                vector<int> points2move;
                for(int k=0; k<edgepoints.size(); k++)
                    if(dist.at<double>(i,k) <= 1.5*majoraxis)
                    {
                        dist.at<double>(i,k) = 0;
                        points2move.push_back(k);
                    }
                for(int k=0; k<edgepoints.size(); k++)
                    if(dist.at<double>(j,k) <= 1.5*majoraxis)
                    {
                        dist.at<double>(j,k) = 0;
                        points2move.push_back(k);
                    }
                cout<< points2move.size() << " points to move." << endl;
                for(int k=0; k<points2move.size(); k++)
                    for(int kk=0; kk<edgepoints.size(); kk++)
                        dist.at<double>(points2move[k],kk) = 0;
			}
            accumulator.clear();
        }
	}

    cout <<"Press any key to exit..."<< endl;
    waitKey(0);

	return 0;
}

vector<double> pointPointsDist( CvPoint p, vector<CvPoint> pts )
{
    vector<double> ds;
    ds.resize(pts.size());
    for(int i=0; i<pts.size(); i++)
        ds[i] = pointdist(p,pts[i]);

    return ds;
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
