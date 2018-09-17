#pragma once

#include <stdio.h>
#undef FAR
#include "include/jpeglib.h"
#include <opencv2/opencv.hpp>

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

int imencodeJPEG(const cv::Mat& src, uchar* buff, int q, int DCT_MODE, bool isOpt);
int imencodeJPEG(const cv::Mat& src, std::vector<uchar>& buff, int q, int DCT_MODE=DCT_IFAST, bool isOpt=true);
int imdecodeJPEG(const std::vector<uchar>& buff, cv::Mat& dest);
int imdecodeJPEG(const unsigned char* buff, int buff_size, cv::Mat& dest);