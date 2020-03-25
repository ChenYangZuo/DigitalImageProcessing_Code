#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();
int exercise_3();
int exercise_4();

int main(){
    cout << "Hello,World!" << endl;
    // exercise_1();
    // exercise_2();
    // exercise_3();
    exercise_4();
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
    Mat kernel = getStructuringElement(2,Size(10,10));//生成10*10的圆
    Mat labelsMat;//标签号
    Mat statsMat;//状态矩阵
    Mat centroidsMat;//连通域中心
    int count;

    threshold(src,result1,100,255,THRESH_OTSU);
    bitwise_not(result1,result1);//两级反转

    morphologyEx(result1,result2,2,kernel);//开运算

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

int exercise_4(){
    Mat src = imread("clip.png",0);
    Mat result1,result2,result3;
    Mat kernel = getStructuringElement(0,Size(25,25));
    Mat kernel0 = getStructuringElement(0,Size(4,4));
    Mat labelsMat;//标签号
    Mat statsMat;//状态矩阵
    Mat centroidsMat;//连通域中心
    int count;
    int result = 0;

    threshold(src,result1,80,255,THRESH_OTSU);//二值化
    bitwise_not(result1,result1);//两级反转

    morphologyEx(result1,result2,MORPH_OPEN,kernel0);
    morphologyEx(result2,result3,MORPH_CLOSE,kernel0);

    count = connectedComponentsWithStats(result2,labelsMat,statsMat,centroidsMat);
    // cout << format(statsMat,Formatter::FMT_PYTHON);

    for(int i=0;i<count;i++){
        if(statsMat.at<int>(i,4) > 4500 && statsMat.at<int>(i,4) < 8000)
            result++;
    }

    cout << result << endl;

    // imshow("test_0",result1);
    // imshow("test_1",result2);
    imshow("test_2",result3);
    waitKey(0);


    return 0;
}