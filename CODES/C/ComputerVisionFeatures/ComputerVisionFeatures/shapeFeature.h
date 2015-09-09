//
//  shapeFeature.h
//  binaryzation
//
//  Created by wangruchen on 15/9/7.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __binaryzation__shapeFeature__
#define __binaryzation__shapeFeature__

#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat shapeFeature(vector<Point>& contourz, Mat& imgBlack, vector<vector<Point>>& imgContour);

#endif /* defined(__binaryzation__shapeFeature__) */
