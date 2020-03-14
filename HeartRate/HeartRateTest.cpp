//
// Created by zuochenyang on 2020/3/7.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int test2(int shuzu[]){
    Mat img = Mat(400, 280, CV_8UC3);
    Point pt1,pt2;
    float max=0;
    for(int k=0;k<256;k++){
        if(shuzu[k]>max)
            max=shuzu[k];
    }

    for(int i=0;i<256;i++){
        pt1.x = 6 + i;
        pt1.y = 394;
        pt2.x = 6 + i;
        pt2.y = 394 - shuzu[i]/max*390;
        line(img,pt1,pt2,CV_RGB(255,255,255),1,8,0);
    }

    imshow("exercise_5",img);
    waitKey(0);
    return 0;

}


int test1(){
    int shuzu[255] = {0};
    VideoCapture cap;
    cap.open("/home/zuochenyang/Desktop/DigitalImageProcessing_Code/test.mp4");
    if(!cap.isOpened()){
        cout << "ERROR 01!";
        return -1;
    }
    double fps = cap.get(CAP_PROP_FPS);
    cout << "FPS:" << fps << endl;


    int jici = 0;
    while(1){
        Mat frame;
        bool rSucess = cap.read(frame);
        if(!rSucess){
            cout << "ERROR 02!";
            break;
        }
        else{
            vector<Mat> channels;
            split(frame,channels);
            Mat R = channels.at(2);
            int height = frame.rows;
            int width = frame.cols;
            int all = 0;
            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    all += frame.at<Vec3b>(i,j)[0];
                }
            }
            cout << all << endl;
            shuzu[jici] = all;
            jici ++;


//            imshow("HeartRateTest",R);
        }
//        waitKey(30);
    }

    test2(shuzu);
    return 0;


}



int main(){

    test1();



    return 0;
}