#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include "ImagePath.h"
#include "contourExtraction.h"
#include "gravity.h"
#include "grayFeature.h"
#include "shapeFeature.h"
#include "WriteData.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    string imgTrainDataPath="Training_Set.txt";
    string imgBinaryTrianDataPath="Training_Set_binary.txt";
    
    Mat imgTrainLabel, imgBinaryTrainLabel;
    vector<string> imgTrainName, imgBinaryTrainName;
    
    ImagePath( imgBinaryTrianDataPath, imgBinaryTrainLabel, imgBinaryTrainName);
    ImagePath( imgTrainDataPath, imgTrainLabel, imgTrainName);
    
    int imgNum=imgTrainName.size();
    
    Mat imgsFeaturesMatrix;
    for (int i=0; i<imgNum; i++) {
        Mat featuresMatrix;
        
        Mat img=imread(imgTrainName[i].c_str(),0);
        Mat imgBinary=imread(imgBinaryTrainName[i].c_str(),0);
        
        Mat imgBlack(imgBinary.size(), CV_8U, Scalar(255,255,255));
        vector<vector<Point>> imgContour;
        vector<Point> contourz;
        
        contourExtraction(imgBinary, imgBlack, contourz, imgContour);//边缘提取
        
        double areaContour=contourArea(contourz, false);//表面积
        double lenContour=arcLength(contourz,1);//轮廓周长
        double circularity=(4*M_PI*areaContour)/(lenContour*lenContour);//circ 密集度
        double perimArea=lenContour/sqrt(areaContour);//PerimArea
        
        Mat shapeFeaturesMatrix=shapeFeature(contourz, imgBlack, imgContour);
        
        int gravityX=0, gravityY=0;
        gravity(contourz, areaContour, gravityX, gravityY);//重心
        
        //灰度
        int grayGravityX=0,grayGravityY=0;//灰度重心
        Mat grayFeaturesMatrix=grayFeature(img, imgBinary, areaContour, grayGravityX, grayGravityY);
        double CD=sqrt((grayGravityX-gravityX)*(grayGravityX-gravityX)+(grayGravityY-gravityY)*(grayGravityY-gravityY))/sqrt(areaContour);//CD
        
        featuresMatrix.push_back(grayFeaturesMatrix);
        featuresMatrix.push_back(shapeFeaturesMatrix.at<double>(0, 0));
        featuresMatrix.push_back(circularity);
        featuresMatrix.push_back(perimArea);
        featuresMatrix.push_back(CD);
        
        imgsFeaturesMatrix.push_back(featuresMatrix);
    }
    imgsFeaturesMatrix=imgsFeaturesMatrix.t();
    Mat features=imgsFeaturesMatrix.reshape(0,9460);
    
    WriteData("9-features.txt", features);
    
    return 0;
}
