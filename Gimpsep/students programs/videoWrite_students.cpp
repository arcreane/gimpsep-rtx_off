#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {

	// Create a VideoCapture object and use camera to capture the video
	// Create a VideoCapture object and open the input file
	// If the input is the web camera, pass 0 instead of the video file name VideoCapture cap(0);
	Mat frame;
	VideoCapture cap;

	int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API

	cap.open(deviceID, apiID);

	// Check if camera opened successfully
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	// Default resolutions of the frame are obtained.The default resolutions are system dependent.
	//int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	//int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	cap >> frame; // load one frame to know size
	Size frameSize = frame.size();

	// Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.

	String file = "outcpp.avi";
	VideoWriter myVideoWriter;
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
	double frameRate = 25.0;
	
	myVideoWriter.open(file, codec, frameRate, frameSize, true);

	if (!myVideoWriter.isOpened()) {
		cerr << "Could not open the output video file for writer\n";
		return -1;
	}

	while (1) {

		// Capture frame-by-frame
		cap >> frame;

		// If the frame is empty, break immediately
		if (frame.empty()) {
			cout << "Video Capture Stoped providing frames" << endl;
			break;
		}

		// Write the frame into the file 'outcpp.avi'
		myVideoWriter.write(frame);

		// Display the resulting frame
		imshow("live", frame);

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}

	// When everything done, release the video capture object
	cap.release();

	// Closes all the frames
	destroyAllWindows();

	return 0;
}
