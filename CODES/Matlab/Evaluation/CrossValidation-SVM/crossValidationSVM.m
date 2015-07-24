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
        model = svmtrain(train_target, train_data, '-s 0 -t 0 -d 1 -g 0 -r 0 -c 1 -e 0.0001 -h 1');
        [predict_label, accuracy, decision_values] = svmpredict(test_target, test_data, model);
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
writeData(resultCM, strcat('HOG-SVM-', num2str(folds), '-folds-', num2str(repetitions), '-repetitions', '.txt'));
