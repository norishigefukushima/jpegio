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

void generateJPEGData(Mat& src, int num_frame)
{
	double sigma = 10.0;
	Mat s, d;
	Mat dest;
	vector<Mat> vs;
	vector<Mat> ds(3);
	src.convertTo(s, CV_32F);
	Mat n(s.size(), CV_32F);
	split(s, vs);

	for (int i = 0; i < num_frame; i++)
	{
		randn(n, 0, sigma);
		ds[0] = vs[0] + n;
		ds[1] = vs[1] + n;
		ds[2] = vs[2] + n;
		merge(ds, d);
		d.convertTo(dest, src.type());
		cv::imwrite(format("images/%05d.jpg", i), dest);
	}
}

void imreadJPEG(string name, Size size, Mat& dest)
{
	FILE* fp = fopen(name.c_str(), "rb");

	uchar* buff = new uchar[size.area()*1.5];
	int bs = fread(buff, sizeof(uchar), size.area()*1.5, fp);
	imdecodeJPEG(buff, bs, dest);
	fclose(fp);
	delete[] buff;
}

void readJPEGTest()
{
	int num_frame = 300;
	auto startTime = getTickCount();
	for (int i = 0; i < num_frame; i++)
	{
		Mat a = cv::imread(format("images/%05d.jpg", i));
	}
	cout << "opencv       : " << (getTickCount() - startTime) / (getTickFrequency()) * 1000.0 / num_frame << "ms" << endl;
	
	startTime = getTickCount();
#pragma omp parallel for
	for (int i = 0; i < num_frame; i++)
	{
		Mat a = cv::imread(format("images/%05d.jpg", i));
	}
	cout << "opencv    omp: " << (getTickCount() - startTime) / (getTickFrequency()) * 1000.0 / num_frame << "ms" << endl;
	
	startTime = getTickCount();
	for (int i = 0; i < num_frame; i++)
	{
		Mat dest;
		imreadJPEG(format("images/%05d.jpg", i), Size(3840,2160), dest);
	}
	cout << "jpegturbo    : " << (getTickCount() - startTime) / (getTickFrequency()) * 1000.0 / num_frame << "ms" << endl;
	
	startTime = getTickCount();
#pragma omp parallel for
	for (int i = 0; i < num_frame; i++)
	{
		Mat dest;
		imreadJPEG(format("images/%05d.jpg", i), Size(3840, 2160), dest);
	}
	cout << "jpegturbo omp: " << (getTickCount() - startTime) / (getTickFrequency()) * 1000.0 / num_frame << "ms" << endl;
}

int main(int srgc, char** argv)
{
	//Mat src = imread("4k.jpg");
	//generateJPEGData(src, 300); return 0;
	//readJPEGTest(); return 0;

	Mat src = imread("kodim23.png");
	speedTest(src, 90 , 10);
	rate_distortionTest(src);
	//looptest(src);

	return 0;
}