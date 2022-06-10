#include "CommandLineMode.h"

int CommandLineMode::run() {
    while (true) {
        update();
        //  int option;
        cout << "Enter the option: \n 1: Erode \n 2: Dilate \n 3: Canny edge detection \n 4: Resize \n 5: Set brightness \n 6: Stitch \n 7: Exit" << endl;
        //          cin >> option;
        char option = (char)waitKey(0);
        cout << "Enter the option:" << option << " , ";
        if (option == 27)
            break;
        if (option == '1') {
            toggleIsErode();
        }
        else if (option == '2') {
            toggleIsDilate();
        }
        else if (option == '3') {
            toggleIsCanny();
        }
        else if (option == '4') {
            cout << "Enter width:" << endl;
            cin >> width;
            cout << "Enter height:" << endl;
            cin >> height;
        }
        else if (option == '5') {
            cout << "Enter brightness value:" << endl;
            cin >> brightness;
        }
        else if (option == '6') {
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
                toggleToStitch();
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
    return 1;
}