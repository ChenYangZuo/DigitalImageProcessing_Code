#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int exercise_1(){
    Mat img = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.jpg");
    int height = img.rows;
    int width = img.cols;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            uchar average = (img.at<Vec3b>(i,j)[0]+img.at<Vec3b>(i,j)[1]+img.at<Vec3b>(i,j)[2])/3;
            img.at<Vec3b>(i,j)[0]=average;
            img.at<Vec3b>(i,j)[1]=average;
            img.at<Vec3b>(i,j)[2]=average;
        }
    }
    imshow("test1", img);
    waitKey(0);

    return 0;
}

int exercise_2(){

    Mat img2 = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.jpg",0);
    imshow("test2", img2);
    waitKey(0);

    return 0;
}

int exercise_3(){
    Mat img3 = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.jpg");
    int height = img3.rows;
    int width = img3.cols;
    uchar threshold = 100;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            uchar average = (img3.at<Vec3b>(i,j)[0]+img3.at<Vec3b>(i,j)[1]+img3.at<Vec3b>(i,j)[2])/3;
            if(average>threshold){
                average = 255;
            }
            else{
                average = 0;
            }
            img3.at<Vec3b>(i,j)[0]=average;
            img3.at<Vec3b>(i,j)[1]=average;
            img3.at<Vec3b>(i,j)[2]=average;
        }
    }
    imshow("test3", img3);
    waitKey(0);

    return 0;
}

int exercise_4(){
    Mat img4 = imread("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.jpg");
    Mat deepMat,shallowMat;
    shallowMat = img4;
    img4.copyTo(deepMat);
    int height = img4.rows;
    int width = img4.cols;
    uchar threshold = 100;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            uchar average = (img4.at<Vec3b>(i,j)[0]+img4.at<Vec3b>(i,j)[1]+img4.at<Vec3b>(i,j)[2])/3;
            if(average>threshold){
                average = 255;
            }
            else{
                average = 0;
            }
            img4.at<Vec3b>(i,j)[0]=average;
            img4.at<Vec3b>(i,j)[1]=average;
            img4.at<Vec3b>(i,j)[2]=average;
        }
    }
    imshow("test4_0",img4);
    imshow("test4_deep",deepMat);
    imshow("test4_shallow",shallowMat);
    waitKey(0);

    return 0;
}

int main(){

    cout << "Hello,World!";

    exercise_1();
    exercise_2();
    exercise_3();
    exercise_4();

    return 0;
}