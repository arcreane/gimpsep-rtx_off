#include "AbstractUserInterfaceMode.h"

int UIMode::run()
{
    return 0;
}

void UIMode::update() {
    
    image = lightenAnDarken(original, 1, brightness - 50);
    image = resizing(image, width + 10, height + 10);
    if (isDilate) {
        image = dilatationAndErosion(image, "dilate");
    }
    if (isErode) {
        image = dilatationAndErosion(image, "erode");
    }
    if (isCanny) {
        image = cannyEdgeDetection(image);
    }
    if (toStitch) {
        image = panoramaStitching(image, imageToStitch);
    }
    imshow("image", image);
}

Mat UIMode::resizing(Mat image, int width, int height) {
    Mat resized;
    resize(image, resized, Size(width, height), INTER_LINEAR);
    return resized;
}

void UIMode::toggleIsErode() {
    isErode = !isErode;
}
void UIMode::toggleIsDilate() {
    isDilate = !isDilate;
}
void UIMode::toggleIsCanny() {
    isCanny = !isCanny;
}
void UIMode::toggleToStitch() {
    toStitch = !toStitch;
}

