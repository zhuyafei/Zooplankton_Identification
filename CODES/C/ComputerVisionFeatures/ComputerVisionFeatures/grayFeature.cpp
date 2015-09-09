//
//  grayFeature.cpp
//  binaryzation
//
//  Created by wangruchen on 15/9/6.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "grayFeature.h"

Mat grayFeature(Mat& img, Mat& imgBinary, double areaContour, int& grayGravityX, int& grayGravityY)
{
    Mat grayFeaturesMatrix;
    Mat imgBinaryInvert;
    Mat imgInvert=img.clone();
    threshold(imgBinary, imgBinaryInvert, 254, 1, THRESH_BINARY);

    Mat imgObjectGray;
    Mat imgObjectX;
    Mat imgObjectY;
    for (int i=0; i<imgBinary.rows; i++) {
        for (int j=0; j<imgBinary.cols; j++) {
            if (imgBinary.at<uchar>(i,j)==255) {
                imgObjectGray.push_back(imgInvert.at<uchar>(i, j));
                imgObjectX.push_back(j);
                imgObjectY.push_back(i);
            }
        }
    }
    
    Scalar meanGray;
    Scalar stdDevGray;
    meanStdDev(imgObjectGray, meanGray, stdDevGray);//mean stdDev 灰度均值和标准差
    Scalar sumGray=cv::sum(imgObjectGray);//灰度和
    
    double minGray = 0.0, maxGray = 0.0;
    double* minp = &minGray;
    double* maxp = &maxGray;
    minMaxIdx(imgObjectGray,minp,maxp);//灰度范围
//    cout << "Mat minv = " << minv << endl;
//    cout << "Mat maxv = " << maxv << endl;
    
    double cvGray=100*(stdDevGray.val[0]/meanGray.val[0]);//CV
    double srGray=100*(stdDevGray.val[0]/maxGray-minGray);//SR
    double meanPos=(meanGray.val[0]-maxGray)/(maxGray-minGray);//MeanPos
    
    //灰度重心

    double sumMidX=0,sumMidY=0;
    for (int i=0; i<imgObjectGray.rows; i++) {
        sumMidX=sumMidX+imgObjectGray.at<uchar>(1, i)*imgObjectX.at<int>(1, i);
        sumMidY=sumMidY+imgObjectGray.at<uchar>(1, i)*imgObjectY.at<int>(1, i);
    }
    grayGravityX=sumMidX/sumGray.val[0];
    grayGravityY=sumMidY/sumGray.val[0];
    
    grayFeaturesMatrix.push_back(meanGray.val[0]);
    grayFeaturesMatrix.push_back(stdDevGray.val[0]);
    grayFeaturesMatrix.push_back(cvGray);
    grayFeaturesMatrix.push_back(srGray);
    grayFeaturesMatrix.push_back(meanPos);
    return grayFeaturesMatrix;
    
}