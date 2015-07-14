//
//  pathAndLabel.cpp
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "pathAndLabel.h"

void pathAndLabel(string dataName, Mat& labels)
{
    ifstream dataPath(dataName);
    string buf;
    while( dataPath )//将训练样本文件依次读取进来
    {
        if( getline( dataPath, buf ) )
        {
            int numLabel=atoi(buf.c_str());
            labels.push_back(numLabel);
        }
    }
    dataPath.close();
}