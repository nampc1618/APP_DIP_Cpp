#include "ImageProcessingToolsWrapper.h"

using namespace CvToolWrapper;

typedef unsigned char byte;

Bitmap^ ImageProcessingToolsWrapper::MatToBitmap(cv::Mat srcMat)
{
#pragma region Convert1
	if (srcMat.data == nullptr)
		return nullptr;
	Bitmap^ bmpimg;
	BitmapData^ data;
	PixelFormat pf;
	ColorPalette^ plt;
	switch (srcMat.channels())
	{
	case 1:
		pf = PixelFormat::Format8bppIndexed;
		bmpimg = gcnew Bitmap(srcMat.cols, srcMat.rows, pf);
		plt = bmpimg->Palette;
		for (int x = 0; x < 256; x++)
		{
			plt->Entries[x] = Color::FromArgb(x, x, x);
		}
		bmpimg->Palette = plt;
		data = bmpimg->LockBits(System::Drawing::Rectangle(0, 0, srcMat.cols, srcMat.rows), ImageLockMode::WriteOnly, pf);
		break;
	case 3:
		pf = PixelFormat::Format24bppRgb;
		bmpimg = gcnew Bitmap(srcMat.cols, srcMat.rows, pf);
		data = bmpimg->LockBits(System::Drawing::Rectangle(0, 0, srcMat.cols, srcMat.rows), ImageLockMode::WriteOnly, pf);
		break;
	case 4:
		pf = PixelFormat::Format32bppArgb;
		bmpimg = gcnew Bitmap(srcMat.cols, srcMat.rows, PixelFormat::Format32bppRgb);
		data = bmpimg->LockBits(System::Drawing::Rectangle(0, 0, srcMat.cols, srcMat.rows), ImageLockMode::WriteOnly, pf);
		break;
	}

	byte* dstData = reinterpret_cast<byte*>(data->Scan0.ToPointer());

	byte* srcData = srcMat.data;

	for (int row = 0; row < data->Height; ++row)
	{
		memcpy(reinterpret_cast<void*>(&dstData[row * data->Stride]), reinterpret_cast<void*>(&srcData[row * srcMat.step]), srcMat.cols * srcMat.channels());
	}

	bmpimg->UnlockBits(data);
	delete(data);
	srcMat.release();
	return bmpimg;
#pragma endregion ConvertType1

#pragma region Convert
	//int stride = srcMat.size().width * srcMat.channels(); //calc the srtide
	//int hDataCount = srcMat.size().height;

	//System::Drawing::Bitmap^ retImg;

	//System::IntPtr ptr(srcMat.data);

	////create a pointer with Stride
	//if (stride % 4 != 0) {//is not stride a multiple of 4?
	//    //make it a multiple of 4 by fiiling an offset to the end of each row

	//    //to hold processed data
	//    uchar* dataPro = new uchar[((srcMat.size().width * srcMat.channels() + 3) & -4) * hDataCount];

	//    uchar* data = srcMat.ptr();

	//    //current position on the data array
	//    int curPosition = 0;
	//    //current offset
	//    int curOffset = 0;

	//    int offsetCounter = 0;

	//    //itterate through all the bytes on the structure
	//    for (int r = 0; r < hDataCount; r++) {
	//        //fill the data
	//        for (int c = 0; c < stride; c++) {
	//            curPosition = (r * stride) + c;

	//            dataPro[curPosition + curOffset] = data[curPosition];
	//        }

	//        //reset offset counter
	//        offsetCounter = stride;

	//        //fill the offset
	//        do {
	//            curOffset += 1;
	//            dataPro[curPosition + curOffset] = 0;

	//            offsetCounter += 1;
	//        } while (offsetCounter % 4 != 0);
	//    }

	//    ptr = (System::IntPtr)dataPro;//set the data pointer to new/modified data array

	//    //calc the stride to nearest number which is a multiply of 4
	//    stride = (srcMat.size().width * srcMat.channels() + 3) & -4;

	//    retImg = gcnew System::Drawing::Bitmap(srcMat.size().width, srcMat.size().height,
	//        stride,
	//        System::Drawing::Imaging::PixelFormat::Format24bppRgb,
	//        ptr);
	//}
	//else {

	//    //no need to add a padding or recalculate the stride
	//    retImg = gcnew System::Drawing::Bitmap(srcMat.size().width, srcMat.size().height,
	//        stride,
	//        System::Drawing::Imaging::PixelFormat::Format8bppIndexed,
	//        ptr);
	//}

	//array<byte>^ imageData;
	//System::Drawing::Bitmap^ output;

	//// Create the byte array.
	//{
	//    System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream();
	//    retImg->Save(ms, System::Drawing::Imaging::ImageFormat::Png);
	//    imageData = ms->ToArray();
	//    delete ms;
	//}

	//// Convert back to bitmap
	//{
	//    System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(imageData);
	//    output = (System::Drawing::Bitmap^)System::Drawing::Bitmap::FromStream(ms);
	//}
	//return output;
#pragma endregion ConvertType2

}

cv::Mat ImageProcessingToolsWrapper::BitmapToMat(Bitmap^ bitmap)
{
	Rectangle rect = Rectangle(0, 0, bitmap->Width, bitmap->Height);

	BitmapData^ bmpData = bitmap->LockBits(rect, ImageLockMode::ReadWrite, bitmap->PixelFormat);

	// data = scan0 is a pointer to our memory block.
	IntPtr data = bmpData->Scan0;

	// step = stride = amount of bytes for a single line of the image
	size_t step = bmpData->Stride;

	// So you can try to get you Mat instance like this:
	cv::Mat mat;

	if (bitmap->PixelFormat == PixelFormat::Format8bppIndexed)
	{
		mat = cv::Mat(bitmap->Height, bitmap->Width, CV_8UC1, data.ToPointer(), step);
	}
	else if (bitmap->PixelFormat == PixelFormat::Format24bppRgb)
	{
		mat = cv::Mat(bitmap->Height, bitmap->Width, CV_8UC3, data.ToPointer(), step);
	}
	else if (bitmap->PixelFormat == PixelFormat::Format32bppRgb)
	{
		mat = cv::Mat(bitmap->Height, bitmap->Width, CV_8UC4, data.ToPointer(), step);
	}
	// Unlock the bits.
	bitmap->UnlockBits(bmpData);
	delete(bmpData);

	return mat;
}

Bitmap^ CvToolWrapper::ImageProcessingToolsWrapper::threshold(Bitmap^ bmp, int threshold)
{
	cv::Mat mat = ImageProcessingToolsWrapper::BitmapToMat(bmp);
	cv::Mat thresh = Binaryzation::threshold(mat, threshold);
	Bitmap^ bmpResutl = ImageProcessingToolsWrapper::MatToBitmap(thresh);
	return bmpResutl;
}

Bitmap^ CvToolWrapper::ImageProcessingToolsWrapper::thresholdInv(Bitmap^ bmp, int threshold)
{
	cv::Mat mat = ImageProcessingToolsWrapper::BitmapToMat(bmp);
	cv::Mat threshInv = Binaryzation::thresholdInv(mat, threshold);
	Bitmap^ bmpResutl = ImageProcessingToolsWrapper::MatToBitmap(threshInv);
	return bmpResutl;
}
//void CvToolWrapper::ImageProcessingToolsWrapper::ShowImage(Bitmap^ bmp, bool isWait, int delay)
//{
//	cv::Mat mat = BitmapUtil::BitmapToMat(bmp);
//	cv::imshow("Window Image", mat);
//	if (isWait)
//		cv::waitKey(delay);
//}
