//
//  extractFeature.cpp
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "extractFeature.h"

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