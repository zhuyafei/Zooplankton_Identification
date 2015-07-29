clear
clc
TrainingSetInfo = importdata('Training_Set.txt');
TrainingSetNum = length(TrainingSetInfo.data);
imgSize = 64;

for num = 2:5
    cellSize = 2^num;
    %% For random dividing - cross validation
    fid = fopen(strcat('./results/', 'Train-Features-LBP-', num2str(cellSize), '-', num2str(imgSize), '.txt'), 'w');
    for i = 1:TrainingSetNum
        img = single(imread(TrainingSetInfo.textdata{i, 1}));
        img = imresize(img, [imgSize imgSize]);
        lbpmatrix = vl_lbp(img, cellSize);
        lbpvector = lbpmatrix(:)';
        for j = 1:length(lbpvector)
            fprintf(fid, '%g\t', lbpvector(j));
        end
        fprintf(fid, '\n');
    end
    fclose(fid);
end