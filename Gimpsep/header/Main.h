#pragma once
#include "AbstractUserInterfaceMode.h"
#include "GraphicUserInterfaceMode.h"
#include "CommandLineUserInterfaceMode.h"
#include "PanoramaStitching.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
class Main
{
};

int runCLUIMode(Mat original);

int runGUIMode(Mat original);
