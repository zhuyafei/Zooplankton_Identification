clear
clc
TrainingSetInfo = importdata('Training_Set.txt');
TestSetInfo = importdata('Test_Set.txt');
TrainingSetNum = length(TrainingSetInfo.data);
TestSetNum = length(TestSetInfo.data);
cellSize = 32;

%% For random dividing - cross validation
fid = fopen('Train-Features-HOG.txt','w');
for i = 1:TrainingSetNum
    img = single(imread(TrainingSetInfo.textdata{i, 1}));
    img = imresize(img, [256 256]);
    hogmatrix = vl_hog(img, cellSize);
    hogvector = hogmatrix(:)';
    for j = 1:length(hogvector)
        fprintf(fid, '%g\t', hogvector(j));
    end
    fprintf(fid, '\n');
end
fclose(fid);

fid = fopen('Test-Features-HOG.txt','w');
for i = 1:TestSetNum
    img = single(imread(TestSetInfo.textdata{i, 1}));
    img = imresize(img, [256 256]);
    hogmatrix = vl_hog(img, cellSize);
    hogvector = hogmatrix(:)';
    for j = 1:length(hogvector)
        fprintf(fid, '%g\t', hogvector(j));
    end
    fprintf(fid, '\n');
end
fclose(fid);

%% For average dividing - cross validation
% fid = fopen('Train-Features-HOG.txt','w');
% for i = 1:TrainingSetNum
%     img = single(imread(TrainingSetInfo.textdata{i, 1}));
%     img = imresize(img, [256 256]);
%     hogmatrix = vl_hog(img, 32);
%     hogvector = hogmatrix(:)';
%     fprintf(fid, '%g\t', TrainingSetInfo.data(i));
%     for j = 1:length(hogvector)
%         if hogvector(j) ~= 0
%             fprintf(fid, '%g:%g\t', j, hogvector(j));
%         end
%     end
%     fprintf(fid, '\n');
% end
% fclose(fid);
% 
% fid = fopen('Test-Features-HOG.txt','w');
% for i = 1:TestSetNum
%     img = single(imread(TestSetInfo.textdata{i, 1}));
%     img = imresize(img, [256 256]);
%     hogmatrix = vl_hog(img, 32);
%     hogvector = hogmatrix(:)';
%     fprintf(fid, '%g\t', TestSetInfo.data(i));
%     for j = 1:length(hogvector)
%         if hogvector(j) ~= 0
%             fprintf(fid, '%g:%g\t', j, hogvector(j));
%         end
%     end
%     fprintf(fid, '\n');
% end
% fclose(fid);

