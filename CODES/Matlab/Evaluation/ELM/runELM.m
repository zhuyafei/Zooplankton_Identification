clear
clc
trainSet = importdata('Training_Set.txt');
trainSetNum = length(trainSet.data);
trainFeature = load('Train-Features-HOG.txt');
label = trainSet.data;

lowvec=min(trainFeature);  
upvec=max(trainFeature);
trainFeature = scaling( trainFeature,lowvec,upvec);

repetitions = 5;
folds = 2;
classesNum = 13;

numHiddenNeur = 650;
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
        
        TrainingData_File = [train_target,train_data];
        TestingData_File = [test_target,test_data];
        
        [TrainingTime, TestingTime, TrainingAccuracy, TestingAccuracy,predictLabel,actualLabel,accuracyTest,accuracyTrain] = elm(TrainingData_File, TestingData_File, 1, numHiddenNeur, 'sig');
    end
    [cm,order] = confusionmat(actualLabel, predictLabel);
    resultCM = resultCM+cm;
end
writeData(resultCM, strcat('ELM-', num2str(folds), '-folds-', num2str(repetitions), '-repetitions-', num2str(numHiddenNeur), '.txt'));