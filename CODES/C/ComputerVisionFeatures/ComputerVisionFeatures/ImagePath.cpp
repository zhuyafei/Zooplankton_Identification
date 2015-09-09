//
//  ImagePath.cpp
//  binaryzation
//
//  Created by wangruchen on 15/9/3.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "ImagePath.h"

void ImagePath(string imgTrainDataPath, Mat& label, vector<string>& imgName)
{
    ifstream imgPathLabel(imgTrainDataPath);
    string buf;
    while (imgPathLabel) {
        if (getline(imgPathLabel, buf)) {
            istringstream s(buf);
            string imgPath,imgClassify,imgLabel;
            s >> imgPath >> imgClassify >> imgLabel;
            
            int numLabel=atoi(imgLabel.c_str());
            label.push_back(numLabel);
            imgName.push_back(imgPath);
        }
    }
}