#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;
using namespace ml;

int WriteData(string fileName, Mat& matData)
{
    int retVal = 0;
    ofstream outFile(fileName.c_str(), ios_base::out);  //按新建或覆盖方式写入
    if (!outFile.is_open())
    {
        cout << "打开文件失败" << endl;
        retVal = -1;
        return (retVal);
    }
    // 检查矩阵是否为空
    if (matData.empty())
    {
        cout << "矩阵为空" << endl;
        retVal = 1;
        return (retVal);
    }
    // 写入数据
    matData.convertTo(matData, CV_32F);
    for (int r = 0; r < matData.rows; r++)
    {
        for (int c = 0; c < matData.cols; c++)
        {
            float data = matData.at<float>(r,c);  //读取数据，at<type> - type 是矩阵元素的具体数据格式
            outFile << data << "\t" ;   //每列数据用 tab 隔开
        }
        outFile << endl;  //换行
    }
    return (retVal);
}

Mat extractFeature(vector<string> imgName)
{
    Mat trainData(0,1764, CV_32FC1);
    for (int i=0; i != imgName.size(); i++) {
        Mat img=imread(imgName[i].c_str(),1);
        resize(img, img, Size(64,64));
        HOGDescriptor hog=HOGDescriptor(Size(64,64), Size(16,16), Size(8,8), Size(8,8), 9);
        vector<float> descriptors;
        hog.compute(img, descriptors);
        Mat descriptorsMat(1,descriptors.size(),CV_32F);
        for (int j=0; j<descriptors.size(); j++) {
            descriptorsMat.at<float>(0, j)=descriptors[j];
        }
        trainData.push_back(descriptorsMat);
    }
    return trainData;
}

int main(int argc, const char * argv[]) {
    
    string classifyName[] = {
        "Appendicularia", "Bubble", "Chaetognatha", "CladoceraPenilia", "Copepoda",
        "Decapoda", "Doliolida", "Egg", "Fiber", "Gelatinous",
        "Multiple", "Nonbio", "Pteropoda"
    };
    ifstream imgtrainData("Training_Set.txt");
    ifstream imgtestData("Test_Set.txt");
    string predictDataTxt="predictData.txt";
    string trainFeatureVector="trainFeatureVector.txt";
    string testFeatureVector="testFeatureVector.txt";
    Mat labels(0,1,CV_32FC1);
    Mat trainData(0,1764, CV_32FC1);
    
    vector<string> trainImgName;
    vector<string> testImgName;
    int imgNumTrain=0;
    string bufTrain;
    
    while( imgtrainData )//将训练样本文件依次读取进来
    {
        if( getline( imgtrainData, bufTrain ) )
        {
            imgNumTrain ++;
            if( imgNumTrain % 2 == 0 )//这里的分类比较有意思，文本中应该是一行是文件路径，接着下一行就是该图片的类别
            {
                for (int m=0; m<13; m++) {
                    if (bufTrain==classifyName[m]) {
                        switch (m) {
                            case 0:
                                labels.push_back(1);
                                break;
                            case 1:
                                labels.push_back(2);
                                break;
                            case 2:
                                labels.push_back(3);
                                break;
                            case 3:
                                labels.push_back(4);
                                break;
                            case 4:
                                labels.push_back(5);
                                break;
                            case 5:
                                labels.push_back(6);
                                break;
                            case 6:
                                labels.push_back(7);
                                break;
                            case 7:
                                labels.push_back(8);
                                break;
                            case 8:
                                labels.push_back(9);
                                break;
                            case 9:
                                labels.push_back(10);
                                break;
                            case 10:
                                labels.push_back(11);
                                break;
                            case 11:
                                labels.push_back(12);
                                break;
                            case 12:
                                labels.push_back(13);//图像所示类别标号
                                break;
                            default:
                                break;
                        }
                    }
                }
                
            }
            else
            {
                trainImgName.push_back( bufTrain );//图像路径
            }
        }
    }
    imgtrainData.close();
    /*------------------------HOG------------------------*/
    trainData=extractFeature(trainImgName);
    WriteData(trainFeatureVector, trainData);
    
    /*-----------------------Train-----------------------*/
    SVM::Params params;
    params.svmType = SVM::C_SVC;//C_SVC用于n类分类问题
    params.kernelType = SVM::LINEAR;
    params.gamma = 3;
//    params.degree = 0;
    Ptr<SVM> svm = SVM::create(params);
    svm->train( trainData , ROW_SAMPLE , labels );
    
    /*----------------------Predict----------------------*/
    Mat predictData(0,1764, CV_32FC1);
    Mat result;   // 输出分类结果
    predictData=extractFeature(trainImgName);
    WriteData(testFeatureVector, trainData);
    
    svm->predict(predictData, result);
    WriteData(predictDataTxt, result);
    
    
    return 0;
}