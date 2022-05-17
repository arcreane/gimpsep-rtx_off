#include "Main.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
}

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

void lightenAnDarken(Mat image, double alpha, int beta) {
    Mat new_image = Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < image.channels(); c++) {
                new_image.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }
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
    cv::Canny(image, imageCanny, 60, 150, 3, false);
    return imageCanny;
}