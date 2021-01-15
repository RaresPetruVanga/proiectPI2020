#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <conio.h>
#include <iostream>
#include "Header.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	const string x = "video.mp4";

	VideoCapture video;

	video = VideoCapture(x);

	if (!video.isOpened()) cout << "FAIL";
	
	cv::Mat frame;

	int frameWidth = video.get(cv::CAP_PROP_FRAME_WIDTH);
	
	int frameHeigth = video.get(cv::CAP_PROP_FRAME_HEIGHT);

	Byte* img1 = (Byte*)malloc(frameWidth * frameHeigth * 3 * sizeof(Byte));

	Byte* img2 = (Byte*)malloc(frameWidth * frameHeigth * 3 * sizeof(Byte));

	cv::Mat result;

	video.read(frame);
	 
	Byte* rez;

	memcpy(img1, frame.data, frame.rows * frame.cols * 3);

	system("cls");

	int nr1;

	while (video.read(frame)) {

		memcpy(img2, frame.data, frame.rows * frame.cols * 3);

		rez = PipeLine(&img1, &img2, frameHeigth, frameWidth);

		result = cv::Mat(frame.rows, frame.cols, CV_8UC1, rez);

		memcpy(img1, frame.data, frame.rows * frame.cols * 3);

		frame = cv::Mat(frame.rows, frame.cols, CV_8UC3, img2);

		cv::imshow("Video", frame);

		cv::imshow("Video feed", result);

		if (cv::waitKey(25) >= 0) break;

		free(rez);

	}

	video.release();

	cv::destroyAllWindows();

	return 0;
}