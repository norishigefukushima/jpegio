#include "jpegio.h"

int main(int srgc, char** argv)
{
	Mat src = imread("kodim23.png");
	Mat dest;
	vector<uchar> buff;
	imencodeJPEG(src,buff,80, 1,true);
	imdecodeJPEG(buff,dest);

	imshow("jpeg",dest);
	waitKey();
	return 0;
}