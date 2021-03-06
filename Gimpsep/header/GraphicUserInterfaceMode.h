#pragma once
#include "AbstractUserInterfaceMode.h"
class GUIMode : public UIMode
{
public :
	Mat3b canvas;
	string toolsWindowName = "tools";
	Rect buttonDilate;
	string buttonDilateText= "Dilate";
	Rect buttonErode;
	string buttonErodeText= "Erode";
	Rect buttonCannydetection;
	string buttonCannydetectionText = "CannyEdge";
	Rect buttonStitch;
	string buttonStitchText = "Stitch";
	Rect buttonExport;
	string buttonExportText = "ExportToPng";

	int run();
	void on_trackbar(int, void*);
	void uiCallbackFunction(int event, int x, int y, int flags);
};

