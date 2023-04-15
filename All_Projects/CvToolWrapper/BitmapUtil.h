#pragma once

#include "opencv2/core/core.hpp"

#using <system.drawing.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

namespace CvToolWrapper 
{
	namespace BitmapUtil
	{
	
		Bitmap^ MatToBitmap(const cv::Mat& img);
		cv::Mat BitmapToMat(Bitmap^ bitmap);
		//static void BitmapToByteArray(Bitmap^ bitmap, uchar*& ptr);
		//std::auto_ptr<cv::Mat> BitmapToMat_Ptr(Bitmap^ bitmap);

	};
}

