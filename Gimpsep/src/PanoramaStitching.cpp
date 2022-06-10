#include "..\header\PanoramaStitching.h"

Mat panoramaStitching(Mat image, Mat imageToStitch,bool &ref_toStitch) {
    string imagePath;
    cout << "Enter an image path:" << endl;
    cin >> imagePath;
    imageToStitch = imread(imagePath, IMREAD_COLOR);
    // Check for failure
    if (imageToStitch.empty())
    {
        printf(" No image data \n ");
        ref_toStitch = false;
        return image;
    }
    
    Stitcher::Mode mode = Stitcher::PANORAMA;
    vector<Mat> imgs;
    imgs.push_back(image);
    imgs.push_back(imageToStitch);
    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(imgs, pano);
    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, you might have entered two different image or the same image as the original one\n";
        ref_toStitch = false;
        return image;
    }
    ref_toStitch = false;
    return pano;
}