#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();
int exercise_3();


int main(){
//    exercise_1();
//    exercise_2();
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

}