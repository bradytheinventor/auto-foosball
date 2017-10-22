//Camera.h
#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Camera {
public:
	Camera(int port);
	cv::Mat scaleImage(cv::Mat src, double scaleFactor);
	cv::Mat getRawImage();
	std::vector<cv::Point2f> getKeypoints();
	cv::Mat getFilteredImage();

private:
	cv::VideoCapture cap;
};

#endif
