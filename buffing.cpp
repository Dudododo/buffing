#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);

	double scale = 0.5;

	double i_minH = 0;
	double i_maxH = 20;
	double i_minS = 43;
	double i_maxS = 255;
	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat medMat;
		Mat bufMat;
		Mat detectMat;

		//缩放
		cap >> frame;
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		//转换图像格式
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

		rFrame.copyTo(detectMat);

		//限定范围
		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		//均值滤波
		cv::GaussianBlur(rFrame, medMat, cv::Size(7, 7), 3, 3);

		//利用mask只对人脸磨皮
		rFrame.copyTo(bufMat);
		medMat.copyTo(bufMat, detectMat);

		imshow("white: in the range", detectMat);
		imshow("buffing", bufMat);
		imshow("frame", rFrame);

		waitKey(30);
	}
}

