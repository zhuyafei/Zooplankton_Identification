//
//  pathAndLabel.cpp
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "pathAndLabel.h"

void pathAndLabel(string dataName, Mat& labels, vector<string>& imgName)
{
    ifstream dataPath(dataName);
    string buf;
    while( dataPath )//将训练样本文件依次读取进来
    {
        if( getline( dataPath, buf ) )
        {
            istringstream s(buf);
            string imgPath,classify,classifyLabel;
            s >> imgPath >> classify >> classifyLabel;
            
            int numLabel=atoi(classifyLabel.c_str());
            imgName.push_back( imgPath );//图像路径
            labels.push_back(numLabel);
        }
    }
    dataPath.close();
}