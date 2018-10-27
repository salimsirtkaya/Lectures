%% EE557 - Estimation Theory - TakeHome - Kalman Filtering %%
%% Salim SIRTKAYA - 112346
%% Fall 205-2006

%%plot function for montecarlo simulations

function [figNo] = MonteCarlo_plot(title,X_filt,X_predict,X_prediction_error,X_filter_error,K,figNo)

N = length(X_predict);
T=1;
rect_trajectory = [250 250 300 300];
rect_err = [150 150 700 500];
rect_gain = [250 250 400 300];

x_predict(1:N) = X_predict(1,1,:);
y_predict(1:N) = X_predict(3,1,:);
figure('position',rect_trajectory);;
plot(x_predict,y_predict);
TITLE([title,' predicted state']);
XLABEL(['FIGURE - ',num2str(figNo)]);
figNo = figNo + 1;

x_filter(1:N) = X_filt(1,1,:);
y_filter(1:N) = X_filt(3,1,:);
figure('position',rect_trajectory);;
plot(x_filter,y_filter);
TITLE([title,' filtered state']);
XLABEL(['FIGURE - ',num2str(figNo)]);
figNo = figNo+1;

x_prediction_error(1:N) = X_prediction_error(1,1,:);
vx_prediction_error(1:N) = X_prediction_error(2,1,:);
y_prediction_error(1:N) = X_prediction_error(3,1,:);
vy_prediction_error(1:N) = X_prediction_error(4,1,:);

%rms errors of the predicted state
x_prediction_rms = sqrt(mean(x_prediction_error.^2)); 
vx_prediction_rms = sqrt(mean(vx_prediction_error.^2)); 
y_prediction_rms = sqrt(mean(y_prediction_error.^2)); 
vy_prediction_rms = sqrt(mean(vy_prediction_error.^2)); 

figure('position',rect_err);
TITLE([title,' prediction state errors']);
Subplot(2,2,1),plot(x_prediction_error);TITLE([title,' predicted state error in x position']);
XLABEL(['rms error = ',num2str(x_prediction_rms)]);YLABEL(['FIGURE - ', num2str(figNo)]);
figNo = figNo +1;
Subplot(2,2,2),plot(vx_prediction_error);TITLE([title,' predicted state error in x velocity']);
XLABEL(['rms error = ',num2str(vx_prediction_rms)]);
Subplot(2,2,3),plot(y_prediction_error);TITLE([title,' predicted state error in y position']);
XLABEL(['rms error = ',num2str(y_prediction_rms)]);
Subplot(2,2,4),plot(vy_prediction_error);TITLE([title,' predicted state error in y velocity']);
XLABEL(['rms error = ',num2str(vy_prediction_rms)]);

x_filter_error(1:N) = X_filter_error(1,1,:);
vx_filter_error(1:N) = X_filter_error(2,1,:);
y_filter_error(1:N) = X_filter_error(3,1,:);
vy_filter_error(1:N) = X_filter_error(4,1,:);

%rms errors of the filtered state
x_filter_rms = sqrt(mean(x_filter_error.^2)); 
vx_filter_rms = sqrt(mean(vx_filter_error.^2)); 
y_filter_rms = sqrt(mean(y_filter_error.^2)); 
vy_filter_rms = sqrt(mean(vy_filter_error.^2)); 

figure('position',rect_err);
TITLE([title,'  filtered state errors']);
Subplot(2,2,1),plot(x_filter_error);TITLE([title,'  filtered state error in x position']);
XLABEL(['rms error = ',num2str(x_filter_rms)]);YLABEL(['FIGURE - ', num2str(figNo)]);
figNo = figNo +1;
Subplot(2,2,2),plot(vx_filter_error);TITLE([title,'  filtered state error in x velocity']);
XLABEL(['rms error = ',num2str(vx_filter_rms)]);
Subplot(2,2,3),plot(y_filter_error);TITLE([title,'  filtered state error in y position']);
XLABEL(['rms error = ',num2str(y_filter_rms)]);
Subplot(2,2,4),plot(vy_filter_error);TITLE([title,'  filtered state error in y velocity']);
XLABEL(['rms error = ',num2str(vy_filter_rms)]);

figure('position',rect_gain);
plot(K);
TITLE([title,' - Kalman Gain Matrix Norm']);
XLABEL(['FIGURE - ',num2str(figNo)]);
figNo = figNo+1;

    
