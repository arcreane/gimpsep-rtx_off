#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//general considerations about brightness and contrast:
//we can observe that on a black and white image contrast and brighness have similar effects.
//however in both cases information is lost when we need to apply saturation. 

int main(int argc, char** argv)
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

    //Defining window names
    String imageBPlusThiftyWindowName = "increase the contrast to 2";
    String imageBPlusOneHundredWindowName = "increase the contrast to 4";
    String imageBMinusThiftyWindowName = "decrease the contrast to 0.5";
    String imageBMinusOneHundredWindowName = "decrease the contrast to 0.25";

    String windows[]{ imageBPlusThiftyWindowName ,imageBPlusOneHundredWindowName ,imageBMinusThiftyWindowName ,imageBMinusOneHundredWindowName };
    double assignedContrast[] = { 2,4,0.5,0.25 };
    double* ptr = assignedContrast;
    //Create and open windows for above window names

    for (String w : windows) {
        namedWindow(w);
    }



    while (1) {

        // read a new frame from video
        // Capture frame-by-frame
        cap >> frame;

        if (frame.empty()) {
            //Breaking the while loop at the end of the video
            cout << "Video Capture Stoped providing frames" << endl;
            break;
        }


        Mat bufferFrame;

        for (String w : windows) {

            // use pointer to iterate over contrast
            //increase the contrast by 2
            //increase the contrast by 4
            //decrease the contrast by 0.5
            //decrease the contrast by 0.25


            frame.convertTo(bufferFrame, -1, *(ptr++),0 );
            //cout << "brigthnesslevelof "<< w<<"at" << *assignedBrightness << endl;

            //Show above frames inside the created windows.
            imshow(w, bufferFrame);
        }
        ptr -= 4;//return pointer to point to first slot of the assigned brigthness array


        //wait for for 10 ms until any key is pressed.
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop
        //If any key is not pressed withing 10 ms, continue the loop
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
    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;
}