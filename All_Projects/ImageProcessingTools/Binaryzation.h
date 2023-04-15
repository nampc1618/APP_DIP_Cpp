#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "IPTExport.h"

class __declspec(dllexport) Binaryzation
{
public:
	static cv::Mat threshold(cv::Mat srcMat, int threshold);
	static cv::Mat thresholdInv(cv::Mat srcMat, int threshold);
};

