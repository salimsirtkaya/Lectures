%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #1, P.5     %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc;
clear all;
close all;

% P.5:(a)
[avErrMSE_a, avErrME_a, SNR_a] = batchEstimatorErr(1, 8, 1000);
disp('--------  P.5-(a)  -----------');
disp('Average Error for Linear Minimum MSE Estimator:'), disp(avErrMSE_a);
disp('Average Error for Mean Estimator:'), disp(avErrME_a);

%P.5:(b)
i = 0;
for ro2 = 0.1 : 0.1 : 10
    i = i+1;
    [avErrMSE_b(i), avErrME_b(i), SNR_b(i)] = batchEstimatorErr(ro2, 8, 1000);
end

figure;
subplot(2,1,1), loglog (SNR_b, avErrMSE_b), grid, title('Avg Square Error vs SNR in LMMSE Estimator');
xlabel('SNR'), ylabel('avg sqr err in LMMSEE');
subplot(2,1,2), loglog (SNR_b, avErrME_b), grid , title('Avg Square Error vs SNR in Mean Estimator');
xlabel('SNR'), ylabel('avg sqr err in ME');

%P.5:(c)
recursiveEstimator(1, 300);