#include "jpegio.h"
#include <iostream>

using namespace std;
using namespace cv;

#include "opencvmacro.h"
#pragma CV_LIBRARY(imgproc)
#pragma CV_LIBRARY(imgcodecs)
//#pragma CV_LIBRARY(highgui)

void speedTest(Mat& src, int quality=80, int iteration=10)
{
	cout<<"speed test"<<endl;
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


	cout<<"decode:"<<endl;
	{
		vector<uchar> buff;
		vector<int> param(2);
		param[0]=IMWRITE_JPEG_QUALITY;
		param[1]=q;
		imencode(".jpg",src,buff,param);

		startTime = getTickCount();
		for(int i=0;i<iter;i++)
		{
			Mat dest = imdecode(buff,1);
		}
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"opencv:"<<time*1000.0/iter<<"ms"<<endl;

	{
		vector<uchar> buff;
		imencodeJPEG(src,buff,q,DCT_IFAST,false);
		startTime = getTickCount();
		for(int i=0;i<iter;i++)
		{
			Mat dest;
			imdecodeJPEG(buff,dest);
		}
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(fastest,huffman):"<<time*1000.0/iter<<"ms"<<endl;


	{
		vector<uchar> buff;
		imencodeJPEG(src,buff,q,DCT_FLOAT,false);

		startTime = getTickCount();
		for(int i=0;i<iter;i++)
		{
			Mat dest;
			imdecodeJPEG(buff,dest);
		}
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(slowest,huffman):"<<time*1000.0/iter<<"ms"<<endl;
	{
		vector<uchar> buff;
		imencodeJPEG(src,buff,q,DCT_IFAST,true);

		startTime = getTickCount();
		for(int i=0;i<iter;i++)
		{
			Mat dest;
			imdecodeJPEG(buff,dest);
		}
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(fastest,ac):"<<time*1000.0/iter<<"ms"<<endl;

	{
		vector<uchar> buff;
		imencodeJPEG(src,buff,q,DCT_FLOAT,true);

		startTime = getTickCount();
		for(int i=0;i<iter;i++)
		{
			Mat dest;
			imdecodeJPEG(buff,dest);
		}
	}
	time = (getTickCount()-startTime)/(getTickFrequency());
	cout<<"jpegturbo(slowest,ac):"<<time*1000.0/iter<<"ms"<<endl;
	cout<<endl;
}

void rate_distortionTest(Mat& src)
{
	cout<<"RD test"<<endl;
	for(int q=100;q>30;q-=10)
	{
		cout<<"quality: "<<q<<endl;
		{
			vector<uchar> buff;
			vector<int> param(2);
			param[0]=IMWRITE_JPEG_QUALITY;
			param[1]=q;
			imencode(".jpg",src,buff,param);
			Mat dest = imdecode(buff,1);
			cout<<"opencv              "<<buff.size()<<"byte, "<<PSNR(src,dest)<<"dB"<<endl;
		}
		{
			vector<uchar> buff;
			Mat dest;
			imencodeJPEG(src,buff,q, DCT_FLOAT,false);
			imdecodeJPEG(buff,dest);
			cout<<"jpeg turbo(huffman) "<<buff.size()<<"byte, "<<PSNR(src,dest)<<"dB"<<endl;

		}
		{
			vector<uchar> buff;
			Mat dest;
			imencodeJPEG(src,buff,q, DCT_FLOAT,true);
			imdecodeJPEG(buff,dest);
			cout<<"jpeg turbo(ac)      "<<buff.size()<<"byte, "<<PSNR(src,dest)<<"dB"<<endl;
		}
		cout<<endl;
	}
}

void looptest(Mat& src)
{
	int q = 99;
	cout << "quality: " << q << endl;
	vector<uchar> buff;
	Mat dest;
	imencodeJPEG(src, buff, q, DCT_FLOAT, false);
	while(1)
	{
		/*
		//opencv
		vector<uchar> buff;
		vector<int> param(2);
		param[0] = IMWRITE_JPEG_QUALITY;
		param[1] = q;
		imencode(".jpg", src, buff, param);
		Mat dest = imdecode(buff, 1);
		*/
		//jpeg
		
		imdecodeJPEG(buff, dest);
		
	}
}

int main(int srgc, char** argv)
{
	Mat src = imread("kodim23.png");
	
	speedTest(src, 90 , 10);
	rate_distortionTest(src);
	//looptest(src);

	return 0;
}