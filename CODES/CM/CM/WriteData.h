//
//  WriteData.h
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __lbp__WriteData__
#define __lbp__WriteData__

#include <opencv2/core.hpp>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace cv;
using namespace std;

int WriteData(string fileName, Mat& matData);

#endif /* defined(__lbp__WriteData__) */
