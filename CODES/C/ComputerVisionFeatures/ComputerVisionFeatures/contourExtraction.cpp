//
//  contourExtraction.cpp
//  binaryzation
//
//  Created by wangruchen on 15/9/6.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "contourExtraction.h"
void contourExtraction(Mat imgBinary, Mat& imgBlack, vector<Point>& contourz, vector<vector<Point>>& imgContour)
{
    Mat img=imgBinary.clone();
    findContours(img, imgContour, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for(size_t b=0; b < imgContour.size(); b++)
    {
        for(size_t a=0; a<imgContour[b].size(); a++)
        {
            contourz.push_back(imgContour[b][a]);
        }
    }
//    drawContours(imgBlack, imgContour, -1, Scalar(0,0,0));
//    imshow("contour", imgBlack);
//    waitKey();
}