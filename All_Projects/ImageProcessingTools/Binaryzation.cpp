#include "Binaryzation.h"

cv::Mat Binaryzation::threshold(cv::Mat srcMat, int threshold)
{
    cv::Mat thresh;
    if (srcMat.channels() == 3 || srcMat.channels() == 4)
    {
        cv::cvtColor(srcMat, srcMat, cv::COLOR_BGR2GRAY);
    }
    cv::threshold(srcMat, thresh, threshold, 255, cv::THRESH_BINARY);
    return thresh;
}

cv::Mat Binaryzation::thresholdInv(cv::Mat srcMat, int threshold)
{
    cv::Mat threshInv;
    if (srcMat.channels() == 3 || srcMat.channels() == 4) 
    {
        cv::cvtColor(srcMat, srcMat, cv::COLOR_BGR2GRAY);
    }
    cv::threshold(srcMat, threshInv, threshold, 255, cv::THRESH_BINARY_INV);
    return threshInv;
}
