#include "Main.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int brightness = 50;
int width = 500;
int height = 500;
Mat original,image;

Mat3b canvas;

string toolsWindowName = "tools";
Rect buttonDelate;
string buttonDelateText("buttonDelate");
Rect buttonErode;
string buttonErodeText("buttonErode");
Rect buttonCannydetection;
string buttonCannydetectionText("buttonCannydetection");
Rect buttonStitch;
string buttonStitchText("buttonStitch");

Mat dilatationAndErosion(Mat image, string action) {
    int morph_size = 2;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    Mat result;

    if (action == "erode") {
        erode(image, result, element, Point(-1, -1), 1);
        return result;
    }

    else if (action == "dilate") {
        dilate(image, result, element, Point(-1, -1), 1);
        return result;
    }

    else {
        cout << "Wrong action\n";
        return image;
    }
    
}

Mat resizing(Mat image, int width, int height) {
	Mat resized;
	resize(image, resized, Size(width, height), INTER_LINEAR);
	return resized;
}

Mat lightenAnDarken(Mat image, double alpha, int beta) {
    Mat new_image = Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < image.channels(); c++) {
                new_image.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }
    return new_image;
}

Mat panoramastitching(Mat image, Mat imageToStitch) {
    Stitcher::Mode mode = Stitcher::PANORAMA;
    vector<Mat> imgs;
    imgs.push_back(image);
    imgs.push_back(imageToStitch);
    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(imgs, pano);
    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images\n";
        return image;
    }
    return pano;
}

Mat CannyEdgeDetection(Mat image) {
    Mat imageCanny;
    cv::Canny(image, imageCanny, 350, 350, 3, false);
    return imageCanny;
}

static void on_trackbar(int, void*)
{
    image = lightenAnDarken(original, 1, brightness - 50);
    image = resizing(image, width, height);
    imshow("original", image);
}

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        
        if (buttonDelate.contains(Point(x, y)))
        {
            cout << "buttonDelate Clicked!" << endl;
            rectangle(canvas(buttonDelate), buttonDelate, Scalar(0, 0, 255), 2);
        }
        if (buttonErode.contains(Point(x, y)))
        {
            cout << "buttonErode Clicked!" << endl;
            rectangle(canvas(buttonErode), buttonErode, Scalar(0, 0, 255), 2);
        }
        if (buttonCannydetection.contains(Point(x, y)))
        {
            cout << "buttonCannydetection Clicked!" << endl;
            rectangle(canvas(buttonCannydetection), buttonCannydetection, Scalar(0, 0, 255), 2);
        }
        if (buttonStitch.contains(Point(x, y)))
        {
            cout << "buttonStitch Clicked!" << endl;
            rectangle(canvas(buttonStitch), buttonStitch, Scalar(0, 0, 255), 2);
        }
    }
    if (event == EVENT_LBUTTONUP)
    {
        rectangle(canvas, buttonDelate, Scalar(200, 200, 200), 2);
        rectangle(canvas, buttonErode, Scalar(200, 200, 200), 2);
        rectangle(canvas, buttonCannydetection, Scalar(200, 200, 200), 2);
        rectangle(canvas, buttonStitch, Scalar(200, 200, 200), 2);
    }

    imshow(toolsWindowName, canvas);
    waitKey(1);
}

int main(int argc, char* argv[]) {
    // Read the image file
    String imageName = "van_gogh.jpg";
    original = imread(imageName, IMREAD_COLOR);
    image = original;
    // Check for failure
    if (original.empty())
    {
        printf(" No image data \n ");
        return -1;
    }

    //create windows
    namedWindow("original", WINDOW_AUTOSIZE);
    namedWindow("tools", WINDOW_AUTOSIZE);
    //namedWindow("dilatation", WINDOW_AUTOSIZE);
    //namedWindow("errosion", WINDOW_AUTOSIZE);
    //namedWindow("resize", WINDOW_AUTOSIZE);
    //namedWindow("light", WINDOW_AUTOSIZE);
    //namedWindow("dark", WINDOW_AUTOSIZE);
    //namedWindow("stitch", WINDOW_AUTOSIZE);
    //namedWindow("canny", WINDOW_AUTOSIZE);

   
    createTrackbar("Brightness", toolsWindowName, &brightness, 100, on_trackbar);
    createTrackbar("Width", toolsWindowName, &width, 1000, on_trackbar);
    createTrackbar("Height", toolsWindowName, &height, 1000, on_trackbar);

    // An image
    Mat3b img(300, 300, Vec3b(0, 255, 0));

    // Your button
    //Rect buttonDelate;
    //Rect buttonErode;
    //Rect buttonCannydetection;
    //Rect buttonStitch;
    buttonDelate = Rect(0, 0, img.cols, 50);

    buttonErode = Rect(0, 50, img.cols, 50);

    buttonCannydetection = Rect(0, 100, img.cols, 50);

    buttonStitch = Rect(0, 150, img.cols, 50);

    // The canvas
    canvas = Mat3b(img.rows + buttonDelate.height, img.cols, Vec3b(0, 0, 0));

    // Draw the button
    canvas(buttonDelate) = Vec3b(200, 200, 200);
    putText(canvas(buttonDelate), buttonDelateText, Point(buttonDelate.width * 0.35, buttonDelate.height * 0.7), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
    canvas(buttonErode) = Vec3b(200, 200, 200);
    putText(canvas(buttonErode), buttonErodeText, Point(buttonErode.width * 0.35, buttonErode.height * 0.7), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
    canvas(buttonCannydetection) = Vec3b(200, 200, 200);
    putText(canvas(buttonCannydetection), buttonCannydetectionText, Point(buttonCannydetection.width * 0.35, buttonCannydetection.height * 0.7), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
    canvas(buttonStitch) = Vec3b(200, 200, 200);
    putText(canvas(buttonStitch), buttonStitchText, Point(buttonStitch.width * 0.35, buttonStitch.height * 0.7), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));

    // Draw the image
    img.copyTo(canvas(Rect(0, buttonDelate.height, img.cols, img.rows)));

    // Setup callback function
    namedWindow(toolsWindowName);
    setMouseCallback(toolsWindowName, callBackFunc);
    //show images
    imshow("original", original);
    //imshow("dilatation", dilatationAndErosion(image,"dilate"));
    //imshow("errosion", dilatationAndErosion(image, "erode"));
    //imshow("resize", resizing(image,200,400));
    //imshow("light", lightenAnDarken(image,1,50));
    //imshow("dark", lightenAnDarken(image,1,-50));
    //imshow("stitch", panoramastitching(image,secondImage));
    //imshow("canny", CannyEdgeDetection(image));


    // Wait for any key stroke
    waitKey(0);

    //destroy all open windows
    destroyAllWindows;
    return 0;
}