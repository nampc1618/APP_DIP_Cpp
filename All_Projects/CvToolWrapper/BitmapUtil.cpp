#include "BitmapUtil.h"

//#define USE_PARALLEL
//#ifdef USE_PARALLEL
//using namespace System::Threading::Tasks;
//#endif

using namespace CvToolWrapper;


ref class BitmapCopyHelper
{
	int m_bitmapStride;
	int m_matstep;
	int m_size;
	uchar* m_dstData;
	uchar* m_srcData;
public:
	BitmapCopyHelper(int bitmapStride, int matstep, int size, uchar* dstData, uchar* srcData) :
		m_bitmapStride(bitmapStride), m_matstep(matstep), m_size(size), m_dstData(dstData), m_srcData(srcData) {
	}
	void CopyMat2Bitmap(int row)
	{
		memcpy(
			reinterpret_cast<void*>(&m_dstData[row * m_bitmapStride]),
			reinterpret_cast<void*>(&m_srcData[row * m_matstep]),
			m_size
		);
	}
	void CopyBitmap2Mat(int row)
	{
		memcpy(
			reinterpret_cast<void*>(&m_dstData[row * m_matstep]),
			reinterpret_cast<void*>(&m_srcData[row * m_bitmapStride]),
			m_size
		);
	}
};


Bitmap^ CvToolWrapper::BitmapUtil::MatToBitmap(const cv::Mat& srcMat)
{
	if (srcMat.data == nullptr)
		return nullptr;
	Bitmap^ bmp;
	BitmapData^ data;
	PixelFormat pixF;
	ColorPalette^ plt;

	switch (srcMat.channels())
	{
	case 1:
		pixF = PixelFormat::Format8bppIndexed;
		bmp = gcnew Bitmap(srcMat.cols, srcMat.rows, pixF);
		plt = bmp->Palette;
		for (int i = 0; i < 256; i++)
		{
			plt->Entries[i] = Color::FromArgb(i, i, i);
		}
		bmp->Palette = plt;
		data = bmp->LockBits(System::Drawing::Rectangle(0, 0, srcMat.cols, srcMat.rows), ImageLockMode::WriteOnly, pixF);
		break;
	case 3:
		pixF = PixelFormat::Format24bppRgb;
		bmp = gcnew Bitmap(srcMat.cols, srcMat.rows, pixF);
		data = bmp->LockBits(System::Drawing::Rectangle(0, 0, srcMat.cols, srcMat.rows), ImageLockMode::WriteOnly, pixF);
		break;
	case 4:
		pixF = PixelFormat::Format32bppRgb;
		bmp = gcnew Bitmap(srcMat.cols, srcMat.rows, pixF);
		data = bmp->LockBits(System::Drawing::Rectangle(0, 0, srcMat.cols, srcMat.rows), ImageLockMode::WriteOnly, pixF);
		break;
	}

	uchar* dstData = reinterpret_cast<uchar*>(data->Scan0.ToPointer());
	uchar* srcData = srcMat.data;

	for (int row = 0; row < data->Height; ++row)
	{
		memcpy(reinterpret_cast<void*>(&dstData[row * data->Stride]), reinterpret_cast<void*>(&srcData[row * srcMat.step]), srcMat.cols * srcMat.channels());
	}

	/*Parallel::For(0, data->Height, gcnew Action<int>(
		gcnew BitmapCopyHelper(data->Stride, srcMat.step, srcMat.cols * srcMat.channels(), dstData, srcData), &BitmapCopyHelper::CopyMat2Bitmap));*/

	bmp->UnlockBits(data);
	delete(data);
	return bmp;
}

