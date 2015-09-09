//
//  grayFeature.h
//  binaryzation
//
//  Created by wangruchen on 15/9/6.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __binaryzation__grayFeature__
#define __binaryzation__grayFeature__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat grayFeature(Mat& img, Mat& imgBinary, double areaContour, int& grayGravityX, int& grayGravityY);

#endif /* defined(__binaryzation__grayFeature__) */
