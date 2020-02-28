#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main()
{
    cout << "Hello,World!";
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.jpg",0);




    imshow("test", img);
    waitKey(0);
    return 0;
}

