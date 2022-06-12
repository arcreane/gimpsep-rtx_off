#include "../header/ExportImage.h"

void exportImage(Mat image)
{
	String pathToSaveImageTo;
	String nameOfImage;
	cout << "Enter the path of the folder where you want to save the image (make sure that it doesn't ends with '\'):" << endl;
	cin >> pathToSaveImageTo;
	if (pathToSaveImageTo == "")
	{
		cout << "image must have a valid path" << endl;
		cin.get(); //wait for a key press
		return;
	}
	cout << "Enter the name of the image :" << endl;
	cin >> nameOfImage;

	String completePathToSaveImageTo = pathToSaveImageTo + "/" + nameOfImage + ".png";
	bool isSuccess = imwrite(completePathToSaveImageTo, image);
	if (isSuccess == false)
	{
		cout << "Failed to save the image" << endl;
		cin.get(); //wait for a key press
		return;
	}
	cout << "the image was successfuly saved at : '"<< completePathToSaveImageTo << "'" << endl;
}
