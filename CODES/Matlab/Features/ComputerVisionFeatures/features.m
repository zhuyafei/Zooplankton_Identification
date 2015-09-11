clear all;
close all;
clc;
TrainingBinarySetInfo = importdata('Training_Set_binary.txt');
TrainingSetInfo = importdata('Training_Set.txt');
%TestSetInfo = importdata('Test_Set.txt');
TrainingSetNum = length(TrainingBinarySetInfo.data);
%TestSetNum = length(TestSetInfo.data);

fid = fopen('17-Features-MATLAB.txt','w');
for i = 1:TrainingSetNum
    
    imageNameNum = strfind(TrainingBinarySetInfo.textdata{i, 1},'/jb');
    classifyNameNum = strfind(TrainingBinarySetInfo.textdata{i, 1},'/T');
    if ~isempty(imageNameNum)
        imageName=TrainingBinarySetInfo.textdata{i, 1}((imageNameNum(1)+1):end);
    end
    k=i
    imgBinary = imread(TrainingBinarySetInfo.textdata{i, 1});
    img = imread(TrainingSetInfo.textdata{i, 1});
    imgContour = edge(imgBinary,'canny');%提取轮廓
    objectArea = sum(sum(imgBinary));%面积
    objectLength = sum(sum(imgContour));%周长
    circularity = (4*pi*objectArea)/(objectLength*objectLength);%circ 密集度
    
    
    %分割后的图像
    num = 1;
    imgGray = [];
    [imgRows imgCols] = size(imgBinary);
    for x=1:imgRows
        for y=1:imgCols
            if imgBinary(x,y)==1
                imgGray(num) = img(x,y);
                imgObjectX(num) = x;
                imgObjectY(num) = y;
                num = num+1;
            end
        end
    end
    
    %灰度特征
    sumGray = sum(imgGray);%灰度之和
    maxGray = max(imgGray);%灰度最大值
    minGray = min(imgGray);%灰度最小值
    meanGray = mean2(imgGray);%均值
    stdDevGray = std2(imgGray);%标准差
    cvGray=100*(stdDevGray/meanGray);%CV
    srGray=100*(stdDevGray/maxGray-minGray);%SR
    meanPos=(meanGray-maxGray)/(maxGray-minGray);%MeanPos
    %灰度重心
    sumMidX=0;
    sumMidY=0;
    for m=1:imgRows
        sumMidX=sumMidX+imgGray(1, m)*imgObjectX(1, m);
        sumMidY=sumMidY+imgGray(1, m)*imgObjectY(1, m);
    end
    grayGravityX=sumMidX/sumGray;
    grayGravityY=sumMidY/sumGray;
    
    %形状特征
    objectFeatures = regionprops(imgBinary,'all');%最小外接矩形
    Elongation = (objectFeatures(1).MajorAxisLength)/(objectFeatures(1).MinorAxisLength);%Elongation 偏心率
    CDExc = sqrt((grayGravityX-objectFeatures(1).Centroid(1))*(grayGravityX-objectFeatures(1).Centroid(1))+(grayGravityY-objectFeatures(1).Centroid(2))*(grayGravityY-objectFeatures(1).Centroid(2)))/sqrt(objectFeatures(1).Area);%CDExc
    circExc = (4*pi*objectFeatures(1).Area)/(objectLength*objectLength);%Circexc
    feret = imMaxFeretDiameter(imgBinary);%Feret直径
    feretAreaexc = feret/sqrt(objectFeatures(1).Area);%FeretAreaexc
    perimFeret = objectLength/feret;%PerimFeret
    fractal = hausDim(imgBinary);
    
    
    rectPass = objectArea/(objectFeatures(1).BoundingBox(3)*objectFeatures(1).BoundingBox(4));%矩形度
    postCom = objectFeatures(1).BoundingBox(3)/objectFeatures(1).BoundingBox(4);%体态比
    convexHull = objectFeatures(1).Area/objectFeatures(1).ConvexArea;%凸率
    elongation = objectLength/(objectFeatures(1).BoundingBox(3)*objectFeatures(1).BoundingBox(4));%伸长率
imshow(imgBinary);
    img_new=bwmorph(imgBinary,'majority',Inf);
    figure,imshow(img_new);
%     skelArea = skeletonDemo(imgBinary);%骨架提取

    perimAreaExc = objectLength/sqrt(objectFeatures(1).Area);%PerimAreaexc
    
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
    featuresMatrix(i,13) = elongation;
    featuresMatrix(i,14) = feret;
    featuresMatrix(i,15) = feretAreaexc;
    featuresMatrix(i,16) = perimFeret;
%     featuresMatrix(i,17) = skelArea;
fprintf(fid, '%g\t', featuresMatrix(i,17)); 
fprintf(fid, '\n');
end
fclose(fid);
% [m n] = size(featuresMatrix);
% fid = fopen('17-Features-MATLAB.txt','w');
% for i = 1:TrainingSetNum
%     for j = 1:n
%         fprintf(fid, '%g\t', featuresMatrix(i,j)); 
%     end
%     fprintf(fid, '\n');
% end
% fclose(fid);