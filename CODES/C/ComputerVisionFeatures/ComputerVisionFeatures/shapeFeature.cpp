//
//  shapeFeature.cpp
//  binaryzation
//
//  Created by wangruchen on 15/9/7.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "shapeFeature.h"

Mat shapeFeature(vector<Point>& contourz, Mat& imgBlack, vector<vector<Point>>& imgContour)
{
    Mat shapeFeaturesMatrix;
    
    //最小外接矩形
    RotatedRect box=minAreaRect(contourz);
    Point2f vertex[4];
    box.points(vertex);
//    for (int j=0; j<4; j++) {
//        line(imgBlack, vertex[j], vertex[(j+1)%4], Scalar(0,0,0));
//    }
//    imshow("minAreaRect", imgBlack);
//    waitKey();
    
    //椭圆
    RotatedRect ellip=fitEllipse(contourz);
    float ellipWidth, ellipHeight;
    ellipWidth=ellip.size.width;//短轴
    ellipHeight=ellip.size.height;//长轴
    double Elongation=ellipHeight/ellipWidth;//Elongation 偏心率
//    ellipse(imgBlack, ellip.center, ellip.size, ellip.angle, 0, 360, Scalar(0,0,0));
//    imshow("ellipse", imgBlack);
//    waitKey();
    
    //圆
    Point2f center;
    float radius=0;
    minEnclosingCircle(Mat(contourz), center, radius);
//    circle(imgBlack, center, radius, Scalar(0,0,0));
//    imshow("circle", imgBlack);
    
    //凸包
    vector<vector<Point>> hull(imgContour.size());
    for (size_t j=0; j<imgContour.size(); j++) {
        convexHull(imgContour[j], hull[j]);
    }
//    drawContours(imgBlack, hull, -1, Scalar(0,0,0));
//    imshow("convex", imgBlack);
//    waitKey();
    
    //骨架化
    
    
    shapeFeaturesMatrix.push_back(Elongation);
    return shapeFeaturesMatrix;
}