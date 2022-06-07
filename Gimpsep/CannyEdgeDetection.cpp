#include "CannyEdgeDetection.h"


Mat cannyEdgeDetection(Mat image) {
    Mat imageCanny;
    cv::Canny(image, imageCanny, 350, 350, 3, false);
    return imageCanny;
}