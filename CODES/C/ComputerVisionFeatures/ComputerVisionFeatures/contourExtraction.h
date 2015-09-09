//
//  contourExtraction.h
//  binaryzation
//
//  Created by wangruchen on 15/9/6.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __binaryzation__contourExtraction__
#define __binaryzation__contourExtraction__

#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void contourExtraction(Mat imgBinary, Mat& imgBlack, vector<Point>& contourz, vector<vector<Point>>& imgContour);

#endif /* defined(__binaryzation__contourExtraction__) */
