#include <opencv2/opencv.hpp>
using namespace cv;
int main( int argc, char** argv )
{
/* // not usefull
 char* imageName = argv[1];
 Mat image;
 if (argc != 2 || !image.data)
 {
     printf(" No image data \n ");
     return -1;
 }
 Mat gray_image;
 */

 
 std::string image_path = samples::findFile("HappyFish.jpg");//images need to be in the project folder
 std::string imageGS_path = "HappyFishGrayScale.jpg";
 Mat img = imread(image_path, IMREAD_COLOR);
 Mat imgGrayScale;
 if (img.empty())
 {
     std::cout << "Could not read the image: " << image_path << std::endl;
     return 1;
 }

 cvtColor(img, imgGrayScale, COLOR_BGR2GRAY); // grayscale conversion
 cv::imwrite(imageGS_path, imgGrayScale); // write grayscale
 imshow("BGR", img); // show RGB image 
 imshow("GrayScale", imgGrayScale); // grayscale show

 int k = waitKey(0); // Wait for a keystroke in the window
 return 0;
}
