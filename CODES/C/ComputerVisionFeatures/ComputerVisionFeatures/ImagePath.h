//
//  ImagePath.h
//  binaryzation
//
//  Created by wangruchen on 15/9/3.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __binaryzation__ImagePath__
#define __binaryzation__ImagePath__

#include <opencv2/core.hpp>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace cv;
using namespace std;

void ImagePath(string imgTrainDataPath, Mat& label, vector<string>& imgName);

#endif /* defined(__binaryzation__ImagePath__) */
