#include "Mode.h"

void Mode::update() {
    
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

Mat Mode::resizing(Mat image, int width, int height) {
    Mat resized;
    resize(image, resized, Size(width, height), INTER_LINEAR);
    return resized;
}

void Mode::toggleIsErode() {
    isErode = !isErode;
}
void Mode::toggleIsDilate() {
    isDilate = !isDilate;
}
void Mode::toggleIsCanny() {
    isCanny = !isCanny;
}
void Mode::toggleToStitch() {
    toStitch = !toStitch;
}

