#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();

int main(){
    cout << "Hello,World!" << endl;

    exercise_1();
    // exercise_2();

    return 0;
}

int exercise_1(){
    Mat src = imread("./src/green.png");
    Mat mask = Mat::zeros(src.size(),CV_8UC1);
    Mat labels,centers;
    Mat sampleData = src.reshape(3,num);
    Mat km;

    int width = src.cols;
    int height = src.rows;
    int num = width*height;
    int cnt = 2;

    sampleData.convertTo(km,CV_32F);

    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT,10,0.1);
    kmeans(km,cnt,labels,criteria,cnt,KMEANS_PP_CENTERS,centers);

    uchar fg[2]={0,255};
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            mask.at<uchar>(i,j)=fg[labels.at<int>(i*height+j)];
        }
    }

    imshow("test0",src);
    imshow("test1",mask);
    waitKey(0);

    return 0;
}

int exercise_2(){


    return 0;
}