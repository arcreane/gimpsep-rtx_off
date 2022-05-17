#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int main(int argc, char** argv)
{

    int exitCode = 0;
    // Read the image file
    std::string imageEco_path = samples::findFile("eco.jpg");//images need to be in the project folder

    std::string imageVanGogh_path = samples::findFile("van_gogh.jpg");//images need to be in the project folder
    
    String imagePaths[2] = { imageEco_path ,imageVanGogh_path };


    for(String image_path : imagePaths) {

        Mat image = imread(image_path, IMREAD_COLOR);

    // Check for failure
    if (image.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        int exitCode = 1;
        return exitCode;
        
        //continue; // remove return statement and uncoment continue if you don't care that one of the file is missing
    }


    //increase the brightness by 50
    Mat new_imageCTimeTwo; 
    image.convertTo(new_imageCTimeTwo, -1, 1, 50);
    //increase the brightness by 100
    Mat new_imageCTimeFour;
    image.convertTo(new_imageCTimeFour, -1, 1, 100);
    //Mat new_imageCTimeFour = saturate_cast<-1>(new_imageCTimeTwo);
    //decrease the brightness by 50
    Mat new_imageCTimedotFive;
    image.convertTo(new_imageCTimedotFive, -1, 1, -50);
    //decrease the brightness by 100
    Mat new_imageCTimedotTwentyFive;
    image.convertTo(new_imageCTimedotTwentyFive, -1, 1, -100);
    //Defining window names for above images

    String imageCTimeTwoWindowName = "increase the brightness by 50 of : "+ image_path;
    String imageCTimeFourWindowName = "increase the brightness by 100 of : "+ image_path;
    String imageCTimedotFiveWindowName = "decrease the brightness by 50 of : "+ image_path;
    String imageCTimedotTwentyFiveWindowName = "decrease the brightness by 100 of : "+ image_path;

   
    
    //Create and open windows for above 
    
    namedWindow(imageCTimeTwoWindowName);
    namedWindow(imageCTimeFourWindowName);
    namedWindow(imageCTimedotFiveWindowName);
    namedWindow(imageCTimedotTwentyFiveWindowName);

    //Show above images inside the created windows.
    imshow(imageCTimeTwoWindowName, new_imageCTimeTwo);
    imshow(imageCTimeFourWindowName, new_imageCTimeFour);
    imshow(imageCTimedotFiveWindowName, new_imageCTimedotFive);
    imshow(imageCTimedotTwentyFiveWindowName, new_imageCTimedotTwentyFive);
   

    }

    // Wait for any key stroke
    waitKey();

    //destroy all open windows
    return exitCode;
  
}
