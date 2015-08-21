clear all;
close all;
clc;

TrainingSetInfo = importdata('Training_Set.txt');
%TestSetInfo = importdata('Test_Set.txt');
TrainingSetNum = length(TrainingSetInfo.data);
%TestSetNum = length(TestSetInfo.data);
resultName = './Results_TH0_Reg10/';

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
    L = bwareaopen(imgbw, 10);      
%%
    result = double(img) .* double(L);
    img5 = uint8(255-result);
    noNoiseName = [resultName classifyName imageName];
    imwrite(img5,noNoiseName);
end