//Camera.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Camera.h"

using namespace cv;
using namespace std;

Camera::Camera(int port) {
	//capture camera stream from /dev/video0
	cap = VideoCapture(port);
	if (!cap.isOpened()) {
		cerr << "ERROR: Unable to open the camera" << endl;
	}

	//set camera stream parameters
	cap.set(CV_CAP_PROP_BUFFERSIZE, 3);
	//cap.set(CV_CAP_PROP_FPS,90);
	//cap.set(CV_CAP_PROP_FRAME_WIDTH,720);
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
}

//scale an image up or down
Mat Camera::scaleImage(Mat src, double scaleFactor) {
	//resize image
	Mat resized;
	resize(src, resized, Size(), scaleFactor, scaleFactor, CV_INTER_AREA);

	return resized;
}

//get a raw image from the camera stream
Mat Camera::getRawImage() {
	Mat raw_frame;

	//capture frame from camera stream
	cap >> raw_frame;
    if (raw_frame.empty()) {
    	cerr << "ERROR: Unable to grab from the camera" << endl;
    }

    return raw_frame;
}

//get coordinates for all blobs (TODO: fix copy-paste of getFilteredImage)
vector<Point2f> Camera::getKeypoints() {
	//get scaled image from camera
		Mat scld_frame = getRawImage();
		scld_frame = scaleImage(scld_frame, 0.5);

		//apply HSV filter to detect green ball
		Mat frame;
		cvtColor(scld_frame, frame, COLOR_BGR2HSV);
		inRange(frame, Scalar(33,53,94), Scalar(88,255,254), frame);

		//apply dilation to inflate image
		int dilationSize = 2;
		Mat dElement = getStructuringElement(MORPH_RECT,
				Size(2*dilationSize+1, 2*dilationSize+1),
				Point(dilationSize,dilationSize));
		dilate(frame, frame, dElement);

		//set parameters for blob detection
		SimpleBlobDetector::Params params;
		params.blobColor = 255;

		params.filterByArea = true;
		params.minArea = 150;

		params.filterByCircularity = true;
		params.minCircularity = 0.5;

		//use parameters to create blob detector
		Ptr<SimpleBlobDetector> detector =
		SimpleBlobDetector::create(params);

		vector<KeyPoint> keypoints;
		detector->detect(frame, keypoints);

		//convert from KeyPoint to Point2f
		vector<Point2f> pt2f;
		vector<int> ki;

		for(int i = 0; i < keypoints.size(); i++) {
			ki.push_back(i);
		}

		KeyPoint::convert(keypoints, pt2f, ki);

		return pt2f;
}

//get a blob-filtered image from the camera stream
Mat Camera::getFilteredImage() {
	//get scaled image from camera
	Mat scld_frame = getRawImage();
	scld_frame = scaleImage(scld_frame, 0.5);

	//apply HSV filter to detect green ball
	Mat frame;
	cvtColor(scld_frame, frame, COLOR_BGR2HSV);
	inRange(frame, Scalar(33,53,94), Scalar(88,255,254), frame);

	//apply dilation to inflate image
	int dilationSize = 2;
	Mat dElement = getStructuringElement(MORPH_RECT,
			Size(2*dilationSize+1, 2*dilationSize+1),
			Point(dilationSize,dilationSize));
	dilate(frame, frame, dElement);

	//set parameters for blob detection
	SimpleBlobDetector::Params params;
	params.blobColor = 255;

	params.filterByArea = true;
	params.minArea = 150;

	params.filterByCircularity = true;
	params.minCircularity = 0.5;

	//use parameters to create blob detector
	Ptr<SimpleBlobDetector> detector =
	SimpleBlobDetector::create(params);

	vector<KeyPoint> keypoints;
	detector->detect(frame, keypoints);

	//detect blobs (replace 'frame' with 'scld_frame' for color underlay)
	Mat frame_keypoints;
	drawKeypoints(frame, keypoints, frame_keypoints, Scalar(0,0,255),
	DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	return frame_keypoints;
}
