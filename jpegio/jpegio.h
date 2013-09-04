#pragma once


#include <stdio.h>
#undef FAR
#include "jpeglib.h"
#include <opencv2/opencv.hpp>
using namespace cv;
#define CV_VERSION_NUMBER CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)

#pragma comment(lib, "opencv_core"CV_VERSION_NUMBER".lib")
#pragma comment(lib, "opencv_highgui"CV_VERSION_NUMBER".lib")
//typedef enum {
//	JDCT_ISLOW,		/* slow but accurate integer algorithm */
//	JDCT_IFAST,		/* faster, less accurate integer method */
//	JDCT_FLOAT		/* floating-point: accurate, fast on fast HW */
//} J_DCT_METHOD;

typedef enum {
	DCT_ISLOW=JDCT_ISLOW,		/* slow but accurate integer algorithm */
	DCT_IFAST=JDCT_IFAST,		/* faster, less accurate integer method */
	DCT_FLOAT=JDCT_FLOAT		/* floating-point: accurate, fast on fast HW */
}DCT_METHOD;
int imencodeJPEG(const Mat& src, uchar* buff, int q, int DCT_MODE, bool isOpt);
int imencodeJPEG(const Mat& src, std::vector<uchar>& buff, int q, int DCT_MODE=DCT_IFAST, bool isOpt=true);
int imdecodeJPEG(const vector<uchar>& buff, Mat& dest);
int imdecodeJPEG(const unsigned char* buff, int buff_size, Mat& dest);