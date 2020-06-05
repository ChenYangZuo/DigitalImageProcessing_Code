#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();

int main(){
    cout << "Hello,World!" << endl;

    // exercise_1();
    exercise_2();

    return 0;
}

int exercise_1(){
    Mat src = imread("./src/green.png");
    Mat mask = Mat::zeros(src.size(),CV_8UC1);
    
    int width = src.cols;
    int height = src.rows;
    int num = width*height;
    int cnt = 2;

    Mat labels,centers;
    Mat sampleData = src.reshape(3,num);
    Mat km;

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
    VideoCapture cap("./src/乖巧的泪子.mp4");

    while(true){
        Mat src;
        cap >> src;

        resize(src,src,Size(src.cols/3,src.rows/3),0,0,INTER_LINEAR); 

        Mat mask = Mat::zeros(src.size(),CV_8UC1);

        int width = src.cols;
        int height = src.rows;
        int num = width*height;
        int cnt = 2;

        Mat labels,centers;
        Mat sampleData = src.reshape(3,num);
        Mat km;

        sampleData.convertTo(km,CV_32F);

        TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT,10,0.1);
        kmeans(km,cnt,labels,criteria,cnt,KMEANS_PP_CENTERS,centers);

        // print(labels);
        // cout << labels.size()<<endl;

        uchar fg[2]={0,255};
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                mask.at<uchar>(i,j)=fg[labels.at<int>(i*height+j)];
            }
        }

        imshow("raw",src);
        imshow("test",mask);
        waitKey(17);

    }
    return 0;
}