#include "Main.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int brightness = 50;
int width = 500;
int height = 500;
Mat original,image;


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

   
    createTrackbar("Brightness", "tools", &brightness, 100, on_trackbar);
    createTrackbar("Width", "tools", &width, 1000, on_trackbar);
    createTrackbar("Height", "tools", &height, 1000, on_trackbar);

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