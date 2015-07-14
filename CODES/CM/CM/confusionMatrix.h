//
//  confusionMatrix.h
//  hogSvm
//
//  Created by wangruchen on 15/7/12.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#ifndef __hogSvm__confusionMatrix__
#define __hogSvm__confusionMatrix__

#include <opencv2/core.hpp>
#include <stdio.h>
#include <fstream>
#include "WriteData.h"

using namespace cv;
using namespace std;

Mat confusionMatrix(Mat labelsTrain, Mat predictTrainResult, int classifyNum, string confusionMatrixTrainName);

#endif /* defined(__hogSvm__confusionMatrix__) */
