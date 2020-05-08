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
//边缘识别
int exercise_5();
//磨皮

int main(){
    cout<<"Hello,World!"<<endl;
    // exercise_1();
    // exercise_2();
    // exercise_3();
    // exercise_4();
    exercise_5();

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
        Sobel(frame,result1,CV_16SC1,1,0,3);
        Sobel(frame,result2,CV_16SC1,0,1,3);
        convertScaleAbs(result1,result1);
        convertScaleAbs(result2,result2);
        imshow("src",frame);
        imshow("Sobel1",result1);
        imshow("Sobel2",result2);
        waitKey(30);
    }
    return 0;
}

int exercise_5(){
    VideoCapture cap(0);
    double i_minH = 0;
    double i_maxH = 20;

    double i_minS = 43;
    double i_maxS = 255;

    double i_minV = 55;
    double i_maxV = 255;

    while(true){
        Mat frame,hsvMat,mask,detectMat,origin;

        cap >> frame;
        cvtColor(frame,hsvMat,COLOR_BGR2HSV);
        frame.copyTo(origin);


        inRange(hsvMat,Scalar(i_minH,i_minS,i_minV),Scalar(i_maxH,i_maxS,i_maxV),mask);

        GaussianBlur(frame,detectMat,Size(5,5),3,3);
        int height = detectMat.rows;
        int width = detectMat.cols;
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                detectMat.at<Vec3b>(i,j)[0]+=10;
            }
        }


        detectMat.copyTo(frame,mask);

        imshow("2",frame);
        imshow("1",origin);

        waitKey(30);
    }
    return 0;
}