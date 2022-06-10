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
	Mat original, defaultImage, postProcessedImage;
	Mat imageToStitch;
	virtual int run();
	 
public:
	bool isErode = false;
	bool isDilate = false;
	bool isCanny = false;
	bool toStitch = false;

	void update();
	Mat resizing(Mat image, int width, int height);
	

	void toggleIsErode();
	void toggleIsDilate();
	void toggleIsCanny();
	void toggleToStitch();

	void setOriginalImage(Mat image);

	void setDefaultImage(Mat image);

	void setPostProcessedImage(Mat image);

	~UIMode() {
		cout << "\ndestroyedUI -------------------------------------------------------------------------------";
	}
};

