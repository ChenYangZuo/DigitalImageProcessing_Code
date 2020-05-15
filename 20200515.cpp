#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();
int exercise_3();
Mat gamma(Mat src,float gamma);

int main(){
    cout << "Hello,World!" << endl;

    exercise_1();
    // exercise_2();
    // exercise_3();
    
    return 0;
}

Mat gamma(Mat src,float gamma){

    int height = src.rows;
    int width = src.cols;
    Mat dst = Mat(height,width,src.type());
    int table[256]={0};
    for(int count=0;count<256;count++){
        table[count]=(pow(count/255.0,gamma)*255 < 255) ? pow(count/255.0,gamma)*255 : 255;
    }

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            dst.at<uchar>(i,j)=table[(int)src.at<uchar>(i,j)];
        }
    }
    return dst;
}

int exercise_1(){
    Mat dst = gamma(imread("./src/face.jpg",0),0.5);

    imshow("test",dst);
    waitKey(0);
    return 0;
}

int exercise_2(){
    Mat src = imread("./src/etest.jpg");
    Mat R,G,B,dst;

    vector<Mat> channels;
    split(src, channels);

	B = channels.at(0);
	G = channels.at(1);
	R = channels.at(2);

    equalizeHist(B,B);
    equalizeHist(G,G);
    equalizeHist(R,R);

    merge(channels, dst);

    imshow("test2",dst);
    imshow("test1",src);
    waitKey(0);

    return 0;
}

int exercise_3(){
    Mat src = imread("./src/gtest.jpg");
    float gam = 0.4;
    vector<Mat> channels,channels2;
    split(src,channels);

    Mat dst;
    Mat dst1 = gamma(channels.at(0),gam);
    Mat dst2 = gamma(channels.at(1),gam);
    Mat dst3 = gamma(channels.at(2),gam);

    channels2.push_back(dst1);
    channels2.push_back(dst2);
    channels2.push_back(dst3);
    merge(channels2,dst);

    imshow("test",dst);
    waitKey(0);
    
    return 0;
}