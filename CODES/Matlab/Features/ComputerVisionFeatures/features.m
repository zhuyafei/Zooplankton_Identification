clear all;
close all;
clc;

addpath('skeleton/','fractal/','inscribedCircle/','FeretDiameter/');

TrainingBinarySetInfo = importdata('Training_Set_binary.txt');
TrainingSetInfo = importdata('Training_Set.txt');
TrainingSetNum = length(TrainingBinarySetInfo.data);

% fid = fopen('17-Features-MATLAB.txt','w');

for i = 1:TrainingSetNum
    imageNameNum = strfind(TrainingBinarySetInfo.textdata{i, 1},'/jb');
    classifyNameNum = strfind(TrainingBinarySetInfo.textdata{i, 1},'/T');
    if ~isempty(imageNameNum)
        imageName=TrainingBinarySetInfo.textdata{i, 1}((imageNameNum(1)+1):end);
    end
    imgBinary = imread(TrainingBinarySetInfo.textdata{i, 1});   
    img = imread(TrainingSetInfo.textdata{i, 1});
    [imgX imgY] = size(imgBinary);
    imgBinaryLarge = zeros(imgX+4,imgY+4);
    imgBinaryLarge(3:end-2,3:end-2) = imgBinary;
%% 提取轮廓    
    imgContour = edge(imgBinaryLarge,'canny');%提取轮廓
    boundary=bwboundaries(imgBinaryLarge);
    boundary=boundary{1};%轮廓的坐标
%% 图像分割（去除噪声）
    imgGraySeg = uint8(255-double(imgBinary).*double(255-img));%分割后的图像
    num = 1;
    imgGray = [];
    [imgRows imgCols] = size(imgBinary);
    for x=1:imgRows
        for y=1:imgCols
            if imgBinary(x,y)==1
                imgGray(num) = img(x,y);%分割后的图像灰度
                imgObjectX(num) = x;%分割后的图像坐标
                imgObjectY(num) = y;
                num = num+1;
            end
        end
    end
%% 区域特征
    objectFeatures = regionprops(imgBinary,'all');
    objectArea = sum(sum(imgBinary));%面积
    objectLength = sum(sum(imgContour));%周长
    fai1=two_dim_moment(imgGraySeg);%不变矩
%% 灰度特征
    sumGray = sum(imgGray);%灰度之和
    maxGray = max(imgGray);%灰度最大值
    minGray = min(imgGray);%灰度最小值
    meanGray = mean(imgGray);%均值
    stdDevGray = std(imgGray);%标准差
    cvGray=100*(stdDevGray/meanGray);%CV
    srGray=100*(stdDevGray/(maxGray-minGray));%SR
    meanPos=(meanGray-maxGray)/(maxGray-minGray);%MeanPos
    %灰度重心
    sumMidX=0;
    sumMidY=0;
    for m=1:length(imgGray)
        sumMidX=sumMidX+imgGray(1, m)*imgObjectX(1, m);
        sumMidY=sumMidY+imgGray(1, m)*imgObjectY(1, m);
    end
    grayGravityX=sumMidX/sumGray;
    grayGravityY=sumMidY/sumGray;
    %灰度共生矩阵
    GLCMS = graycomatrix(imgGraySeg,'Offset',[2 0]);
    stats = graycoprops(GLCMS,{'energy','contrast','homogeneity','correlation'});%计算灰度共生矩阵统计特征
%% 形状特征
    %对称性   
    B = imrotate(imgBinary,pi-objectFeatures(1).Orientation,'bicubic','crop');%旋转
    BSymmetryY = max((imgCols-round(objectFeatures(1).Centroid(2)))*2,round(objectFeatures(1).Centroid(2))*2);
    BSymmetry = zeros(imgRows,BSymmetryY);
    BSymmetry(:,(BSymmetryY/2-round(objectFeatures(1).Centroid(2))+1):(BSymmetryY/2+imgCols-round(objectFeatures(1).Centroid(2)))) = B;
%     BF = flipud(BSymmetry);%上下翻转
    BF = fliplr(BSymmetry);%左右翻转
    BorBF = BSymmetry | BF;
    symmetry = sum(sum(BorBF))/sum(sum(BSymmetry));
%% 统计特征   
    circularity = (4*pi*objectFeatures(1).Area)/(objectFeatures(1).Perimeter*objectFeatures(1).Perimeter);%circ 密集度 
    Elongation = (objectFeatures(1).MajorAxisLength)/(objectFeatures(1).MinorAxisLength);%Elongation 偏心率
    CDExc = sqrt((grayGravityX-objectFeatures(1).Centroid(1))*(grayGravityX-objectFeatures(1).Centroid(1))+(grayGravityY-objectFeatures(1).Centroid(2))*(grayGravityY-objectFeatures(1).Centroid(2)))/sqrt(objectFeatures(1).Area);%CDExc
    feret = imMaxFeretDiameter(imgBinary);%Feret直径
    feretAreaexc = feret/sqrt(objectFeatures(1).Area);%FeretAreaexc
    perimFeret = objectFeatures(1).Perimeter/feret;%PerimFeret
    perimAreaExc = objectFeatures(1).Perimeter/sqrt(objectFeatures(1).Area);%PerimAreaexc

    rectPass = objectFeatures(1).Area/(objectFeatures(1).BoundingBox(3)*objectFeatures(1).BoundingBox(4));%矩形度
    postCom = objectFeatures(1).BoundingBox(3)/objectFeatures(1).BoundingBox(4);%体态比
    convexHull = objectFeatures(1).Area/objectFeatures(1).ConvexArea;%凸率
    longRate = objectFeatures(1).Perimeter/(objectFeatures(1).BoundingBox(3)*objectFeatures(1).BoundingBox(4));%伸长率
%     skelArea = skeletonDemo(imgBinary,TrainingBinarySetInfo.textdata{i, 1});%骨架提取
%     fractal = hausDim(imgBinary);%分形维数
    
    
    featuresMatrix(i,1) = meanGray;
    featuresMatrix(i,2) = stdDevGray;
    featuresMatrix(i,3) = cvGray;
    featuresMatrix(i,4) = srGray;
    featuresMatrix(i,5) = meanPos;
    featuresMatrix(i,6) = Elongation;
    featuresMatrix(i,7) = circularity;
    featuresMatrix(i,8) = perimAreaExc;
    featuresMatrix(i,9) = CDExc;
    featuresMatrix(i,10) = rectPass;
    featuresMatrix(i,11) = postCom;
    featuresMatrix(i,12) = convexHull;
    featuresMatrix(i,13) = longRate;
    featuresMatrix(i,14) = feret;
    featuresMatrix(i,15) = feretAreaexc;
    featuresMatrix(i,16) = perimFeret;
%     featuresMatrix(i,17) = skelArea;
    featuresMatrix(i,18) = stats.Contrast;
    featuresMatrix(i,19) = symmetry;
    featuresMatrix(i,20:26) = fai1;
% %     fprintf(fid, '%g\t', featuresMatrix(i,17)); 
% %     fprintf(fid, '\n');
end
% fclose(fid);
[m n] = size(featuresMatrix);
fid = fopen('20-Features-MATLAB.txt','w');
for i = 1:TrainingSetNum
    for j = 1:n
        fprintf(fid, '%g\t', featuresMatrix(i,j)); 
    end
    fprintf(fid, '\n');
end
fclose(fid);