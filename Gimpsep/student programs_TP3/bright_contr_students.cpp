#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    /*< Simple contrast control */

    const double alpha = 8; // contrast factor
    
    /*< Simple brightness control */
    const int beta = 0; // brightness factor


    //reading the image and creating a new image matrix
    std::string image_path = samples::findFile("eco.jpg");//images need to be in the project folder
    std::string newimage_path = "ecoBrightnessContrasted.jpg";
    Mat image = imread(image_path, IMREAD_COLOR);
    Mat new_image = Mat::zeros(image.size(), image.type());
    if (image.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
                           
   
    
    
    
    //asking for alpha [1.0-3.0] and beta values [0-100]
    
    const int maxX = image.cols;
    const int maxY = image.rows;
    const int numberOfChannels = image.channels();

    
    for(int x = 0; x < maxX; x++) {
        for (int y = 0; y < maxY; y++) {
            for (int c = 0; c < numberOfChannels; c++) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
           }
        }
    }
    /*
    image.convertTo(new_image, -1, alpha, beta);
    */
    //create windows
    //cv::imwrite(newimage_path, new_image); // write grayscale

    //show original and new image

    imshow("based image", image); // show RGB image 
    imshow("contrasted/brightned image", new_image); // grayscale show
    
    
    waitKey();
    return 0;
}
