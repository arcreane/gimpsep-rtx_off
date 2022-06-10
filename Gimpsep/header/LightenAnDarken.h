#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


Mat lightenAnDarken(Mat image, double alpha, int beta);