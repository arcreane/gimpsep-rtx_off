#include "..\header\Main.h"


int runGUIMode(Mat original)
{
    GUIMode userInterface = GUIMode::GUIMode();
    cout << &userInterface.isErode;
    userInterface.setOriginalImage(original);
    return userInterface.run();
}

int runCLUIMode(Mat original)
{
    CLUIMode userInterface = CLUIMode::CLUIMode();
    userInterface.setOriginalImage(original);
    return userInterface.run();
}



int main(int argc, char* argv[]) {
    // Enter the ui option
    cout << "Welcome to our Gimp Project, the ui option doesn't use external dependencies, only opencv so feel free to test it" << endl;

    char uiOption;
    cout << "Enter the ui option: \n 1: Command line \n 2: Graphic \n 3: Test Sample (GUI)" << endl;
    cin >> uiOption;

    // Secret option to use an existing image directly
    if (uiOption == '3') {
        Mat original = imread("van_gogh-L.jpg", IMREAD_COLOR);
        runGUIMode(original);
        return 1;
    }

    // Read the image file
    String fullImagePath;
    cout << "Enter an image path:" << endl;
    cin >> fullImagePath;
    Mat original = imread(fullImagePath, IMREAD_COLOR);

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

