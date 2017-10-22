#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Motor.h"
#include "Player.h"
#include "Camera.h"

using namespace std;
using namespace cv;

int main() {
	//create objects
	Motor m = Motor(0, 1, 2, 3);
	Camera c = Camera(0);
    Player p = Player(0, 200, 0, 1, 2, 3);

    // Move player to 500mm location
    p.moveTo(-1);
 
	//main program loop
	while(1) {
		//get blob positions from camera
		vector<Point2f> points = c.getKeypoints();

		if(points.size() > 0) {
			cout << points[0].x << ", " << points[0].y << endl;
		}

		//get processed image from camera
		Mat img = c.getFilteredImage();

		//display image
		imshow("Foosball", img);

		//wait for exit keypress
		int key = cv::waitKey(1);
		key = (key==255) ? -1 : key; //#Solve bug in 3.2.0
		if (key>=0)
			break;
	}

	return 0;
}
