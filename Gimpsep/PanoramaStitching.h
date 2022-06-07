#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class PanoramaStitching
{
};

Mat panoramaStitching(Mat image, Mat imageToStitch);

