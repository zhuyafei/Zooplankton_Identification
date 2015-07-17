clear
clc
TrainingSetInfo = importdata('Training_Set.txt');
TestSetInfo = importdata('Test_Set.txt');
TrainingSetNum = length(TrainingSetInfo.data);
TestSetNum = length(TestSetInfo.data);

%% For random dividing - cross validation
fid = fopen('Train-Features-LBP.txt','w');
for i = 1:TrainingSetNum
    img = single(imread(TrainingSetInfo.textdata{i, 1}));
    img = imresize(img, [256 256]);
    lbpmatrix = vl_lbp(img, 32);
    lbpvector = lbpmatrix(:)';
    for j = 1:length(lbpvector)
        fprintf(fid, '%g\t', lbpvector(j));
    end
    fprintf(fid, '\n');
end
fclose(fid);

fid = fopen('Test-Features-LBP.txt','w');
for i = 1:TestSetNum
    img = single(imread(TestSetInfo.textdata{i, 1}));
    img = imresize(img, [256 256]);
    lbpmatrix = vl_hog(img, 32);
    lbpvector = lbpmatrix(:)';
    for j = 1:length(lbpvector)
        fprintf(fid, '%g\t', lbpvector(j));
    end
    fprintf(fid, '\n');
end
fclose(fid);

%% For average dividing - cross validation
% fid = fopen('Train-Features-LBP.txt','w');
% for i = 1:TrainingSetNum
%     img = single(imread(TrainingSetInfo.textdata{i, 1}));
%     img = imresize(img, [256 256]);
%     lbpmatrix = vl_lbp(img, 32);
%     lbpvector = lbpmatrix(:)';
%     fprintf(fid, '%g\t', TrainingSetInfo.data(i));
%     for j = 1:length(lbpvector)
%         if lbpvector(j) ~= 0
%             fprintf(fid, '%g:%g\t', j, lbpvector(j));
%         end
%     end
%     fprintf(fid, '\n');
% end
% fclose(fid);
% 
% fid = fopen('Test-Features-LBP.txt','w');
% for i = 1:TestSetNum
%     img = single(imread(TestSetInfo.textdata{i, 1}));
%     img = imresize(img, [256 256]);
%     lbpmatrix = vl_lbp(img, 32);
%     lbpvector = lbpmatrix(:)';
%     fprintf(fid, '%g\t', TestSetInfo.data(i));
%     for j = 1:length(lbpvector)
%         if lbpvector(j) ~= 0
%             fprintf(fid, '%g:%g\t', j, lbpvector(j));
%         end
%     end
%     fprintf(fid, '\n');
% end
% fclose(fid);

