//
//  pathAndLabel.h
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __lbp__pathAndLabel__
#define __lbp__pathAndLabel__

#include <opencv2/core.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace cv;
using namespace std;

void pathAndLabel(string dataName, Mat& labels, vector<string>& imgName);

#endif /* defined(__lbp__pathAndLabel__) */
