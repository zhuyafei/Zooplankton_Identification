clear
clc
TrainingSetInfo = importdata('Training_Set.txt');
TestSetInfo = importdata('Test_Set.txt');

training_label_vector = TrainingSetInfo.data;
test_label_vector = TestSetInfo.data;
training_instance_matrix = load('Train-Features-LBP.txt');
test_instance_matrix = load('Test-Features-LBP.txt');

model = svmtrain(training_label_vector, training_instance_matrix, '-c 1 -g 0.07 -b 1');
[predict_label, accuracy, prob_estimates] = svmpredict(test_label_vector, test_instance_matrix, model, '-b 1');