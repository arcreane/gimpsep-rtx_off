#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
// Read source image
//samples::addSamplesDataSearchPath("C:/Users/TTR92/Desktop/TPMultimedia/VsProject/TP4/");
std::string image_path = samples::findFile("HappyFish.jpg");
std::string imageGS_path = "HappyFishGrayScale.jpg";
Mat img = imread(image_path, IMREAD_COLOR);
if (img.empty())
{
    std::cout << "Could not read the image: " << image_path << std::endl;
    return 1;
}
                   
// Scaling factors
double downScaleX = 0.6;
double downScaleY = 0.6;

double upScaleX = 1.8;
double upScaleY = 1.8;

Size dsize = Size(0, 0);
 
// Scaling down the image 0.6 times
Mat resizedImgtime0point6;
cv::resize( img , resizedImgtime0point6, dsize , downScaleX, downScaleY, INTER_LINEAR);

// Scaling up the image 1.8 times

Mat resizedImgtime1point8;
cv::resize(img, resizedImgtime1point8, dsize, upScaleX, upScaleY, INTER_LINEAR);

//Cropped image
Mat crop = img(cv::Range(50,150 ), cv::Range(0, 150));



//Display windows and show for all four images

imshow("BGR", img); // show RGB image 
imshow("resized 0.6", resizedImgtime0point6); // show resized image
imshow("resized 1.8", resizedImgtime1point8); // show resized image
imshow("croppedImage", crop); // show resized image


int k = waitKey(0); // Wait for a keystroke in the window
}
