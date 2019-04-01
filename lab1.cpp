#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void toFlip(Mat image) {
	Mat flip_image;
	flip_image = image;
	int i, j, k;
	int rows = image.rows;
	int cols = image.cols;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols/2; j++) {
			uchar temp;
			for (k = 0; k < 3; k++) {
				temp = flip_image.at<Vec3b>(i, j)[k];
				flip_image.at<Vec3b>(i, j)[k] = flip_image.at<Vec3b>(i, cols - 1 - j)[k];
				flip_image.at<Vec3b>(i, cols - 1 - j)[k] = temp;
			}
		}
	}
	imwrite("sophia_Flip_Image.jpg", flip_image);
	imshow("Flip image", flip_image);
}

void toGray(Mat image){
	Mat gray_image;
	gray_image = image;;
	int i, j;
	int rows = gray_image.rows;
	int cols = gray_image.cols;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			uchar sum = 0;
			sum = gray_image.at<Vec3b>(i, j)[0]*0.11  + gray_image.at<Vec3b>(i, j)[1]*0.59 + gray_image.at<Vec3b>(i, j)[2]*0.30;
			gray_image.at<Vec3b>(i, j)[0] = sum;
			gray_image.at<Vec3b>(i, j)[1] = sum;
			gray_image.at<Vec3b>(i, j)[2] = sum;	
		}
	}
	imwrite("sophia_Gray_Image.jpg", gray_image);
	imshow("Gray image", gray_image);
}

void toNegative(Mat image) {
	Mat negative_image;
	negative_image = image;
	int i, j, k;
	int rows = image.rows;
	int cols = image.cols;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			for (k = 0; k < 3; k++) {
				negative_image.at<Vec3b>(i, j)[k] = 255 - negative_image.at<Vec3b>(i, j)[k];
			}
		}
	}
	imwrite("sophia_Negative_Image.jpg", negative_image);
	imshow("Negative image", negative_image);
}

void toEmboss(Mat image) {
	Mat emboss_image;
	emboss_image = image;
	uchar preColor[3] = { 0 };
	uchar currColor[3];
	int rows = image.rows;
	int cols = image.cols;
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			uchar r, g, b;
			currColor[0] = emboss_image.at<Vec3b>(i, j)[0];
			currColor[1] = emboss_image.at<Vec3b>(i, j)[1];
			currColor[2] = emboss_image.at<Vec3b>(i, j)[2];
			r = currColor[0] - preColor[0] + 128;
			g = currColor[0] - preColor[0] + 128;
			b = currColor[0] - preColor[0] + 128;

			uchar sum = 0;
			sum = r * 0.11 + g * 0.59 + b * 0.30;
			emboss_image.at<Vec3b>(i, j)[0] = sum;
			emboss_image.at<Vec3b>(i, j)[1] = sum;
			emboss_image.at<Vec3b>(i, j)[2] = sum;

			preColor[0] = currColor[0];
			preColor[1] = currColor[1];
			preColor[2] = currColor[2];

		}
	}
	imwrite("sophia_Emboss_Image.jpg", emboss_image);
	imshow("Emboss image", emboss_image);
}

int main()
{
	Mat image;
	Mat resize_image;

	image = imread("sophia.jpg", IMREAD_COLOR); // Read the file
	int resize_height = 500;
	int resize_width = 376;

	if (image.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return 0;
	}
	resize(image, resize_image, Size(resize_width, resize_height), (0, 0), (0, 0));
	Mat resize_image_flip = resize_image.clone();
	Mat resize_image_gray = resize_image.clone();
	//Mat resize_image_negative = resize_image.clone();
	Mat resize_image_emboss = resize_image.clone();

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.WINDOW_AUTOSIZE
	imwrite("sophia_Original_Image.jpg", resize_image);
	imshow("Original image", resize_image);

	toFlip(resize_image_flip);
	toGray(resize_image_gray);
	//toNegative(resize_image_negative);
	toEmboss(resize_image_emboss);
	                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	return 0;
}