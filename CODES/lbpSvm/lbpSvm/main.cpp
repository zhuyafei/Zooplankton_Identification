#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>
#include "pathAndLabel.h"
#include "WriteData.h"
#include "extractFeature.h"

using namespace cv;
using namespace std;
using namespace ml;

int main(int argc, const char * argv[])
{
    int classifyNum=13;
    string imgtrainDataName="Training_Set.txt";
    string imgtestDataName="Test_Set.txt";
    string testDataTxt="predictData.txt";
    string trainFeatureVector="trainFeatureVector.txt";
    string testFeatureVector="testFeatureVector.txt";
    Mat labelsTrain(0,1,CV_32FC1);
    Mat labelsTest(0,1,CV_32FC1);
    Mat trainData(0,16384, CV_32FC1);
    Mat testData(0,16384, CV_32FC1);
    
    vector<string> trainImgName;
    vector<string> testImgName;
    
    pathAndLabel(imgtrainDataName, labelsTrain, trainImgName);
    pathAndLabel(imgtestDataName, labelsTest, testImgName);
    /*------------------------LBP------------------------*/

    trainData=extractFeature(trainImgName);
    WriteData(trainFeatureVector, trainData);
    
    /*-----------------------Train-----------------------*/
    SVM::Params params;
    params.svmType = SVM::C_SVC;//C_SVC用于n类分类问题
    params.kernelType = SVM::LINEAR;
    params.gamma = 3;
    //    params.degree = 0;
    Ptr<SVM> svm = SVM::create(params);
    svm->train( trainData , ROW_SAMPLE , labelsTrain );
    
    /*----------------------Predict----------------------*/
    
    Mat result;   // 输出分类结果
    testData=extractFeature(trainImgName);
    WriteData(testFeatureVector, testData);
    
    svm->predict(testData, result);
    WriteData(testDataTxt, result);
    
    /*------------------confusionMatrix------------------*/
    labelsTrain.convertTo(labelsTrain, CV_32S);
    result.convertTo(result, CV_32S);
    Mat confusionMatrix=Mat::zeros(classifyNum, classifyNum, CV_32S);
    for (int i=0; i<result.rows; i++) {
        int trueClassify=labelsTrain.at<int>(0, i);
        int predictClassify=result.at<int>(0, i);
        confusionMatrix.at<int>(trueClassify-1,predictClassify-1)++;
    }
    string confusionMatrixName="confusionMatrix.txt";
    WriteData(confusionMatrixName, confusionMatrix);
    return 0;
}