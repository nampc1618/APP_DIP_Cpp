#pragma once
#include "../ImageProcessingTools/Binaryzation.h"
#include "BitmapUtil.h"

//#include "opencv2/videoio/videoio.hpp"
//#include "opencv2/highgui/highgui.hpp"

namespace CvToolWrapper
{
	public ref class ImageProcessingToolsWrapper
	{
	private:
		static cv::Mat BitmapToMat(Bitmap^ srcBmp);
		static Bitmap^ MatToBitmap(cv::Mat srcMat);
	public:
		static Bitmap^ threshold(Bitmap^ bmp, int threshold);
		static Bitmap^ thresholdInv(Bitmap^ bmp, int threshold);
		//static void ShowImage(Bitmap^ bmp, bool isWait, int delay);
	};
}


