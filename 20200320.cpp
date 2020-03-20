#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();
int exercise_3();

int main(){
    cout << "Hello,World!" << endl;
    // exercise_1();
    // exercise_2();
    exercise_3();
    return 0;
}

int exercise_1(){
    Mat src = imread("coin.png");
    Mat kernel = getStructuringElement(0,Size(3,3));
    Mat out1,out2,out3,out4;
    morphologyEx(src,out1,0,kernel);
    morphologyEx(src,out2,1,kernel);
    morphologyEx(src,out3,2,kernel);
    morphologyEx(src,out4,3,kernel);

    imshow("erode",out1);
    imshow("dilate",out2);
    imshow("open",out3);
    imshow("close",out4);

    waitKey(0);
    return 0;
}

int exercise_2(){
    Mat src = imread("coin.png",0);
    Mat result1,result2;
    Mat labelsMat;//标签号
    Mat statsMat;//状态矩阵
    Mat centroidsMat;//连通域中心
    int count;

    threshold(src,result1,100,255,THRESH_OTSU);
    count = connectedComponentsWithStats(result1,labelsMat,statsMat,centroidsMat);

    cout << count-1 <<endl;

    for(int i;i<count;i++){
        Rect box;
        box.x = statsMat.at<int>(i,0);
        box.y = statsMat.at<int>(i,1);
        box.width = statsMat.at<int>(i,2);
        box.height = statsMat.at<int>(i,3);
        rectangle(result1,box,CV_RGB(255,255,255),1,8,0);
    }

    imshow("exercise_2",result1);
    waitKey(0);

    return 0;
}

int exercise_3(){
    Mat src = imread("IMG_1989.JPG",0);
    Mat result1,result2,result3;
    Mat kernel = getStructuringElement(2,Size(10,10));
    Mat labelsMat;//标签号
    Mat statsMat;//状态矩阵
    Mat centroidsMat;//连通域中心
    int count;

    threshold(src,result1,100,255,THRESH_OTSU);
    bitwise_not(result1,result1);

    morphologyEx(result1,result2,2,kernel);

    count = connectedComponentsWithStats(result2,labelsMat,statsMat,centroidsMat);

    for(int i;i<count;i++){
        Rect box;
        box.x = statsMat.at<int>(i,0);
        box.y = statsMat.at<int>(i,1);
        box.width = statsMat.at<int>(i,2);
        box.height = statsMat.at<int>(i,3);
        rectangle(result2,box,CV_RGB(255,255,255),1,8,0);
    }

    imshow("src",result1);
    imshow("test_open",result2);
    cout << count-1 << endl;

    waitKey(0);

    return 0;
}