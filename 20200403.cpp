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
    cout<<"Hello,World!"<<endl;

    exercise_1();
    // exercise_2();
    // exercise_3();
    // exercise_4();
    return 0;
}

int exercise_1(){

    Mat src = imread("lena.jpg");
    if(src.empty()) return -1;
    Mat result1,result2;
    Mat output1,output2;
    Sobel(src,result1,CV_16SC1,2,0,3);
    Sobel(src,result2,CV_16SC1,0,2,3);
    Canny(result1,result2,output1,20,60);
    Canny(imread("lena.jpg",0),output2,20,60);
    imshow("test1",src);
    imshow("test2",output2);
    waitKey(0);
    return 0;
}

int exercise_2(){
    Mat src = imread("lena.jpg");
    Mat dst;
    float angle = -15.0,scale = 1;
    Point2f center(src.cols*0.5,src.rows*0.5);
    Mat affine_matrix = getRotationMatrix2D(center,angle,scale);
    warpAffine(src,dst,affine_matrix,src.size());
    imshow("src",src);
    imshow("dst",dst);
    waitKey(0);
    return 0;
}

int exercise_3(){
    Mat src = imread("lena.jpg");
    Mat dst;
    Point2f src_pt[]={
        Point2f(200,200),
        Point2f(250,200),
        Point2f(200,100)
    };
    Point2f dst_pt[]={
        Point2f(300,100),
        Point2f(300,500),
        Point2f(200,100)
    };
    Mat affine_matrix =getAffineTransform(src_pt,dst_pt);
    warpAffine(src,dst,affine_matrix,src.size());
    imshow("src",src);
    imshow("dst",dst);
    waitKey(0);
    return 0;
}

int exercise_4(){
    Mat src = imread("lena.jpg");
    Mat dst;
    Point2f pts1[]={
        Point2f(150,150),
        Point2f(150,300),
        Point2f(350,300),
        Point2f(350,150)
    };
    Point2f pts2[]={
        Point2f(200,150),
        Point2f(200,300),
        Point2f(340,270),
        Point2f(340,180)
    };
    Mat perspective_matrix =getPerspectiveTransform(pts1,pts2);
    warpPerspective(src,dst,perspective_matrix,src.size());
    imshow("src",src);
    imshow("dst",dst);
    waitKey(0);

    return 0;
}

int exercise_5(){
    Mat src = imread("lena_rot.jpg");
    int height = src.rows;
    int width = src.cols;
    for(int i=0;i<width;i++){
        if(src.at<Vec3b>(0,i)[0]+src.at<Vec3b>(0,i)[1]+src.at<Vec3b>(0,i)[2]>750){
            Point2f pt1(0,i);
            break;
        }
    }//左上

    for(int i=0;i<width;i++){
        if(src.at<Vec3b>(height,i)[0]+src.at<Vec3b>(height,i)[1]+src.at<Vec3b>(height,i)[2]>750){
            Point2f pt1(height,i);
            break;
        }
    }//右下

    for(int i=0;i<height;i++){
        if(src.at<Vec3b>(0,i)[0]+src.at<Vec3b>(0,i)[1]+src.at<Vec3b>(0,i)[2]>750){
            Point2f pt1(0,i);
            break;
        }
    }//




    return 0;
}