#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int main(int argc, char** argv)
{

    // Read the image file
    std::string imageEco_path = samples::findFile("eco.jpg");//images need to be in the project folder
    std::string imageVanGogh_path = samples::findFile("van_gogh.jpg");//images need to be in the project folder
    String imagePaths[2] = { imageEco_path ,imageVanGogh_path };

    for (String image_path : imagePaths) {

        Mat image = imread(image_path, IMREAD_COLOR);

        // Check for failure
        if (image.empty())
        {
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;

            //continue; // remove return statement and uncoment continue if you don't care that one of the file is missing
        } 

    
        //increase the contrast by 2
        Mat new_imageCTimeTwo;
        image.convertTo(new_imageCTimeTwo, -1, 2, 0);
        //increase the contrast by 4
        Mat new_imageCTimeFour;
        image.convertTo(new_imageCTimeFour, -1, 4, 0);
        //decrease the contrast by 0.5
        Mat new_imageCTimedotFive;
        image.convertTo(new_imageCTimedotFive, -1, 0.5, 0);
        //decrease the contrast by 0.25
        Mat new_imageCTimedotTwentyFive;
        image.convertTo(new_imageCTimedotTwentyFive, -1, 0.25, 0);
        //Defining window names for above images

        String imageCTimeTwoWindowName = "increase the contrast by  time 2 of : " + image_path;
        String imageCTimeFourWindowName = "increase the contrast by time 4 of : " + image_path;
        String imageCTimedotFiveWindowName = "decrease the contrast by time 0.5 of : " + image_path;
        String imageCTimedotTwentyFiveWindowName = "decrease the contrast by time 0.25 of : " + image_path;



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
    return 0;

}