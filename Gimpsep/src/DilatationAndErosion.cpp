
#include "..\header\DilatationAndErosion.h"


Mat dilatationAndErosion(Mat image, string action, int morph_size) {
    
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    Mat result;

    if (action == "erode") {
        erode(image, result, element, Point(-1, -1), 1);
        return result;
    }

    else if (action == "dilate") {
        dilate(image, result, element, Point(-1, -1), 1);
        return result;
    }

    else {
        cout << "Wrong action\n";
        return image;
    }

}