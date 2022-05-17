#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name VideoCapture cap(0);
  Mat frame;
  VideoCapture cap;

  int deviceID = 0;             // 0 = open default camera
  int apiID = cv::CAP_ANY;      // 0 = autodetect default API

  cap.open(deviceID, apiID);

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  while(1){

    
    // Capture frame-by-frame
    cap >> frame;
    //cap.read(frame);
    
    // If the frame is empty, break immediately
    if (frame.empty()) {
        cout << "Video Capture Stoped providing frames" << endl;
        break;
    }
    // Display the resulting frame
    imshow("live", frame);

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(1);
    if(c==27)
      break;
  }

  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();

  return 0;
}
