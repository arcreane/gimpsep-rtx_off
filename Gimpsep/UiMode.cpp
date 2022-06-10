#include "UiMode.h"

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
                rectangle(canvas(buttonStitch), buttonStitch, Scalar(0, 0, 255), 2);
            }
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
}