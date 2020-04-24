#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<float> getHog(Mat img){
    int size = 16;
    int nx = img.cols/size;//横着有这么多cell
    int ny = img.rows/size;//竖着有这么多cell

    Mat gx,gy;
    Mat mag,angle;
    Sobel(img,gx,CV_32F,1,0,1);
    Sobel(img,gy,CV_32F,0,1,1);
    cartToPolar(gx,gy,mag,angle,true);

    int i,j,x,y;
    vector<float> hist(nx*ny*8,0);

    for(j=0;j<ny;j++){//从上往下遍历cell
        for(i=0;i<nx;i++){//从左往右
            for(y=0;y<16;y++){//从上往下遍历像素
                for(x=0;x<16;x++){//从左往右
                    if(angle.at<float>(16*j+y,16*i+x)<=45)
                        hist[8*nx*j+8*i]+=mag.at<float>(16*j+y,16*i+x);
                    else if(angle.at<float>(16*j+y,16*i+x)<=90)
                        hist[8*nx*j+8*i+1]+=mag.at<float>(16*j+y,16*i+x);
                    else if(angle.at<float>(16*j+y,16*i+x)<=135)
                        hist[8*nx*j+8*i+2]+=mag.at<float>(16*j+y,16*i+x);
                    else if(angle.at<float>(16*j+y,16*i+x)<=180)
                        hist[8*nx*j+8*i+3]+=mag.at<float>(16*j+y,16*i+x);
                    else if(angle.at<float>(16*j+y,16*i+x)<=225)
                        hist[8*nx*j+8*i+4]+=mag.at<float>(16*j+y,16*i+x);
                    else if(angle.at<float>(16*j+y,16*i+x)<=270)
                        hist[8*nx*j+8*i+5]+=mag.at<float>(16*j+y,16*i+x);
                    else if(angle.at<float>(16*j+y,16*i+x)<=315)
                        hist[8*nx*j+8*i+6]+=mag.at<float>(16*j+y,16*i+x);
                    else if(angle.at<float>(16*j+y,16*i+x)<=360)
                        hist[8*nx*j+8*i+7]+=mag.at<float>(16*j+y,16*i+x);
                }
            }
        }
    }

    return hist;
}

int main(){
    cout << "Hello,World!" << endl;

    Mat src = imread("./src/hogTemplate.jpg");
    Mat img1 = imread("./src/img1.jpg");
    Mat img2 = imread("./src/img2.jpg");

    vector<float> hist;
    vector<float> hist1;
    vector<float> hist2;
    hist = getHog(src);
    hist1 = getHog(img1);
    hist2 = getHog(img2);

    int distance1=0,distance2=0;

    for(int i=0;i<hist.size();i++){
        distance1+=(hist[i]-hist1[i])*(hist[i]-hist1[i]);
    }
    distance1=sqrt(distance1);

    for(int i=0;i<hist.size();i++){
        distance2+=(hist[i]-hist2[i])*(hist[i]-hist2[i]);
    }
    distance2=sqrt(distance2);

    cout << distance1 << endl;
    cout << distance2 << endl;

    if(distance1>distance2){
        cout<<"img2相似度更高"<<endl;
    }
    else{
        cout<<"img1相似度更高"<<endl;
    }
    
    return 0;
}