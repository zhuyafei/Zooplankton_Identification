#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>
#include "pathAndLabel.h"
#include "WriteData.h"
#include "confusionMatrix.h"

using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
    int classifyNum=13;
    string trainTest="Test";
    string featureMethod="HOG";
    string classifierMethod="RandomForest";
    
    stringstream imgLabelsTxt;
    imgLabelsTxt << trainTest << "-" << featureMethod << "-" << classifierMethod << ".txt";
    stringstream imgPredictLabelsTxt;
    imgPredictLabelsTxt << "Predict" << trainTest << "-" << featureMethod << "-" << classifierMethod << ".txt";
    stringstream confusionMatrixTrainName;
    confusionMatrixTrainName << "./result/" << trainTest << "-CM-" << featureMethod << "-" << classifierMethod << ".txt";
    
    Mat imgLabels(0,1,CV_32FC1);
    Mat imgPredictLabels(0,1,CV_32FC1);
    vector<string> trainImgName;
    vector<string> testImgName;
    
    pathAndLabel(imgLabelsTxt.str(), imgLabels);
    pathAndLabel(imgPredictLabelsTxt.str(), imgPredictLabels);
    
    /*----------------- Confusion Matrix-----------------*/
    confusionMatrix(imgLabels, imgPredictLabels, classifyNum, confusionMatrixTrainName.str());
    return 0;
}