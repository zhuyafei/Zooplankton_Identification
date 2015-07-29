clear
clc
TrainingSetInfo = importdata('Training_Set.txt');
TrainingSetNum = length(TrainingSetInfo.data);
imgSize = 64;

for num = 2:5
    cellSize = 2^num;
    %% For random dividing - cross validation
    fid = fopen(strcat('./results/', 'Train-Features-HOG-', num2str(cellSize), '-', num2str(imgSize), '.txt'), 'w');
    for i = 1:TrainingSetNum
        img = single(imread(TrainingSetInfo.textdata{i, 1}));
        img = imresize(img, [imgSize imgSize]);
        hogmatrix = vl_hog(img, cellSize);
        hogvector = hogmatrix(:)';
        for j = 1:length(hogvector)
            fprintf(fid, '%g\t', hogvector(j));
        end
        fprintf(fid, '\n');
    end
    fclose(fid);
end