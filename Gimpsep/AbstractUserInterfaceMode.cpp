#include "AbstractUserInterfaceMode.h"

void UIMode::update() {
    setPostProcessedImage(defaultImage);
    if (toStitch) {
        Mat temp = panoramaStitching(defaultImage, imageToStitch,toStitch);
        setDefaultImage(temp); // set new default as stutch image
        setPostProcessedImage(temp);
    }
    setPostProcessedImage(lightenAnDarken(postProcessedImage, 1, brightness - 50)); //!\\ don't move the lighten and darken under cannyEdgeDetection
    setPostProcessedImage(resizing(postProcessedImage, width + 10, height + 10));
    if (isDilate) {
        cout << "applying post process dilatation";
        setPostProcessedImage(
            dilatationAndErosion(postProcessedImage, "dilate")
        );
    }
    if (isErode) {
        setPostProcessedImage(
            dilatationAndErosion(postProcessedImage, "erode")
        );
    }
    if (isCanny) {
        setPostProcessedImage(
            cannyEdgeDetection(postProcessedImage)
        );
    }
    imshow("image", postProcessedImage);
}

Mat UIMode::resizing(Mat image, int width, int height) {
    Mat resized;
    resize(image, resized, Size(width, height), INTER_LINEAR);
    return resized;
}

void UIMode::toggleIsErode() {
    UIMode::isErode = !isErode;
}
void UIMode::toggleIsDilate() {
    UIMode::isDilate = !isDilate;
}
void UIMode::toggleIsCanny() {
    UIMode::isCanny = !isCanny;
}
void UIMode::toggleToStitch() {
    UIMode::toStitch = !toStitch;
}

void UIMode::setOriginalImage(Mat image) {
    UIMode::height = image.size[0];
    UIMode::width = image.size[1];
    UIMode::original = image;
    UIMode::defaultImage = image;
    UIMode::postProcessedImage = image;
}

void UIMode::setDefaultImage(Mat image) {
    UIMode::height = image.size[0];
    UIMode::width = image.size[1];
    UIMode::defaultImage = image;
}

void UIMode::setPostProcessedImage(Mat image) {
    UIMode::postProcessedImage = image;
}

int UIMode::run()
{
    return 0;
}