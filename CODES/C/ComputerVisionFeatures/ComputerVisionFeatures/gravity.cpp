//
//  gravity.cpp
//  binaryzation
//
//  Created by wangruchen on 15/9/6.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "gravity.h"

void gravity(vector<Point>& contourz, double areaContour, int gravityX, int gravityY)
{
    double m10,m01;
    Moments moment;
    moment=moments(contourz);
    m10=moment.m10;
    m01=moment.m01;
    gravityX=m10/areaContour;
    gravityY=m01/areaContour;
}