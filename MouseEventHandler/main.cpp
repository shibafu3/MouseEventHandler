#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300d.lib")            // opencv_core
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300.lib") 
#endif

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <list>

using namespace std;
using namespace cv;




void Mouse(int ev,  int x, int y, int flag,  void *param){
	Mat* image = static_cast<Mat*>(param);
	static Mat temp = (*image).clone();

	static int click = 0;
	static Point pt = Point(0, 0);

	switch (ev){
	case cv::EVENT_MOUSEMOVE:
		if (click){
			*image = (temp).clone();
			circle(*image, Point(x, y), 10, Scalar::all(255), 1, CV_AA);
		}
		break;

	case cv::EVENT_LBUTTONDOWN:
		click = true;

		*image = (temp).clone();
		circle(*image, Point(x, y), 10, Scalar::all(255), 1, CV_AA);
		break;

	case cv::EVENT_LBUTTONUP:
		click = false;
		pt = Point(x, y);

		circle(*image, Point(x, y), 10, Scalar::all(255), 3, CV_AA);
		temp = (*image).clone();
		break;
	}

}



int main(){

	Mat image(Size(512, 512), CV_8UC3, Scalar::all(0));

	namedWindow("image", CV_WINDOW_AUTOSIZE);
	setMouseCallback("image", Mouse, (void *)&image);

	while (1){
		imshow("image", image);
		waitKey(1);
	}




	return 0;
}