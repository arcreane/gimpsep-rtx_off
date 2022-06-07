#include "..\header\PanoramaStitching.h"

Mat panoramaStitching(Mat image, Mat imageToStitch) {
    Stitcher::Mode mode = Stitcher::PANORAMA;
    vector<Mat> imgs;
    imgs.push_back(image);
    imgs.push_back(imageToStitch);
    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(imgs, pano);
    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images\n";
        return image;
    }
    return pano;
}