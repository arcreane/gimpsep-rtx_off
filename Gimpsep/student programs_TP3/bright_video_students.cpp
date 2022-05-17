#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;





int main(int argc, char** argv)
{
    //open the video file for reading
    Mat frame;
    VideoCapture cap("chaplin.mp4");

    // Check if camera opened successfully
    if (!cap.isOpened()) {
        // if not success, exit program
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    
    //Defining window names
    String imageBPlusThiftyWindowName = "increase the brightness by 50";
    String imageBPlusOneHundredWindowName = "increase the brightness by 100";
    String imageBMinusThiftyWindowName = "decrease the brightness by 50";
    String imageBMinusOneHundredWindowName = "decrease the brightness by 100";
    
    String windows[]{ imageBPlusThiftyWindowName ,imageBPlusOneHundredWindowName ,imageBMinusThiftyWindowName ,imageBMinusOneHundredWindowName };
    int assignedBrightness[] = { 50,100,-50,-100 };
    int* ptr = assignedBrightness;
    //Create and open windows for above window names
    
    for(String w: windows){
    namedWindow(w);
    }

    

    while (1) {

        // read a new frame from video
        // Capture frame-by-frame
        cap >> frame;
        //cap.read(frame);

        if (frame.empty()) {
            //Breaking the while loop at the end of the video
            cout << "Video Capture Stoped providing frames" << endl;
            break;
        }

        
        Mat bufferFrame;
        
        for (String w : windows) {
        
        // use pointer to iterate over brightness
        //increase the brightness by 50
        //increase the brightness by 100
        //decrease the brightness by 50
        //decrease the brightness by 100


        frame.convertTo(bufferFrame, -1, 1, *(ptr++));
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
