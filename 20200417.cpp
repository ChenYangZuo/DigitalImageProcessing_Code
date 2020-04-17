#include <opencv2/opencv.hpp>
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
    Mat src = imread("./src/rim.png");
    Mat src1;
    Mat result1;
    vector<vector<Point>> dst;

    cvtColor(src,src1,COLOR_RGB2GRAY);
    threshold(src1,result1,230,255,THRESH_OTSU);
    bitwise_not(result1,result1);

    findContours(result1,dst,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    
    cout<<"共："<<dst.size()<<endl;

    for(int i=0;i<dst.size();i++){
        RotatedRect rbox = minAreaRect(dst[i]);
        Point2f vtx[4];

        if(rbox.size.width/rbox.size.height>0.9 && rbox.size.width/rbox.size.height<1.1 && rbox.size.width>10){
            rbox.points(vtx);
            drawContours(src,dst,i,Scalar(0,255,255),3,8);
        }

    }

    imshow("test",src);
    waitKey(0);

    return 0;
}

int exercise_2(){
    Mat src = imread("./src/die_on_chip.png");
    Mat src1;
    Mat result1;
    vector<vector<Point>> dst;

    cvtColor(src,src1,COLOR_RGB2GRAY);
    threshold(src1,result1,80,255,THRESH_OTSU);

    imshow("test",result1);
    waitKey(0);

    findContours(result1,dst,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    cout<<"共："<<dst.size()<<endl;

    for(int i=0;i<dst.size();i++){
        RotatedRect rbox = minAreaRect(dst[i]);
        Point2f vtx[4];


        if(rbox.size.width/rbox.size.height>0.9 && rbox.size.width/rbox.size.height<1.1 && rbox.size.width>10){
            rbox.points(vtx);
            drawContours(src,dst,i,Scalar(0,255,255),1,8);

            for(int j=0;j<4;j++){
                line(src,vtx[j],vtx[j<3?j+1:0],Scalar(0,0,255),2);
            }

        }

    }

    imshow("test",src);
    waitKey(0);
    return 0;
}

int exercise_3(){
    Mat src = imread("./src/topic1.JPG");
    Mat hsvMat,mask,mask2,result1;
    vector<vector<Point>> dst;

    Size mSize = Size(src.cols*0.3,src.rows*0.3);
    resize(src,src,mSize,INTER_LINEAR);

    cvtColor(src,hsvMat,COLOR_BGR2HSV);
    inRange(hsvMat,Scalar(150,43,46),Scalar(180,255,255),mask);
    inRange(hsvMat,Scalar(0,43,46),Scalar(10,255,255),mask2);

    mask = mask + mask2;

    findContours(mask,dst,RETR_EXTERNAL,CHAIN_APPROX_NONE);

    for(int i=0;i<dst.size();i++){
        RotatedRect rbox = minAreaRect(dst[i]);
        Point2f vtx[4];

        if(rbox.size.width>300){
            rbox.points(vtx);
            drawContours(src,dst,i,Scalar(0,255,255),1,8);

            for(int j=0;j<4;j++){
                line(src,vtx[j],vtx[j<3?j+1:0],Scalar(0,0,255),2);
            }
        }
    }


    // imshow("test1",mask);
    imshow("test2",src);
    waitKey(0);

    return 0;
}