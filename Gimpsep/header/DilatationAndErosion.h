#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat dilatationAndErosion(Mat image, string action, int morph_size);
