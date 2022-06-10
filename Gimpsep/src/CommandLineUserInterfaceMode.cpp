#include "..\header\CommandLineUserInterfaceMode.h"

int CLUIMode::run() {
    while (true) {
        update();
        //  int option;
        cout << 
            "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nEnter the option: \n" <<
            "\n 1: Erode : "<< isErode <<
            "\n 2: Dilate : " << isDilate <<
            "\n 3: Canny edge detection : "<< isCanny <<
            "\n 4: Resize : "<< height <<"x"<<width<<
            "\n 5: Set brightness :"<<brightness<<
            "\n 6: Stitch"<<
            "\n 7: Exit" << endl;

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
            toggleToStitch();
        }
        else if (option == '7') {
            destroyAllWindows;
            return 0;
        }
        else {
            cout << "Option doesn't exist" << endl;
        }

    }
    return 1;
}