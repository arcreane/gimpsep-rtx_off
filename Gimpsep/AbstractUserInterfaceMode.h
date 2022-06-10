#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "header/CannyEdgeDetection.h"
#include "header/DilatationAndErosion.h"
#include "header/LightenAnDarken.h"
#include "header/PanoramaStitching.h"

using namespace cv;
using namespace std;

class UIMode
{
protected:
	int brightness = 50;
	int width = 500;
	int height = 500;
	Mat original, image;
	virtual int run();

public:
	bool isErode = false;
	bool isDilate = false;
	bool isCanny = false;
	bool toStitch = false;

	void update();
	Mat resizing(Mat image, int width, int height);
	Mat imageToStitch;

	void toggleIsErode();
	void toggleIsDilate();
	void toggleIsCanny();
	void toggleToStitch();


};

