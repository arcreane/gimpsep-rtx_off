//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

static void on_trackbar(int, void*)
{
}

int main(int argc, char* argv[])
{
    //open the video file for reading
    Mat frame;
    VideoCapture cap("chaplin.mp4");

    // if not success, exit program
    if (!cap.isOpened()) {
        // if not success, exit program
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    
    
     //define original and rotate window name
    const String originalWindow = "original";
    const String rotatedWindow = "rotated";
    const String trackbarWindow = "trackbarWindow"; 
    namedWindow(trackbarWindow, WINDOW_AUTOSIZE); // Create Window

    int iAngle = 180;
    int * ptriAngle = &iAngle;
    //create track bar
    createTrackbar(trackbarWindow, rotatedWindow, ptriAngle, 360, on_trackbar);

    while (1)
    {
        

 // read a new frame from video
        cap >> frame;

 //if not success, break loop
        if (frame.empty())
 {
                       cout << "Cannot read the frame from video file" << endl;
                       break;
        }
        imshow(originalWindow, frame);
        //show the two video
       
        //get the affine transformation matrix 2D

        // Rotate the image using warpAffine
        
        //show the rotate frame



        //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        int pressedKey = waitKey(10);
        if (pressedKey != 27)
        {
            continue;
        }
        else
        {
            cout << "escape key is pressed by user. ending video" << endl;
            break;
        }
    }

    return 0;
}
