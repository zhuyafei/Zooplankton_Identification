clear
clc
trainSet = importdata('Training_Set.txt');
trainSetNum = length(trainSet.data);
trainFeature = load('Train-Features-HOG.txt');
label = trainSet.data;
repetitions = 5;
folds = 2;
classesNum = 13;

resultCM = zeros(classesNum, classesNum);
for trial = 1:repetitions
    indices = crossvalind('Kfold', trainSetNum, folds);
    num=1;
    for k = 1:folds
        test = (indices == k); 
        train = ~test;
        train_data = trainFeature(train,:);
        train_target = label(train);
        test_data = trainFeature(test, :);
        test_target = label(test);
        model = classRF_train(train_data, train_target, 100);
        predict_label = classRF_predict(test_data, model);
        labelSize = length(predict_label);
        for i = 1:labelSize
            predictLabel(num,1) = predict_label(i, 1);
            actualLabel(num,1) = test_target(i, 1);
            num = num+1;
        end
    end
    [cm,order] = confusionmat(actualLabel, predictLabel);
    resultCM = resultCM+cm;
end
writeData(resultCM, strcat('HOG-RF-', num2str(folds), '-folds-', num2str(repetitions), '-repetitions', '.txt'));
