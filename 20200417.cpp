#include <opencv2/opencv.hpp>
// #include <opencv2/imgproc/types_c.h> 
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();
int exercise_3();

int main(){
    cout << "Hello,World!" << endl;

    exercise_1();
    // exercise_2();
    // exercise_3();

    return 0;
}

int exercise_1(){
    Mat src = imread("./src/rim.png");
    vector<vector<Point2f>> dst;
    cvtColor(src,src,COLOR_RGB2GRAY);
    findContours(src,dst,CV_RETR_EXTERNAL);
    return 0;
}

int exercise_2(){

    return 0;
}

int exercise_3(){

    return 0;
}