#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/imgproc/types_c.h>
using namespace cv;
using namespace std;

int exercise_1();
int exercise_2();
int calculate(vector<Mat> srcMats,Mat &meanMat,Mat &varMat);
int gaussianThreshold(Mat frame,Mat meanMat,Mat varMat,float weight,Mat &dstMat);

int main(){
    cout << "Hello,World!" << endl;

    // exercise_1();
    exercise_2();
    
    return 0;
}

int exercise_1(){
    VideoCapture cap;
    Mat frame,bgMat,subMat,b_subMat;
    cap.open(0);
    int count = 0;

    while(1){
        cap.read(frame);
        cvtColor(frame,frame,CV_BGR2GRAY);
        if(count == 0){
            frame.copyTo(bgMat);
        }
        else{
            absdiff(frame,bgMat,subMat);
            threshold(subMat,b_subMat,50,255,CV_THRESH_BINARY);
            imshow("src",frame);
            imshow("dst",b_subMat);
            waitKey(30);
        }
        count++;
    }

    return 0;
}

int exercise_2(){
    VideoCapture cap;
    cap.open(0);

    int count = 0;
    int trainCount = 200;
    float weight = 1;

    Mat frame,sumMat,GaussianMat,dstMat;
    vector<Mat> srcMats;

    while(1){
        cap.read(frame);
        cvtColor(frame,frame,CV_BGR2GRAY);
        
        if(count == 0){
            cout << "start to collect..." << endl;
        }
        else if(count < trainCount){
            srcMats.push_back(frame);
        }
        else if(count == trainCount){
            sumMat.create(frame.size(),CV_8UC1);
			GaussianMat.create(frame.size(),CV_32FC1);
			cout << "start to calculate..." << endl;
			calculate(srcMats,sumMat,GaussianMat);
        }
        else{
            dstMat.create(frame.size(), CV_8UC1);
			gaussianThreshold(frame, sumMat, GaussianMat, weight, dstMat);
			imshow("result",dstMat);
			imshow("frame",frame);
			waitKey(30);
        }
        count++;
    }

    return 0;
}

int calculate(vector<Mat> srcMats,Mat &sumMat,Mat &GaussianMat){
    int col = srcMats[0].cols;
    int row = srcMats[0].rows;
    
    for(int i = 0;i < row;i++){
        for(int j = 0;j < col;j++){
            int sum = 0;
            float temp = 0;

            for(int n = 0;n < srcMats.size();n++){
                sum += srcMats[n].at<uchar>(i,j);
            }
            sumMat.at<uchar>(i,j)=sum/srcMats.size();

            for(int n = 0;n < srcMats.size();n++){
                temp += pow(srcMats[n].at<uchar>(i,j)-sumMat.at<uchar>(i,j),2);
            }
            GaussianMat.at<float>(i,j) = temp / srcMats.size();
        }
    }

    return 0;
}

int gaussianThreshold(Mat frame,Mat sumMat,Mat varMat,float weight,Mat &dstMat){
    int col = frame.cols;
    int row = frame.rows;
    for(int i = 0;i < row;i++){
        for(int j = 0;j < col;j++){
            if(frame.at<uchar>(i,j) - sumMat.at<uchar>(i,j) > varMat.at<uchar>(i,j)*weight){
                dstMat.at<uchar>(i,j)=255;
            }
            else
            {
                dstMat.at<uchar>(i,j)=0;
            }
        }
    }

    return 0;
}