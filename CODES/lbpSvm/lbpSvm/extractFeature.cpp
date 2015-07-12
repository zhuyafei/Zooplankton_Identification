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
    Mat featureData(0,16384, CV_32FC1);
    for (int i=0; i != imgName.size(); i++) {
        Mat img=imread(imgName[i].c_str(),0);
        resize(img, img, Size(64,64));
        Mat lbpFeature=lbp::OLBP(img);
        normalize(lbpFeature, lbpFeature, 0, 255, NORM_MINMAX, CV_8U);
        cout << lbpFeature.size() << endl;
        Mat spatialHist=lbp::spatial_histogram(lbpFeature, 256);
        vector<float> featureVector;
        for(int j = 0; j < spatialHist.cols; ++j)
        {
            if(spatialHist.at<int>(0, j) != -1)
                featureVector.push_back(spatialHist.at<int>(0, j));
        }
        Mat descriptorsMat(1,featureVector.size(),CV_32F);
        for (int j=0; j<featureVector.size(); j++) {
            descriptorsMat.at<float>(0, j)=featureVector[j];
        }
        featureData.push_back(descriptorsMat);
    }
    return featureData;
}