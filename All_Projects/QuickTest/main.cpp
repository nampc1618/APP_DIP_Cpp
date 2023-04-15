#include <iostream>
#include <string>
#include "FilterColor.h"
#include "Binaryzation.h"
#include "IPTExport.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	/*FilterColor filter; 
	filter.Filter();*/

	cv::Mat mat = cv::imread("..\\ImageTest\\hotgirl.jpeg");

	cv::Mat thresh = Binaryzation::threshold(mat, 120);
	cv::namedWindow("Display Window", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Window", thresh);

	cv::waitKey(0);
	return 0;
}