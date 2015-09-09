//
//  gravity.h
//  binaryzation
//
//  Created by wangruchen on 15/9/6.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __binaryzation__gravity__
#define __binaryzation__gravity__

#include <stdio.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void gravity(vector<Point>& contourz, double areaContour, int gravityX, int gravityY);

#endif /* defined(__binaryzation__gravity__) */
