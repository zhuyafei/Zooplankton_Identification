//
//  WriteData.cpp
//  lbp
//
//  Created by wangruchen on 15/7/10.
//  Copyright (c) 2015年 wangruchen. All rights reserved.
//

#include "WriteData.h"

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