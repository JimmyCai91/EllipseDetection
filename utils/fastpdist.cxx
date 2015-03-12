#include "fastpdist.hpp"

using namespace std;
using namespace cv;

Mat fastpdist( vector<Point>& _xy )
{	
	// vector contains at least 2 points
	CV_Assert(_xy.size() > 1);

	// copy points
	vector<Point> xy = _xy;
	
	// create X and Y matrix
	Mat X, Y;
	X.create(xy.size(), xy.size(), CV_64F);
	Y.create(xy.size(), xy.size(), CV_64F);

	// use for loop at first
	int nRows = X.rows;
	int nCols = X.cols * X.channels();

//	if(I.isContinuous())
//	{
//		nCols *= Rows;
//		nRows = 1;
//	}

	int i,j;
	double* p;
	for(i=0; i<nRows; i++)
	{
		p = X.ptr<double>(i);
		for(j=0; j<nCols; j++)
		{
			p[j] = xy[j].x;
		}
	}

	for(i=0; i<nRows; i++)
	{
		p = Y.ptr<double>(i);
		for(j=0; j<nCols; j++)
		{
			p[j] = xy[j].y;
		}
	}
	
	Mat X_transpose, Y_transpose;
	transpose(X, X_transpose);
	subtract(X, X_transpose, X);
	transpose(Y, Y_transpose);
	subtract(Y, Y_transpose, Y);
	
	// square X and Y matrix
	pow(X,2,X);
	pow(Y,2,Y);

	// get distance matrix
	Mat dist;
	add(X,Y,dist);
	sqrt(dist, dist);

	return dist;
}
