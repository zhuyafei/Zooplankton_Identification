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
    string classifyName[] = {
        "Appendicularia", "Bubble", "Chaetognatha", "CladoceraPenilia", "Copepoda",
        "Decapoda", "Doliolida", "Egg", "Fiber", "Gelatinous",
        "Multiple", "Nonbio", "Pteropoda"
    };
    string buf;
    int imgNum=0;
    
    while( dataPath )//将训练样本文件依次读取进来
    {
        if( getline( dataPath, buf ) )
        {
            imgNum ++;
            if( imgNum % 2 == 0 )//这里的分类比较有意思，文本中应该是一行是文件路径，接着下一行就是该图片的类别
            {
                for (int m=0; m<13; m++) {
                    if (buf==classifyName[m]) {
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
                imgName.push_back( buf );//图像路径
            }
        }
    }
    dataPath.close();
}