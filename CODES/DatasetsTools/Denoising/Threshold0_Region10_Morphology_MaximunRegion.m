clear all;
close all;
clc;

TrainingSetInfo = importdata('Training_Set.txt');
%TestSetInfo = importdata('Test_Set.txt');
TrainingSetNum = length(TrainingSetInfo.data);
%TestSetNum = length(TestSetInfo.data);
resultName = './Results_TH0_Reg10_Mor_MaxReg/';

for i = 1:TrainingSetNum
    
    imageNameNum = strfind(TrainingSetInfo.textdata{i, 1},'/jb');
    classifyNameNum = strfind(TrainingSetInfo.textdata{i, 1},'/T');
    if ~isempty(imageNameNum)
        imageName=TrainingSetInfo.textdata{i, 1}((imageNameNum(1)+1):end);
    end
    if ~isempty(classifyNameNum)
        classifyName=TrainingSetInfo.textdata{i, 1}((classifyNameNum(1)):imageNameNum(1));
        mkdir(strcat(resultName,classifyName));
    end
    
    img = imread(TrainingSetInfo.textdata{i, 1});
    img = imresize(img, [256 256]);
    img = 255-img;
    imgbw = logical(img);
%     imgbw = im2bw(img,10/255);
    L = bwareaopen(imgbw, 10);
%% 数学形态学
    se = strel('square',2);
    L1 = imclose(L,se);
    L2 = imopen(L1,se);
    L3 = imclose(L2,se);
%% 求取最大连通区域
    imLabel = bwlabel(L3);                 
    stats = regionprops(imLabel,'Area');      
    area = cat(1,stats.Area);  
    index = find(area == max(area));       
    L3 = ismember(imLabel,index); 
%%
    result = double(img) .* double(L3);
    img5 = uint8(255-result);
    noNoiseName = [resultName classifyName imageName];
    imwrite(img5,noNoiseName);
end