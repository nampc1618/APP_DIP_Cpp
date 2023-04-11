#include "FilterColor.h"
#include <iostream>
#include <string>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


Mat imgHSV, mask;
int hmin = 20, smin = 130, vmin = 146;
int hmax = 110, smax = 255, vmax = 255;

void FilterColor::Filter()
{
	string path = "..\\ImageTest\\beer.jpg";
	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	namedWindow("Trackbars", (640, 200));

	createTrackbar("Hue min", "Trackbars", &hmin, 179);
	createTrackbar("Hue max", "Trackbars", &hmax, 179);
	createTrackbar("Sat min", "Trackbars", &smin, 255);
	createTrackbar("Sat max", "Trackbars", &smax, 255);
	createTrackbar("Val min", "Trackbars", &vmin, 255);
	createTrackbar("Val max", "Trackbars", &vmax, 255);

	while (true)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		Mat kernel = getStructuringElement(MORPH_CROSS, Size(3, 3));
		erode(mask, mask, kernel, Point(-1, -1), 2);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(mask, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

		Mat drawing = Mat::zeros(mask.size(), CV_8UC3);
		for (size_t i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area > 20)
				drawContours(drawing, contours, i, Scalar(0, 0, 255), 1);
		}

		imshow("Source Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image mask", mask);
		imshow("Image drawing", drawing);
		waitKey(2);
	}
}