//void CvToolWrapper::BitmapUtil::Convert::BitmapToByteArray(Bitmap^ bitmap, uchar*& ptr)
//{
//	int cols = bitmap->Width;
//	BitmapData^ bmpData = bitmap->LockBits(System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height), ImageLockMode::ReadOnly, bitmap->PixelFormat);
//
//	uchar* dstData = (uchar*)ptr;
//	uchar* srcData = reinterpret_cast<uchar*>(bmpData->Scan0.ToPointer());
//
//	switch (bmpData->PixelFormat)
//	{
//	case PixelFormat::Format8bppIndexed:
//		for (int row = 0; row < bmpData->Height; row++)
//		{
//			memcpy(reinterpret_cast<void*>(&dstData[row * cols]), reinterpret_cast<void*>(&srcData[row * bmpData->Stride]), cols * 1);
//		}
//		break;
//	case PixelFormat::Format24bppRgb:
//		for (int row = 0; row < bmpData->Height; row++)
//		{
//			memcpy(reinterpret_cast<void*>(&dstData[row * cols]), reinterpret_cast<void*>(&srcData[row * bmpData->Stride]), cols * 3);
//		}
//		break;
//	case PixelFormat::Format32bppRgb:
//		for (int row = 0; row < bmpData->Height; row++)
//		{
//			memcpy(reinterpret_cast<void*>(&dstData[row * cols]), reinterpret_cast<void*>(&srcData[row * bmpData->Stride]), cols * 4);
//		}
//		break;
//	}
//
//	bitmap->UnlockBits(bmpData);
//	delete(bmpData);
//}

//std::auto_ptr<cv::Mat> CvToolWrapper::BitmapUtil::BitmapToMat_Ptr(Bitmap^ bitmap)
//{
//	BitmapData^ bmpData = bitmap->LockBits(System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height), ImageLockMode::ReadOnly, bitmap->PixelFormat);
//	std::auto_ptr<cv::Mat> mat;
//
//	if (bitmap->PixelFormat == PixelFormat::Format8bppIndexed)
//	{
//		mat = std::auto_ptr<cv::Mat>(new cv::Mat(bitmap->Height, bitmap->Width, CV_8UC1));
//	}
//	else if (bitmap->PixelFormat == PixelFormat::Format24bppRgb)
//	{
//		mat = std::auto_ptr<cv::Mat>(new cv::Mat(bitmap->Height, bitmap->Width, CV_8UC3));
//	}
//	else if (bitmap->PixelFormat == PixelFormat::Format32bppRgb)
//	{
//		mat = std::auto_ptr<cv::Mat>(new cv::Mat(bitmap->Height, bitmap->Width, CV_8UC4));
//	}
//
//	uchar* dstData = mat->data;
//	uchar* srcData = reinterpret_cast<uchar*>(bmpData->Scan0.ToPointer());
//
//	/*for (int row = 0; row < data->Height; ++row)
//  {
//	memcpy(reinterpret_cast<void*>(&dstData[row*mat->step]), reinterpret_cast<void*>(&srcData[row*data->Stride]), mat->cols*mat->channels());
//  }*/
//
//	Parallel::For(0, bmpData->Height, gcnew Action<int>(
//		gcnew BitmapCopyHelper(bmpData->Stride, mat->step, mat->cols * mat->channels(), dstData, srcData), &BitmapCopyHelper::CopyBitmap2Mat));
//
//	bitmap->UnlockBits(bmpData);
//	delete(bmpData);
//	return mat;
//}

cv::Mat CvToolWrapper::BitmapUtil::BitmapToMat(Bitmap^ bitmap)
{
	BitmapData^ bmpData = bitmap->LockBits(System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height), ImageLockMode::ReadOnly, bitmap->PixelFormat);
	cv::Mat mat;

	if (bitmap->PixelFormat == PixelFormat::Format8bppIndexed)
	{
		mat = cv::Mat(bitmap->Height, bitmap->Width, CV_8UC1);
	}
	else if (bitmap->PixelFormat == PixelFormat::Format24bppRgb)
	{
		cv::Mat(bitmap->Height, bitmap->Width, CV_8UC3);
	}
	else if (bitmap->PixelFormat == PixelFormat::Format32bppRgb)
	{
		cv::Mat(bitmap->Height, bitmap->Width, CV_8UC4);
	}

	uchar* dstData = mat.data;
	uchar* srcData = reinterpret_cast<uchar*>(bmpData->Scan0.ToPointer());

	for (int row = 0; row < bmpData->Height; ++row)
	{
		memcpy(reinterpret_cast<void*>(&dstData[row * mat.step]), reinterpret_cast<void*>(&srcData[row * bmpData->Stride]), mat.cols * mat.channels());
	}

	/*Parallel::For(0, bmpData->Height, gcnew Action<int>(
		gcnew BitmapCopyHelper(bmpData->Stride, mat.step, mat.cols * mat.channels(), dstData, srcData), &BitmapCopyHelper::CopyBitmap2Mat));*/

	bitmap->UnlockBits(bmpData);
	delete(bmpData);
	return mat;
}

