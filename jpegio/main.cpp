#include "jpegio.h"
#include <iostream>
using namespace std;
void speedTest(Mat& src, int quality=80, int iteration=10)
{
	int iter = iteration;
	int q = quality;

	cout<<"encode:"<<endl;
	int64 startTime = getTickCount();
	for(int i=0;i<iter;i++)
	{
		vector<uchar> buff;
		vector<int> param(2);
		param[0]=IMWRITE_JPEG_QUALITY;
		param[1]=q;
		imencode(".jpg",src,buff,param);
	}
	double time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"opencv:"<<time*1000.0/iter<<"ms"<<endl;

	startTime = getTickCount();
	for(int i=0;i<iter;i++)
	{
		vector<uchar> buff;
		
		imencodeJPEG(src,buff,q,DCT_IFAST,false);
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(fastest,huffman):"<<time*1000.0/iter<<"ms"<<endl;

	startTime = getTickCount();
	for(int i=0;i<iter;i++)
	{
		vector<uchar> buff;
		
		imencodeJPEG(src,buff,q,DCT_FLOAT,false);
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(slowest,huffman):"<<time*1000.0/iter<<"ms"<<endl;

	startTime = getTickCount();
	for(int i=0;i<iter;i++)
	{
		vector<uchar> buff;
		
		imencodeJPEG(src,buff,q,DCT_IFAST,true);
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(fastest,ac):"<<time*1000.0/iter<<"ms"<<endl;

	startTime = getTickCount();
	for(int i=0;i<iter;i++)
	{
		vector<uchar> buff;
		
		imencodeJPEG(src,buff,q,DCT_FLOAT,true);
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(slowest,ac):"<<time*1000.0/iter<<"ms"<<endl;
}
int main(int srgc, char** argv)
{
	Mat src = imread("kodim23.png");
	speedTest(src);
	/*
	Mat dest;
	
	imencodeJPEG(src,buff,80, 1,true);
	imdecodeJPEG(buff,dest);

	imshow("jpeg",dest);
	waitKey();*/
	return 0;
}