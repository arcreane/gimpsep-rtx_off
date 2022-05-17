#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{

// Reading the image
std::string image_path = samples::findFile("van_gogh.jpg");
Mat img = imread(image_path, IMREAD_COLOR);


Point2f center(img.cols/2, img.rows/2);
double rotationAngle=30;
double scale=1;

// Getting the matrix which will define the rotation
Mat rotMatrix = cv::getRotationMatrix2D(center, rotationAngle, scale);

// Rotating the source and storing in result
Mat rotatedImg;
cv::warpAffine(img, rotatedImg, rotMatrix, img.size());
    
// Create windows for display


// Display images
imshow("croppedImage", rotatedImg); // show resized image
//imshow("croppedImage", crop); // show resized image


int k = waitKey(0); // Wait for a keystroke in the window

}
