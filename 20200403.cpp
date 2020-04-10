#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int exercise_1();
//Canny算子
int exercise_2();
//旋转缩放
int exercise_3();
//仿射变换
int exercise_4();
//投影变换
int exercise_5_1();
//自动校正旋转
int exercise_6();

int main(){
    cout<<"Hello,World!"<<endl;

    // exercise_1();
    // exercise_2();
    // exercise_3();
    // exercise_4();
    exercise_5_1();
    // exercise_6();

    return 0;
}

int exercise_1(){
    Mat src = imread("./src/lena.jpg");
    Mat output2,output1;

    Mat result1,result2;
    Sobel(src,result1,CV_16SC1,1,0,3);
    Sobel(src,result2,CV_16SC1,0,1,3);
    Canny(result1,result2,output1,20,60);

    Canny(imread("./src/lena.jpg",0),output2,20,60);
    imshow("test1",output1);
    imshow("test2",output2);
    waitKey(0);
    return 0;
}

int exercise_2(){
    Mat src = imread("./src/lena.jpg");
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
    Mat src = imread("./src/lena.jpg");
    Mat dst;
    Point2f src_pt[]={
        Point2f(200,200),
        Point2f(250,200),
        Point2f(200,100)
    };
    Point2f dst_pt[]={
        Point2f(300,100),
        Point2f(300,50),
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
    Mat src = imread("./src/lena.jpg");
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
    Mat src = imread("./src/lena_rot.jpg");
    Mat dst;
    int height = src.rows;
    int width = src.cols;
    Point2f src_pt[4];

    Point2f dst_pt[]={
        Point2f(0,0),
        Point2f(height,width),//(512,512)
        Point2f(height,0),//(0.512)
        Point2f(0,width)
    };

    for(int i=0;i<width;i++){
        if(src.at<Vec3b>(0,i)[0]+src.at<Vec3b>(0,i)[1]+src.at<Vec3b>(0,i)[2]<750){
            src_pt[0] = Point2f(0,i);
            cout << i << endl;
            break;
        }
    }//左上  x=70,y=0

    for(int i=0;i<width;i++){
        if(src.at<Vec3b>(height-1,i)[0]+src.at<Vec3b>(height-1,i)[1]+src.at<Vec3b>(height-1,i)[2]<750){
            src_pt[1] = Point2f(height-1,i);
            cout << i << endl;
            break;
        }
    }//右下  x=436,y=512

    for(int i=0;i<height;i++){
        if(src.at<Vec3b>(i,0)[0]+src.at<Vec3b>(i,0)[1]+src.at<Vec3b>(i,0)[2]<750){
            src_pt[2] = Point2f(i,0);
            cout << i << endl;
            break;
        }
    }//左下  x=0,y=441

    // for(int i=0;i<height;i++){
    //     if(src.at<Vec3b>(i,width)[0]+src.at<Vec3b>(i,width)[1]+src.at<Vec3b>(i,width)[2]>750){
    //         // Point2f pt4(i,width);
    //         src_pt[3] = Point2f(i,width);
    //         cout << i << endl;
    //         break;
    //     }
    // }//右上

    
    cout << src_pt[0]<<dst_pt[0]<<endl;
    cout << src_pt[1]<<dst_pt[1]<<endl;
    cout << src_pt[2]<<dst_pt[2]<<endl;
    // cout << src_pt[3]<<dst_pt[3]<<endl;
    Mat affine_matrix =getAffineTransform(dst_pt,src_pt);
    warpAffine(src,dst,affine_matrix,Size(height-70,height-70));
    imshow("src",src);
    imshow("dst",dst);
    waitKey(0);


    return 0;
}

int exercise_5_1(){
    Mat src = imread("./src/lena_rot.jpg");
    Mat dst;
    int height = src.rows;
    int width = src.cols;
    int i;

    Point2f dst_pts[]={
        Point2f(0,0),//左上
        Point2f(height,width),//右下
        Point2f(height,0),//左下
        Point2f(0,width)//右上
    };
    
    for(i=0;i<width;i++){
        if(src.at<Vec3b>(0,i)[0]+src.at<Vec3b>(0,i)[1]+src.at<Vec3b>(0,i)[2]<750){
            cout << "偏移量：" << i << endl;
            break;
        }
    }

    Point2f src_pts[]={Point2f(0,i),Point2f(height,width-i),Point2f(height-70,0),Point2f(i,width)};

    Mat affine_matrix =getAffineTransform(dst_pts,src_pts);
    warpAffine(src,dst,affine_matrix,src.size());

    Point2f center(src.cols*0.5,src.rows*0.5);
    float scale = (height*width)/((height*width)-i*(height-i)*0.5*4);
    cout << "缩放比例：" << scale << endl;
    affine_matrix = getRotationMatrix2D(center,0,scale);
    warpAffine(dst,dst,affine_matrix,src.size());

    imshow("src",src);
    imshow("dst",dst);
    waitKey(0);

}

int exercise_6(){
    Mat src = imread("./src/lena.jpg");
    Mat dst;
    int height = src.rows;
    int width = src.cols;
    float angle = 15.0;

    float scale = 1/(sin((angle*3.14)/180)+cos((angle*3.14)/180));
    cout<<scale;

    Point2f center(src.cols*0.5,src.rows*0.5);
    Mat affine_matrix = getRotationMatrix2D(center,angle,scale);

    warpAffine(src,dst,affine_matrix,src.size());
    imshow("src",src);
    imshow("dst",dst);
    waitKey(0);
    return 0;

}