//
//  classifierSVM.h
//  hogSvm
//
//  Created by wangruchen on 15/7/13.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __hogSvm__classifierSVM__
#define __hogSvm__classifierSVM__

#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include "extractFeature.h"
#include "WriteData.h"

using namespace cv;
using namespace std;
using namespace ml;



void classifierSVM(Mat& trainData, Mat& labelsTrain, vector<string> trainImgName, vector<string> testImgName, string kernelFunction, Mat& resultTrain, Mat& resultTest);



#endif /* defined(__hogSvm__classifierSVM__) */
