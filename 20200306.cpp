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
    imshow("src",img);
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
    Point pt,pt1,pt2;
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test1.png");
    pt.x = 100;
    pt.y = 200;
    pt1.x = 360;
    pt1.y = 360;
    pt2.x = 240;
    pt2.y = 240;
    Rect rect;
    rect.x = 360;
    rect.y = 240;
    rect.width = 120;
    rect.height = 240;
    circle(img,pt,80,CV_RGB(0,255,0),5,8,0);
    line(img,pt1,pt2,CV_RGB(0,255,0),3,8,0);
    rectangle(img,rect,CV_RGB(0,255,0),3,8,0);
    imshow("exercise_3",img);
    waitKey(0);
    return 0;
}

int exercise_5(float his[],int width,int height){
    Mat img = Mat(400, 280, CV_8UC3);
    Point pt1,pt2;
    float max=0;
    for(int k=0;k<256;k++){
        if(his[k]>max)
            max=his[k];
    }

    for(int i=0;i<256;i++){
        pt1.x = 6 + i;
        pt1.y = 394;
        pt2.x = 6 + i;
        pt2.y = 394 - his[i]/max*390;
        line(img,pt1,pt2,CV_RGB(255,255,255),1,8,0);
    }


    imshow("exercise_5",img);
    waitKey(0);
    return 0;
}

int exercise_4(){
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.jpg",0);
//    imshow("exercise_4",img);
    float histgram[256]={0};
    int height = img.rows;
    int width = img.cols;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            histgram[img.at<Vec3b>(i,j)[0]]++;
        }
    }

    for(int k=0;k<256;k++){
        cout<< k << ":" << histgram[k] << endl;
    }
    exercise_5(histgram,width,height);
//    waitKey(0);
    return 0;

}



int main(){
    cout << "Hello,World!";
    exercise_1();
//    exercise_3();
//    exercise_2();
//    exercise_4();
    return 0;
}