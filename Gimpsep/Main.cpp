#include "Main.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "CannyEdgeDetection.h"
#include "DilatationAndErosion.h"
#include "LightenAnDarken.h"
#include "PanoramaStitching.h"

#include <iostream>


using namespace cv;
using namespace std;

int brightness = 50;
int width = 500;
int height = 500;
Mat original,image;
bool isErode = false;
bool isDilate = false;
bool isCanny = false;
bool toStitch = false;
Mat imageToStitch;

Mat3b canvas;

string toolsWindowName = "tools";
Rect buttonDelate;
string buttonDelateText("Delate");
Rect buttonErode;
string buttonErodeText("Erode");
Rect buttonCannydetection;
string buttonCannydetectionText("CannyEdge");
Rect buttonStitch;
string buttonStitchText("Stitch");



Mat resizing(Mat image, int width, int height) {
	Mat resized;
	resize(image, resized, Size(width, height), INTER_LINEAR);
	return resized;
}


static void update() {
    image = lightenAnDarken(original, 1, brightness - 50);
    image = resizing(image, width+10, height+10);
    if (isDilate) {
        image = dilatationAndErosion(image, "dilate");
    }
    if (isErode) {
        image = dilatationAndErosion(image, "erode");
    }
    if (isCanny) {
        image = cannyEdgeDetection(image);
    }
    if (toStitch) {
        image = panoramaStitching(image, imageToStitch);
    }
    imshow("image", image);
}

static void on_trackbar(int, void*) {
    update();
}

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        
        if (buttonDelate.contains(Point(x, y)))
        {
            isDilate = !isDilate;
            rectangle(canvas, buttonDelate, Scalar(0, 0, 255), 2);
        }
        if (buttonErode.contains(Point(x, y)))
        {
            isErode = !isErode;
            rectangle(canvas, buttonErode, Scalar(0, 0, 255), 2);
        }
        if (buttonCannydetection.contains(Point(x, y)))
        {
            isCanny = !isCanny;
            rectangle(canvas, buttonCannydetection, Scalar(0, 0, 255), 2);
        }
        if (buttonStitch.contains(Point(x, y)))
        {
            string imagePath;
            cout << "Enter an image path:" << endl;
            cin >> imagePath;
            imageToStitch = imread(imagePath, IMREAD_COLOR);
            // Check for failure
            if (imageToStitch.empty())
            {
                printf(" No image data \n ");
            }
            else {
                toStitch = true;
            }
            rectangle(canvas(buttonStitch), buttonStitch, Scalar(0, 0, 255), 2);

        }
        update();
    }
    if (event == EVENT_LBUTTONUP)
    {
        if (!isDilate) {
            rectangle(canvas, buttonDelate, Scalar(200, 200, 200), 2);
        }
        if (!isErode) {
            rectangle(canvas, buttonErode, Scalar(200, 200, 200), 2);
        }
        if (!isCanny) {
            rectangle(canvas, buttonCannydetection, Scalar(200, 200, 200), 2);
        }
        if (!toStitch) {
            rectangle(canvas, buttonStitch, Scalar(200, 200, 200), 2);
        }
    }

    imshow(toolsWindowName, canvas);
    waitKey(1);
}

int main(int argc, char* argv[]) {
    // Enter the ui option
    int uiOption;
    cout << "Enter the ui option: \n 1: Command line \n 2: UI" << endl;
    cin >> uiOption;

    // Read the image file
    String imageName;
    cout << "Enter an image path:" << endl;
    cin >> imageName;
    original = imread(imageName, IMREAD_COLOR);
    image = original;

    // Check for failure
    if (original.empty())
    {
        printf(" No image data \n ");
        return -1;
    }

    //create window
    namedWindow("image", WINDOW_AUTOSIZE);

    //show image
    imshow("image", original);

    if (uiOption == 1) {
        while (true) {
            update();
            waitKey(1);
            int option;
            cout << "Enter the option: \n 1: Erode \n 2: Dilate \n 3: Canny edge detection \n 4: Resize \n 5: Set brightness \n 6: Stitch \n 7: Exit" << endl;
            cin >> option;
            if (option==1) {
                isErode = !isErode;
            } else if (option == 2) {
                isDilate = !isDilate;
            } else if (option == 3) {
                isCanny = !isCanny;
            } else if (option == 4) {
                cout << "Enter width:" << endl;
                cin >> width;
                cout << "Enter height:" << endl;
                cin >> height;
            } else if (option == 5) {
                cout << "Enter brightness value:" << endl;
                cin >> brightness;
            } else if (option == 6) {
                string imagePath;
                cout << "Enter an image path:" << endl;
                cin >> imagePath;
                imageToStitch = imread(imagePath, IMREAD_COLOR);
                // Check for failure
                if (imageToStitch.empty())
                {
                    printf(" No image data \n ");
                }
                else {
                    toStitch = true;
                }
            }
            else if (option == 7) {
                destroyAllWindows;
                return 0;
            }
            else {
                cout << "Option doesn't exist" << endl;
            }
        }
    }
    if (uiOption == 2) {
        //create tool window
        namedWindow("tools", WINDOW_AUTOSIZE);

        //create trackBars
        createTrackbar("Brightness", toolsWindowName, &brightness, 100, on_trackbar);
        createTrackbar("Width", toolsWindowName, &width, 1000, on_trackbar);
        createTrackbar("Height", toolsWindowName, &height, 1000, on_trackbar);

        // An image
        Mat3b img(300, 300, Vec3b(0, 255, 0));

        //Buttons
        buttonDelate = Rect(0, 0, img.cols, 50);

        buttonErode = Rect(0, 60, img.cols, 50);

        buttonCannydetection = Rect(0, 120, img.cols, 50);

        buttonStitch = Rect(0, 180, img.cols, 50);

        // The canvas
        canvas = Mat3b(img.rows + buttonDelate.height + buttonErode.height + buttonCannydetection.height + buttonStitch.height, img.cols, Vec3b(0, 0, 0));

        // Draw the button
        canvas(buttonDelate) = Vec3b(200, 200, 200);
        putText(canvas(buttonDelate), buttonDelateText, Point(buttonDelate.width * 0.35, buttonDelate.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));
        canvas(buttonErode) = Vec3b(200, 200, 200);
        putText(canvas(buttonErode), buttonErodeText, Point(buttonErode.width * 0.35, buttonErode.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));
        canvas(buttonCannydetection) = Vec3b(200, 200, 200);
        putText(canvas(buttonCannydetection), buttonCannydetectionText, Point(buttonCannydetection.width * 0.35, buttonCannydetection.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));
        canvas(buttonStitch) = Vec3b(200, 200, 200);
        putText(canvas(buttonStitch), buttonStitchText, Point(buttonStitch.width * 0.35, buttonStitch.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));

        // Setup callback function
        namedWindow(toolsWindowName);
        setMouseCallback(toolsWindowName, callBackFunc);

        //init button
        imshow(toolsWindowName, canvas);


        // Wait for any key stroke
        waitKey(0);

        //destroy all open windows
        destroyAllWindows;
        return 0;
    }
}