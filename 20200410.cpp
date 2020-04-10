#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
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
    Mat src = imread("./src/lena.jpg");
    Mat dst;
    float angle = 15.0,scale = 1.0;
    Point2f center(src.cols/2.0,src.rows/2.0);
    Mat rot = getRotationMatrix2D(center,angle,scale);
    Rect bbox = RotatedRect(center,src.size(),angle).boundingRect();
    rot.at<double>(0,2) += bbox.width/2.0 - center.x;
    rot.at<double>(1,2) += bbox.height/2.0 - center.y;
    warpAffine(src,dst,rot,bbox.size());
    imshow("test",dst);
    waitKey(0);
    return 0;
}

int exercise_2(){
    Mat src = imread("./src/metal-part-distorted-03.png",0);
    Mat output;
    vector<Vec2f> dst;
    Canny(src,output,120,170);
    // imshow("test",output);
    // waitKey(0);
    HoughLines(output,dst,1,CV_PI/180,100);

    vector<Vec2f>::iterator it = dst.begin();
    for(;it != dst.end();++it){
        float rho = (*it)[0],theta = (*it)[1];
        Point pt1,pt2;
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a*rho;
        double y0 = b*rho;
        pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
        pt1.y = saturate_cast<int>(y0 + 1000 * (a));
        pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
        pt2.y = saturate_cast<int>(y0 - 1000 * (a));
        line(src,pt1,pt2,Scalar(0,0,255),1,8);
        
    }

    imshow("test",src);
    waitKey(0);
    return 0;
}

int exercise_3(){
    Mat src = imread("./src/metal-part-distorted-03.png");
    Mat output;
    vector<Vec4i> dst;
    Canny(src,output,100,170);
    // imshow("test",output);
    // waitKey(0);

    HoughLinesP(output,dst,1.0,CV_PI/180,20,3,8);

    for(int i = 0;i<dst.size();i++){
        Point pt1,pt2;
        pt1.x = dst[i][0];
        pt1.y = dst[i][1];
        pt2.x = dst[i][2];
        pt2.y = dst[i][3];
        cout << dst[i][0] << "," << dst[i][1] << " - " << dst[i][2] << "," << dst[i][3] << endl;
        line(src,pt1,pt2,Scalar(0,0,255),2,8);
    }

    imshow("test",src);
    waitKey(0);

    return 0;
}