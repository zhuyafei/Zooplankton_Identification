//
//  classifierSVM.cpp
//  hogSvm
//
//  Created by wangruchen on 15/7/13.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "classifierSVM.h"

void classifierSVM(Mat& trainData, Mat& labelsTrain, vector<string> trainImgName, vector<string> testImgName, string kernelFunction, Mat& resultTrain, Mat& resultTest)
{
    Mat trainFeatureData(0,1764, CV_32FC1);
    Mat testFeatureData(0,1764, CV_32FC1);
    string predictTrainFeatureVector="./result/PredictTrain-Features-SIFT.txt";
    string predictTestFeatureVector="./result/PredictTest-Features-SIFT.txt";
    stringstream predictTrainDataTxt;
    stringstream predictTestDataTxt;
    
    SVM::Params params;
    params.svmType = SVM::C_SVC;//C_SVC用于n类分类问题
    if( kernelFunction == "LINEAR" )
    params.kernelType = SVM::LINEAR;
    if( kernelFunction == "RBF" )
    params.kernelType = SVM::RBF;
    Ptr<SVM> svm = SVM::create(params);
    svm->train( trainData , ROW_SAMPLE , labelsTrain );

    /*----------------Predict traindata------------------*/
//    Mat resultTrain;   // 输出分类结果
    trainFeatureData=extractFeature(trainImgName);
    WriteData(predictTrainFeatureVector, trainFeatureData);

    predictTrainDataTxt<<"./result/PredictTrain-SIFT-SVM-"<<kernelFunction<<".txt";
    svm->predict(trainFeatureData, resultTrain);
    WriteData(predictTrainDataTxt.str(), resultTrain);
    
    /*----------------Predict testdata-------------------*/
//    Mat resultTest;   // 输出分类结果
    testFeatureData=extractFeature(testImgName);
    WriteData(predictTestFeatureVector, testFeatureData);

    predictTestDataTxt<<"./result/PredictTest-SIFT-SVM-"<<kernelFunction<<".txt";
    svm->predict(testFeatureData, resultTest);
    WriteData(predictTestDataTxt.str(), resultTest);
}