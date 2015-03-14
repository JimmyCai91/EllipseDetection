#include "findedgepoints.hpp"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<CvPoint> findedgepoints( Mat edgemap )
{
	// accept only char type matrices
	CV_Assert(edgemap.depth() != sizeof(uchar));

	vector<CvPoint> points;
	int nRows = edgemap.rows;
	int nCols = edgemap.cols;

	int i,j;
	uchar* p;

	for(i=0; i<nRows; ++i)
	{
		p = edgemap.ptr<uchar>(i);
		for(j=0; j<nCols; ++j)
		{
			if( p[j] == 255 )
				points.push_back(cvPoint(j,i));
		}
	}

	return points;
}
