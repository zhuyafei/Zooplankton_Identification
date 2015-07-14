//
//  confusionMatrix.cpp
//  hogSvm
//
//  Created by wangruchen on 15/7/12.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "confusionMatrix.h"

Mat confusionMatrix(Mat labels, Mat result, int classifyNum, string confusionMatrixTrainName)
{
    labels.convertTo(labels, CV_32S);
    result.convertTo(result, CV_32S);
    Mat confusionMatrix=Mat::zeros(classifyNum, classifyNum, CV_32S);
    for (int i=0; i<result.rows; i++) {
        int trueClassify=labels.at<int>(0, i);
        int predictClassify=result.at<int>(0, i);
        confusionMatrix.at<int>(trueClassify-1,predictClassify-1)++;
    }
    WriteData(confusionMatrixTrainName, confusionMatrix);
    return confusionMatrix;
}