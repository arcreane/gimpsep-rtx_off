

#include <opencv2/opencv.hpp>
#include <iostream>

#include "..\header\Main.h"
#include "..\AbstractUserInterfaceMode.h"
#include "..\GraphicUserInterfaceMode.h"
#include "..\CommandLineUserInterfaceMode.h"
#include "..\header\PanoramaStitching.h"


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


static int runGUIMode()
{
    GUIMode userInterface = GUIMode::GUIMode();
    return userInterface.run();
}

static int runCLUIMode()
{
    CLUIMode userInterface = CLUIMode::CLUIMode();
    return userInterface.run();
}



int main(int argc, char* argv[]) {
    // Enter the ui option
    cout << "welcome to our Gimp Project, the ui option doesn't use external dependencies, only opencv so feel free to test it" << endl;

    cout << "Enter the ui option: \n 1: Command line \n 2: UI" << endl;
    char uiOption;
    while (1) {
        uiOption = (char)waitKey(1000);
        if (uiOption == '1' || uiOption == '2') {
            break;
        }
    }

    // Read the image file
    cout << "Enter an image path:" << endl;
    String imageName;
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

    if (uiOption == '1') {
        runCLUIMode();
        return 1;
    }

    if (uiOption == '2') {
        runGUIMode();
        return 1;
    }
}

