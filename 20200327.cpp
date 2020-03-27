#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
//中值滤波
int exercise_2();
//均值滤波
int exercise_3();
//戴sigma参数的滤波
int exercise_4();

int main(){
    cout<<"Hello,World!"<<endl;
    // exercise_1();
    // exercise_2();
    // exercise_3();
    // exercise_4();


    return 0;
}

int exercise_1(){
    VideoCapture cap(0);
    while(true){
        Mat frame,result;
        cap >> frame;
        medianBlur(frame,result,5);
        imshow("src",frame);
        imshow("medianBlur",result);
        waitKey(30);
    }
    return 0;
}

int exercise_2(){
    VideoCapture cap(0);
    while(true){
        Mat frame,result;
        cap >> frame;
        blur(frame,result,Size(5,5));
        imshow("src",frame);
        imshow("blur",result);
        waitKey(30);
    }
    return 0;
}

int exercise_3(){
    VideoCapture cap(0);
    while(true){
        Mat frame,result,result2;
        cap >> frame;
        GaussianBlur(frame,result,Size(5,5),20.0,1.0);
        GaussianBlur(frame,result2,Size(5,5),1.0,20.0);
        imshow("src",frame);
        imshow("GaussianBlur1",result);
        imshow("GaussianBlur2",result2);
        waitKey(30);
    }
    return 0;
}

int exercise_4(){
    VideoCapture cap(0);
    while(true){
        Mat frame,result1,result2;
        cap >> frame;
        Sobel(frame,result1,0,1,0,3);
        Sobel(frame,result2,0,0,1,3);
        imshow("src",frame);
        imshow("Sobel1",result1);
        imshow("Sobel2",result2);
        waitKey(30);
    }
    return 0;
}