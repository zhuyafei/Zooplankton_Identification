clear
clc
trainSet = importdata('Training_Set.txt');
trainSetNum = length(trainSet.data);
trainFeature1 = load('19+7-Features-MATLAB-our-ZY.txt');
trainFeature2 = load('Train-Features-LBP.txt');
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
        train_data1 = trainFeature1(train,:);
        train_data2 = trainFeature2(train,:);
        train_target = label(train);
        test_data1 = trainFeature1(test, :);
        test_data2 = trainFeature2(test, :);
        test_target = label(test);
        model1 = classRF_train(train_data1, train_target, 100);
        model2 = svmtrain(train_target, train_data2, '-s 0 -t 0 -d 1 -g 0 -r 0 -c 1 -e 0.0001 -h 1 -b 1');
        [predict_label_train1, prob_estimates_train1] = classRF_predict(train_data1, model1);
        [predict_label_train2, accuracy_train2, prob_estimates_train2] = svmpredict(train_target, train_data2, model2,'-b 1');
        
        [predict_label_test1, prob_estimates_test1] = classRF_predict(test_data1, model1);
        [predict_label_test2, accuracy_test2, prob_estimates_test2] = svmpredict(test_target, test_data2, model2,'-b 1');
        
        predictFeaturesTrain = [prob_estimates_train1/100,prob_estimates_train2];
        predictFeaturesTest = [prob_estimates_test1/100,prob_estimates_test2];
        
        model = svmtrain(train_target, predictFeaturesTrain, '-s 0 -t 0 -d 1 -g 0 -r 0 -c 1 -e 0.0001 -h 1');
        [predict_label, accuracy, decision_values] = svmpredict(test_target, predictFeaturesTest, model);

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
writeData(resultCM, strcat('FeaturesFusion2', num2str(folds), '-folds-', num2str(repetitions), '-repetitions', '.txt'));

