#include "..\header\GraphicUserInterfaceMode.h"


struct StaticOpenCVCallBackHandler { // is used to use static methodes within the UIMode object
    GUIMode &mode;

    // static  function
    static void callback(int event, int x, int y, int flags, void* userdata) {
        StaticOpenCVCallBackHandler* handler = (StaticOpenCVCallBackHandler*)userdata; // cast user data back to "this"
        handler->real_callback(event, x, y, flags);
    }
    // class member function
    void real_callback(int event, int x, int y, int flags) { 
        mode.uiCallbackFunction(event, x, y, flags);
    }

    // static trackbar call back function
    static void on_trackbar(int pos, void* userptr) {
        StaticOpenCVCallBackHandler* handler = (StaticOpenCVCallBackHandler*)userptr; // cast user data back to "this"
        handler->real_on_trackbar();
    }
    // class member function
    void real_on_trackbar() {
       mode.update();
    }
};

void GUIMode::on_trackbar(int, void*) {
    update();
}

void GUIMode::uiCallbackFunction(int event, int x, int y, int flags) {
    if (event == EVENT_LBUTTONDOWN)
    {
        if (buttonDilate.contains(Point(x, y)))
        {
            toggleIsDilate();
            rectangle(canvas, buttonDilate, Scalar(0, 0, 255), 2);
            imshow(toolsWindowName, canvas);
        }
        if (buttonErode.contains(Point(x, y)))
        {
            toggleIsErode();
            rectangle(canvas, buttonErode, Scalar(0, 0, 255), 2);
            imshow(toolsWindowName, canvas);
        }
        if (buttonCannydetection.contains(Point(x, y)))
        {
            toggleIsCanny();
            rectangle(canvas, buttonCannydetection, Scalar(0, 0, 255), 2);
            imshow(toolsWindowName, canvas);
        }
        if (buttonStitch.contains(Point(x, y)))
        {
            toggleToStitch();
            rectangle(canvas, buttonStitch, Scalar(0, 0, 255), 2);
            imshow(toolsWindowName, canvas);
        }
        if (buttonExport.contains(Point(x, y)))
        {
            exportImage(postProcessedImage);
            imshow(toolsWindowName, canvas);
        }
        update();
    }
    if (event == EVENT_LBUTTONUP)
    {
        if (!isDilate) {
            rectangle(canvas, buttonDilate, Scalar(200, 200, 200), 2);
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
    return;
}

int GUIMode::run() {
    //create tool window
    namedWindow("tools", WINDOW_AUTOSIZE);

    //create trackBars
    StaticOpenCVCallBackHandler handler = { *this };
    createTrackbar("Brightness", toolsWindowName, &brightness, 100, StaticOpenCVCallBackHandler::on_trackbar, (void*)(&handler));
    createTrackbar("Width", toolsWindowName, &width, 1000, StaticOpenCVCallBackHandler::on_trackbar, (void*)(&handler));
    createTrackbar("Height", toolsWindowName, &height, 1000, StaticOpenCVCallBackHandler::on_trackbar, (void*)(&handler));
    createTrackbar("Dilation", toolsWindowName, &dilation, 21, StaticOpenCVCallBackHandler::on_trackbar, (void*)(&handler));
    createTrackbar("Erosion", toolsWindowName, &erosion, 21, StaticOpenCVCallBackHandler::on_trackbar, (void*)(&handler));

    // An image
    Mat3b img(300, 300, Vec3b(0, 255, 0));

    //Buttons
    buttonDilate = Rect(0, 0, img.cols, 50);
    buttonErode = Rect(0, 60, img.cols, 50);
    buttonCannydetection = Rect(0, 120, img.cols, 50);
    buttonStitch = Rect(0, 180, img.cols, 50);
    buttonExport = Rect(0, 280, img.cols, 50);

    // The canvas
    canvas = Mat3b(img.rows + buttonDilate.height + buttonErode.height + buttonCannydetection.height + buttonStitch.height, img.cols, Vec3b(0, 0, 0));

    // Draw the button
    canvas(buttonDilate) = Vec3b(200, 200, 200);
    putText(canvas(buttonDilate), buttonDilateText, Point(buttonDilate.width * 0.35, buttonDilate.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));
    canvas(buttonErode) = Vec3b(200, 200, 200);
    putText(canvas(buttonErode), buttonErodeText, Point(buttonErode.width * 0.35, buttonErode.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));
    canvas(buttonCannydetection) = Vec3b(200, 200, 200);
    putText(canvas(buttonCannydetection), buttonCannydetectionText, Point(buttonCannydetection.width * 0.35, buttonCannydetection.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));
    canvas(buttonStitch) = Vec3b(200, 200, 200);
    putText(canvas(buttonStitch), buttonStitchText, Point(buttonStitch.width * 0.35, buttonStitch.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));
    canvas(buttonExport) = Vec3b(200, 200, 200);
    putText(canvas(buttonExport), buttonExportText, Point(buttonExport.width * 0.35, buttonExport.height * 0.7), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0));

    // Setup callback function
    namedWindow(toolsWindowName);
    // Mount back the parameters
    setMouseCallback(toolsWindowName, StaticOpenCVCallBackHandler::callback, (void*)(&handler));
    //init button
    imshow(toolsWindowName, canvas);

    while ((cv::waitKey() & 0xEFFFFF) != 27); //27 is the keycode for ESC
    destroyAllWindows;

    return 1;
}
