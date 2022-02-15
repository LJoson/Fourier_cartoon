#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/types_c.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> 
#include <fstream>
#include <math.h>
using namespace cv;
using namespace std;
int main()
{
	Mat src = imread("1.PNG");
	Mat grayImage;
	cvtColor(src, grayImage, CV_BGR2GRAY);  //灰度处理
	GaussianBlur(grayImage, grayImage, Size(3, 3), 0, 0);  //高斯模糊处理
	threshold(grayImage, grayImage, 128, 255, CV_THRESH_BINARY);  //二值化处理
	Mat cannyImage;
	Canny(grayImage, cannyImage, 128, 255, 3);    //提取边缘算子
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//contours为输出的轮廓数据集合
	findContours(cannyImage, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE, Point(0, 0));
	//findContours(grayImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			cout << contours[i][j].x << ", " << contours[i][j].y << ", ";
			ofstream f;
			f.open("2.txt", ios::out | ios::app);
			f << contours[i][j].x << ", " << contours[i][j].y << ", ";
		}
	}
	Mat imageContours = Mat::zeros(src.size(), CV_8UC1);
	Mat Contours = Mat::zeros(src.size(), CV_8UC1);  //绘制
	for (int i = 0; i < contours.size(); i++)
	{
		//contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数
		for (int j = 0; j < contours[i].size(); j++)
		{
			//绘制出contours向量内所有的像素点
			Point P = Point(contours[i][j].x, contours[i][j].y);
			Contours.at<uchar>(P) = 255;
		}

		//输出hierarchy向量内容
		char ch[256];
		sprintf_s(ch, "%d", i);
		string str = ch;
		cout << "向量hierarchy的第" << str << " 个元素内容为：" << endl << hierarchy[i] << endl << endl;

		//绘制轮廓
		drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);
	}
	imshow("Contours Image", imageContours); //轮廓
	imshow("Point of Contours", Contours);   //向量contours内保存的所有轮廓点集
	waitKey(0);

	return 0;
}