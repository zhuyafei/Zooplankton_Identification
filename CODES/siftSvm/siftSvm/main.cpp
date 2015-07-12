#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>
#include "pathAndLabel.h"
#include "WriteData.h"
#include "extractFeature.h"
#include "confusionMatrix.h"

using namespace cv;
using namespace std;
using namespace ml;

int main(int argc, const char * argv[]) {
    int classifyNum=13;
    string imgTrainDataName="Training_Set.txt";
    string imgTestDataName="Test_Set.txt";
    string predictTrainDataTxt="./result/predictTrainData.txt";
    string predictTestDataTxt="./result/predictTestData.txt";
    string trainFeatureVector="./result/trainFeatureVector.txt";
    string predictTrainFeatureVector="./result/predictTrainFeatureVector.txt";
    string predictTestFeatureVector="./result/predictTestFeatureVector.txt";
    string confusionMatrixTrainName="./result/confusionMatrixTrain.txt";
    string confusionMatrixTestName="./result/confusionMatrixTest.txt";
    Mat labelsTrain(0,1,CV_32FC1);
    Mat labelsTest(0,1,CV_32FC1);
    Mat trainData(0,50, CV_32FC1);
    Mat trainFeatureData(0,50, CV_32FC1);
    Mat testFeatureData(0,50, CV_32FC1);
    
    vector<string> trainImgName;
    vector<string> testImgName;
    
    pathAndLabel(imgTrainDataName, labelsTrain, trainImgName);
    pathAndLabel(imgTestDataName, labelsTest, testImgName);
    /*---------------------Train SIFT--------------------*/
    trainData=extractFeature(trainImgName);
    WriteData(trainFeatureVector, trainData);
    /*-----------------------Train-----------------------*/
    SVM::Params params;
    params.svmType = SVM::C_SVC;//C_SVC用于n类分类问题
    params.kernelType = SVM::LINEAR;
    //    params.gamma = 3;
    Ptr<SVM> svm = SVM::create(params);
    svm->train( trainData , ROW_SAMPLE , labelsTrain );
    
    /*----------------Predict traindata------------------*/
    Mat resultTrain;   // 输出分类结果
    trainFeatureData=extractFeature(trainImgName);
    WriteData(predictTrainFeatureVector, trainFeatureData);
    
    svm->predict(trainFeatureData, resultTrain);
    WriteData(predictTrainDataTxt, resultTrain);
    
    /*----------------Predict testdata-------------------*/
    Mat resultTest;   // 输出分类结果
    testFeatureData=extractFeature(testImgName);
    WriteData(predictTestFeatureVector, testFeatureData);
    
    svm->predict(testFeatureData, resultTest);
    WriteData(predictTestDataTxt, resultTest);
    
    
    /*-------------Traindata Confusion Matrix------------*/
    Mat confusionMatrixTrain;
    confusionMatrixTrain=confusionMatrix(labelsTrain, resultTrain, classifyNum);
    WriteData(confusionMatrixTrainName, confusionMatrixTrain);
    
    /*-------------Testdata Confusion Matrix-------------*/
    Mat confusionMatrixTest;
    confusionMatrixTest=confusionMatrix(labelsTest, resultTest, classifyNum);
    WriteData(confusionMatrixTestName, confusionMatrixTest);
    
    
    return 0;
}