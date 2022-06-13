#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int main() {
	Mat src = imread("D:/OpenCV/picture zone/yuntu.png");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow("input",CV_WINDOW_AUTOSIZE);
	imshow("input",src);

	Mat blur_image;
	GaussianBlur(src, blur_image, Size(15, 15), 0, 0);
	imshow("GaussianBlur", blur_image);


	Mat src_gray;
	cvtColor(blur_image,src_gray,COLOR_BGR2GRAY);
	//equalizeHist(src_gray,src_gray);
	imshow("src_gray",src_gray);

	Mat src_binary;
	threshold(src_gray,src_binary,0,255,THRESH_BINARY|THRESH_TRIANGLE);
	imshow("binary",src_binary);

	Mat src_close;
	Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3),Point(-1,-1));
	morphologyEx(src_binary,src_close,MORPH_CLOSE,kernel,Point(-1,-1),2);
	imshow("close",src_close);

	//≤È’“¬÷¿™
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	findContours(src_close, contours,hireachy,CV_RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());

	Mat dst = Mat::zeros(src.size(),CV_8UC3);
	double area;
	double len;
	for (size_t i = 0; i < contours.size(); i++)
	{
		//…∏—°
		Rect rect = boundingRect(contours[i]);
		if (rect.width < src.cols / 2)
		{
			continue;
		}
		if (rect.width > src.cols + 20)
		{
			continue;
		}

		//º∆À„
		area = contourArea(contours[i]);
		len = arcLength(contours[i],true);


		drawContours(dst , contours, static_cast<int>(i),Scalar(0,0,255),2,8,hireachy,0);

	}
	imshow("output",dst);
	printf("area = %f,len = %f\n",area,len);


	waitKey(0);
	return 0;
}