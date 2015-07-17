//
//  extractFeature.h
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __lbp__extractFeature__
#define __lbp__extractFeature__

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "lbp.hpp"
#include "histogram.hpp"

using namespace cv;
using namespace std;

Mat extractFeature(vector<string> imgName);

#endif /* defined(__lbp__extractFeature__) */
