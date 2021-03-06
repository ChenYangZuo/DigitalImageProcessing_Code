#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
//肤色识别
int exercise_2();
//两种二值化算法
int exercise_3();
void threshod_Mat(int th,void* data);
//回调函数的用法

int main(){
    // exercise_1();
    // exercise_2();
    exercise_3();

    return 0;
}

int exercise_1(){
    VideoCapture cap(0);
    double scale = 0.5;

    double i_minH = 0;
    double i_maxH = 20;

    double i_minS = 43;
    double i_maxS = 255;

    double i_minV = 55;
    double i_maxV = 255;

    while(true){
        Mat frame;
        Mat hsvMat;
        Mat detectMat;

        cap >> frame;

        // frame = imread("test3.jpg");

        cvtColor(frame,hsvMat,COLOR_BGR2HSV);
        frame.copyTo(detectMat);

        
        inRange(hsvMat,Scalar(i_minH,i_minS,i_minV),Scalar(i_maxH,i_maxS,i_maxV),detectMat);

        imshow("2",detectMat);
        imshow("1",frame);

        waitKey(30);
    }

    return 0;

}

int exercise_2(){
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test2.jpg",0);
    Mat result1,result2;
    threshold(img,result1,100,255,THRESH_OTSU);
    adaptiveThreshold(img,result2,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,15,10);
    imshow("src",img);
    imshow("result1",result1);
    imshow("result2",result2);
    waitKey(0);
    return 0;

}

int exercise_3(){
    Mat srcMat;
    Mat gryMat;
    int lowTh = 30;
    int maxTh = 255;

    srcMat = imread("clip.png");
    if(!srcMat.data){
        cout << "ERROR1" << endl;
        return 0;
    }

    cvtColor(srcMat,gryMat,CV_BGR2GRAY);
    imshow("test",gryMat);
    createTrackbar("TEST","test",&lowTh,maxTh,threshod_Mat,&gryMat);
    waitKey(0);

    return 0;

}

void threshod_Mat(int th,void* data){
    Mat src = *(Mat*)(data);
    Mat dst;
    threshold(src,dst,th,255,0);
    imshow("test",dst);

}