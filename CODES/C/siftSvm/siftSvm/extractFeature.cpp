//
//  extractFeature.cpp
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "extractFeature.h"
#define DICTIONARY_BUILD 1

Mat extractFeature(vector<string> imgName)
{
    Ptr<Feature2D> featureDetector = SURF:: create();
    Ptr<DescriptorExtractor> descExtractor = featureDetector;
    Ptr<DescriptorMatcher> descMatcher = DescriptorMatcher::create("BruteForce");
    Ptr<BOWImgDescriptorExtractor> bowExtractor = makePtr<BOWImgDescriptorExtractor>( descExtractor, descMatcher );
    
    Mat trainData(0,50, CV_32FC1);
    Mat allDescriptor;
    int clusterNum=50;
    TermCriteria terminateCriterion;
    terminateCriterion.epsilon=FLT_EPSILON;
    BOWKMeansTrainer bowTrainer(clusterNum, terminateCriterion, 3, KMEANS_PP_CENTERS );
    

    for (int i=0; i != imgName.size(); i++) {
        Mat img=imread(imgName[i].c_str(),1);
        vector<KeyPoint> keyPointDic;
        Mat descriptor;
        featureDetector->detect(img, keyPointDic);
        descExtractor->compute(img, keyPointDic, descriptor);
        for (int j=0; j<descriptor.rows; j++) {
            bowTrainer.add(descriptor.row(j));
        }
    }
    
    Mat vocabulary = bowTrainer.cluster();// allDescriptor );
    bowExtractor->setVocabulary(vocabulary);
    
    Mat feature;
    Mat zeroMatrix=Mat::zeros(1, 50, CV_32FC1);
    for( int i=0; i != imgName.size(); i++)
    {
        Mat img=imread(imgName[i].c_str());
        vector<KeyPoint> keyPointImg;
        featureDetector->detect(img, keyPointImg);
        Mat  imgDescriptor;
        bowExtractor->compute(img, keyPointImg, imgDescriptor);
        if (imgDescriptor.empty()) {
//            zeroNum.push_back(i);
            feature.push_back(zeroMatrix);
        }
        else
            feature.push_back( imgDescriptor );
    }
    trainData.push_back(feature);
    cout << trainData.size() << endl;
    return trainData;
}