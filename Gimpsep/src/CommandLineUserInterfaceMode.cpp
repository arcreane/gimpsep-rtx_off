#include "..\header\CommandLineUserInterfaceMode.h"

int CLUIMode::run() {
    //  int option;
    
    while (true) {
        cout <<
            "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nEnter the option (make sure that the image display window is active): \n" <<
            "\n 1: Erode : " << isErode <<
            "\n 2: Dilate : " << isDilate <<
            "\n 3: Canny edge detection : " << isCanny <<
            "\n 4: Resize : " << height << "x" << width <<
            "\n 5: Set brightness :" << brightness <<
            "\n 6: Stitch" <<
            "\n 7: ExportImage to Png" <<
            "\n 8: Exit" << endl;
        update();
        char option = waitKey(0);
        cout << "please enter an option : " << endl;
        //cin >> option;

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
            cout << "! make sure the console is active when entering field! " << endl;
            cout << "Enter width:" << endl;
            cin >> width;
            cout << "Enter height:" << endl;
            cin >> height;
        }
        else if (option == '5') {
            cout << "! make sure the console is active when entering field! " << endl;
            cout << "Enter brightness value:" << endl;
            cin >> brightness;
        }
        else if (option == '6') {
            cout << "! make sure the console is active when entering field! " << endl;
            toggleToStitch();
        }
        else if (option == '7') {
            cout << "! make sure the console is active when entering field! " << endl;
            exportImage(postProcessedImage);
        }
        else if (option == '8') {
            destroyAllWindows;
            return 0;
        }

        else {
            cout << "Option doesn't exist" << endl;
        }

    }
    return 1;
}
