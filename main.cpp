#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.jpg");
    imshow("test", img);
    waitKey(0);
    return 0;
}
