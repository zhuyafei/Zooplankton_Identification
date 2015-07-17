#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>
#include "pathAndLabel.h"
#include "WriteData.h"
#include "confusionMatrix.h"
#include "classifierSVM.h"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    int classifyNum=13;
    string imgTrainDataName="Training_Set.txt";
    string imgTestDataName="Test_Set.txt";
    string trainFeatureVector="./result/Train-Features-SIFT.txt";
    
    Mat labelsTrain(0,1,CV_32FC1);
    Mat labelsTest(0,1,CV_32FC1);
    Mat trainData(0,50, CV_32FC1);
    
    vector<string> trainImgName;
    vector<string> testImgName;
    
    pathAndLabel(imgTrainDataName, labelsTrain, trainImgName);
    pathAndLabel(imgTestDataName, labelsTest, testImgName);
    
    /*---------------Train Feature Vector HOG-----------------*/
    trainData=extractFeature(trainImgName);
    WriteData(trainFeatureVector, trainData);
    
    /*-----------------------Classifier-----------------------*/
    string kernelFunction;
    for (int i=0; i<2; i++) {
        if (i==0) {
            kernelFunction="LINEAR";
        }
        else if (i==1) {
            kernelFunction="RBF";
        }
        Mat predictTrainResult,predictTestResult;   // 输出分类结果
        classifierSVM(trainData, labelsTrain, trainImgName, testImgName, kernelFunction, predictTrainResult, predictTestResult);
        
        /*----------------- Confusion Matrix-----------------*/
        for (int j=0; j<2; j++) {
            stringstream confusionMatrixTrainName;
            stringstream confusionMatrixTestName;
            if (j==0) {
                confusionMatrixTrainName<<"./result/Train-CM-SIFT-SVM-"<<kernelFunction<<".txt";
                confusionMatrix(labelsTrain, predictTrainResult, classifyNum, confusionMatrixTrainName.str());
            }
            else if (j==1) {
                confusionMatrixTestName<<"./result/Test-CM-SIFT-SVM-"<<kernelFunction<<".txt";
                confusionMatrix(labelsTest, predictTestResult, classifyNum, confusionMatrixTestName.str());
            }
        }
    }
    return 0;
}