#include "EllipseDetection.hpp"

int main() {

	JimEllipse ellipse;
	ellipse.center = cvPoint(0,0);
	ellipse.major_axis = 10;
	ellipse.minor_axis = 5;
	ellipse.orientation = 0;

	return 0;
}
