


#include "..\header\Main.h"


static int runGUIMode(Mat original)
{
    GUIMode userInterface = GUIMode::GUIMode();
    cout << &userInterface.isErode;
    userInterface.setOriginalImage(original);
    return userInterface.run();
}

static int runCLUIMode(Mat original)
{
    CLUIMode userInterface = CLUIMode::CLUIMode();
    userInterface.setOriginalImage(original);
    return userInterface.run();
}



int main(int argc, char* argv[]) {
    // Enter the ui option
    cout << "welcome to our Gimp Project, the ui option doesn't use external dependencies, only opencv so feel free to test it" << endl;

    char uiOption;
    cout << "Enter the ui option: \n 1: Command line \n 2: UI" << endl;
    cin >> uiOption;

    // secret option to use existing image
    if (uiOption == '3') {
        Mat original = imread("van_gogh-L.jpg", IMREAD_COLOR);
        runGUIMode(original);
        return 1;
    }

    // Read the image file
    cout << "Enter an image path:" << endl;
    String imageName;
    cin >> imageName;
    Mat original = imread(imageName, IMREAD_COLOR);

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
        runCLUIMode(original);
        return 1;
    }

    if (uiOption == '2') {
        runGUIMode(original);
        return 1;
    }   
}

