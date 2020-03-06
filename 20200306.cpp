#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1(){
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test1.png");
    vector<Mat> channels;
    split(img,channels);
    Mat B = channels.at(0);
    Mat G = channels.at(1);
    Mat R = channels.at(2);
    imshow("red",R);
    imshow("green",G);
    imshow("blue",B);
    waitKey(0);
}

int exercise_2(){
    VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened()){
        cout << "ERROR!";
        return -1;
    }
    double fps = cap.get(CAP_PROP_FPS);
    cout << "FPS:" << fps << endl;
    while(1){
        Mat frame;
        bool rSucess = cap.read(frame);
        if(!rSucess){
            cout << "ERROR!";
            break;
        }
        else{
            imshow("test2",frame);
        }
        waitKey(30);
    }

}

int exercise_3(){
    Point pt;
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test1.png");
    pt.x = 100;
    pt.y = 200;
    circle(img,pt,80,CV_RGB(0,255,0),5,8,0);
    imshow("exercise_3",img);
    waitKey(0);
    return 0;
}

int exercise_4(){

}

int main(){
    cout << "Hello,World!";
//    exercise_1();
//    exercise_3();
    exercise_2();

    return 0;
}