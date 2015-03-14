#include "EllipseDetection.hpp"
#include "preprocessing.hpp"
#include "findedgepoints.hpp"
#include "fastpdist.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iterator>
#include <ctime>
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

    cout << "Edge map dilation..." << endl;
    dilate(edgemap, edgemap, Mat());
    imshow("Edge Map", edgemap);
    waitKey(200);

    Mat mask = Mat::zeros(edgemap.rows+2, edgemap.cols+2, CV_8U);
    cout << "Mask..." << endl;
    floodFill(edgemap, mask, Point(1,1), 255, 0, Scalar(), Scalar(), 4+(255<<8) + FLOODFILL_MASK_ONLY);
    imshow("Edge Map", mask);
    waitKey(200);

    cout<< "Closing operation..." << endl;
    dilate(mask, mask, Mat());
    erode(mask, mask, Mat());
    imshow("Edge Map", mask);
    waitKey(200);

    cout << "Edge map result..." << endl;
    dilate(mask, edgemap, Mat());
    edgemap = edgemap - mask;
    imshow("Edge Map", edgemap);
    waitKey(200);

    Mat rgb;
    cvtColor(edgemap, rgb, CV_GRAY2BGR);

    cout << "Collecting edge points..." << endl;
	vector<CvPoint> edgepoints = findedgepoints( edgemap );

    cout << "Edge points randomize..." << endl;
    random_shuffle(edgepoints.begin(),edgepoints.end());

    cout << "Calculation distance map..." << endl;
	Mat dist = fastpdist( edgepoints );
    dist.convertTo(dist,CV_32S);

	vector<long> accumulator;
    accumulator.resize(max_majoraxis);
    Point centerpoint;
    double majoraxis, minoraxis;
    double f, d, costau, costau2, sintau2, angle;
    int i, j, k, kk;
    int num_edgepoints = edgepoints.size();
    clock_t t;
    t = clock();
	for(i=0; i<num_edgepoints; ++i)
	{
        for(j=i+1; j<num_edgepoints; ++j)
		{
            if(dist.at<int>(i,j) < min_majoraxis)
                continue;
            if(dist.at<int>(i,j) > max_majoraxis)
                continue;
            centerpoint = cvPoint((edgepoints[i].x+edgepoints[j].x)/2,(edgepoints[i].y+edgepoints[j].y)/2); 	

            /// start voting 
            majoraxis = pointdist(edgepoints[i],edgepoints[j])/2;
			for(k=0; k<num_edgepoints; ++k)
			{
                if(pointdist(centerpoint,edgepoints[k]) >= majoraxis)
                    continue;
                f = min(pointdist(edgepoints[i],edgepoints[k]),pointdist(edgepoints[j],edgepoints[k]));
                if(f < min_minoraxis)
                    continue;
                d = pointdist(centerpoint,edgepoints[k]);
				costau = (majoraxis*majoraxis+d*d-f*f)/(2*majoraxis*d);
                if(costau >= 1)
                    continue;
				costau2 = costau*costau;
                sintau2 = 1-costau2;
				minoraxis = sqrt((majoraxis*majoraxis*d*d*sintau2)/(majoraxis*majoraxis-d*d*costau2));
                if(minoraxis < min_minoraxis)
                    continue;
				if(minoraxis < majoraxis) accumulator[round(minoraxis)]++;						
			}
            
            if (*max_element(accumulator.begin(),accumulator.end()) > least_number)
			{
//                cout << "accumulator's size is: " << accumulator.size() << endl;
//                for(vector<int>::const_iterator p = accumulator.begin(); p != accumulator.end(); ++p)
//                    cout << *p << ' ';
//                cout << endl;
 
                angle = atan2((edgepoints[i].y-edgepoints[j].y),0.001+(edgepoints[i].x-edgepoints[j].x))*57;
                minoraxis = distance(accumulator.begin(), max_element(accumulator.begin(), accumulator.end()));
//                cout << "end point " << i << " " << edgepoints[i].x << " " << edgepoints[i].y << endl;
//                cout << "end point " << j << " " << edgepoints[j].x << " " << edgepoints[j].y << endl;
//                cout << "majoraxis: " << majoraxis << ", minoraxis: " << minoraxis << ", angle: " 
//                        << angle << ", match points: " << *max_element(accumulator.begin(), accumulator.end()) << endl;

                // mark end points
//                circle(rgb, edgepoints[i], 3, Scalar(255,0,0));
//                circle(rgb, edgepoints[j], 3, Scalar(255,0,0));
//                ellipse(rgb, centerpoint, Size(majoraxis,minoraxis), angle, 0, 360, Scalar(0,255,0), 1);
                ellipse(image, centerpoint, Size(majoraxis,minoraxis), angle, 0, 360, Scalar(0,225,0), 2);
//                imshow("Edge Map", rgb);
//                waitKey(1);
                
                // clear out this ellipse
                for(k=0; k<num_edgepoints; ++k)
                    if(dist.at<int>(i,k) <= 1.5*majoraxis || dist.at<int>(j,k) <= 1.5*majoraxis)
                        for(kk=0; kk<num_edgepoints; ++kk)
                            dist.at<int>(kk,k) = max_majoraxis+1;

			}
            accumulator.assign(max_majoraxis,0);
        }
	}
    t = clock() - t;
    cout << "It took " << (float)t/CLOCKS_PER_SEC << " seconds..." << endl;  
    imshow("Edge Map", image);
    cout <<"Press any key to exit..."<< endl;
    waitKey(0);

	return 0;
}

inline double pointdist( CvPoint point1, CvPoint point2 )
{
	double dist;
	double p1x, p1y, p2x, p2y;
	p1x = point1.x; p1y = point1.y;
	p2x = point2.x; p2y = point2.y;

	dist = sqrt((p1x-p2x)*(p1x-p2x) + (p1y-p2y)*(p1y-p2y));

	return dist;
}
