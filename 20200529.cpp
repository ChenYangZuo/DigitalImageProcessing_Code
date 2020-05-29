#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

vector<float> getHog(const Mat& img){
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
                    int count = (int)(angle.at<float>(16*j+y,16*i+x)/45);
                    hist[8*nx*j+8*i+count]+=mag.at<float>(16*j+y,16*i+x);
                }
            }
        }
    }

    return hist;
}

int main(){
    cout << "Hello,World!" << endl;

    Mat src = imread("./src/img.png",0);
    Mat mTemplate = imread("./src/template.png",0);

//    imshow("test",src);
//    waitKey(0);

    int row = src.rows;//行
    int col = src.cols;//列

    int row_t = mTemplate.rows;
    int col_t = mTemplate.cols;

    // Mat dist(row-row_t+1,col-col_t+1,CV_8UC1,Scalar(255));

    float distance = 0;
    float min_distance = 0;
//    int min_x = 0;
//    int min_y = 0;

    vector<float> hist0;
    vector<float> hist1;

    hist0 = getHog(mTemplate);

    Rect rect;
//    rect.x = min_x;
//    rect.y = min_y;
//    rect.width = col_t;
//    rect.height = row_t;

    for(int i=0;i<row-row_t;i++){
        for(int j=0;j<col-col_t;j++){
            Mat slide = src(Rect(j,i,col_t,row_t));

            hist1 = getHog(slide);
            for(int k=0;k<hist0.size();k++){
                distance+=(hist0[k]-hist1[k])*(hist0[k]-hist1[k]);
            }
            distance=sqrt(distance);

            if(i==0 & j==0){
                min_distance = distance;
            }

            if(distance < min_distance){
                min_distance = distance;
                rect = Rect(j,i,col_t,row_t);
            }

        }
    }


    rectangle(src,rect,CV_RGB(255,255,255),1,8,0);

    // imshow("test",dist);
    imshow("test",src);
    waitKey(0);
    
    return 0;
}