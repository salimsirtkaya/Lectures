%% EE557 - Estimation Theory - TakeHome - Kalman Filtering %%
%% Salim SIRTKAYA - 112346
%% Fall 205-2006

%% This is the mainprogram that calls all the subroutines and generates the
%% outputs mentioned in the take-home and runs a montecarlo simulation

clear all;
close all;
clc;
T = 1; % time interval between the samples
N = 100; % number of points

figNo = 1;

%%figure properties
set(0,'Units','centimeters');

rect_trajectory = [250 250 300 300];
rect_err = [150 150 700 500];
rect_gain = [250 250 400 300];

A = [1 T 0 0; 0 1 0 0; 0 0 1 T; 0 0 0 1];
G = [0.5*T^2 0; T 0; 0 0.5*T^2; 0 T];
C = [1 0 0 0; 0 0 1 0];

Wm = zeros(2,1);
Q = 5*eye(2); % process noise covariance
Vm = zeros(2,1);
R = 5*eye(2); % observation noise covariance

S0 = 10*eye(4); % initial covariance
Xm0 = zeros(4,1); % initial mean of the state

%part a -creation of the trajectory, states and observations
[X_state,Y_observation,figNo] =  trajectory(A,G,C,Wm,Q,Vm,R,S0,Xm0,T,N,figNo);

% part-b -predicted state,filtered state,kalman gain norm with default
% variables
X_filt_b_rms =0;X_predict_b_rms=0;X_filt_error_b_rms=0;X_predict_error_b_rms=0;norm_L1_rms=0;L_fixed1_rms=0;
for i=1:50
    [X_filt_b,X_predict_b,X_prediction_error_b,X_filter_error_b,norm_L1,L_fixed1,figNo] =  kalman('part B',X_state,Y_observation,S0,Xm0,R,Q,C,N,A,G,figNo);
    X_filt_b_rms = X_filt_b_rms + X_filt_b;
    X_predict_b_rms = X_predict_b_rms + X_predict_b;
    X_filt_error_b_rms = X_filt_error_b_rms + X_filter_error_b;
    X_predict_error_b_rms = X_predict_error_b_rms + X_prediction_error_b;
    norm_L1_rms = norm_L1_rms + norm_L1;
    L_fixed1_rms = L_fixed1_rms +L_fixed1;
end

X_filt_b_rms = (X_filt_b_rms/50);
X_predict_b_rms = (X_predict_b_rms/50);
X_filt_error_b_rms = (X_filt_error_b_rms/50);
X_predict_error_b_rms = (X_predict_error_b_rms/50);
norm_L1_rms = (norm_L1_rms/50);
L_fixed1_rms = (L_fixed1_rms/50);

figNo = MonteCarlo_plot('Part B - ',X_filt_b_rms,X_predict_b_rms,X_predict_error_b_rms,X_filt_error_b_rms,norm_L1_rms,figNo);


%part-c -predicted state,filtered state,kalman gain norm with increased Q
X_filt_c_rms =0;X_predict_c_rms=0;X_filt_error_c_rms=0;X_predict_error_c_rms=0;norm_L2_rms=0;L_fixed2_rms=0;

for i=1:50
    [X_filt_c,X_predict_c,X_prediction_error_c,X_filter_error_c,norm_L2,L_fixed2,figNo] =  kalman('part C',X_state,Y_observation,S0,Xm0,R,2*Q,C,N,A,G,figNo);
    X_filt_c_rms = X_filt_c_rms + X_filt_c;
    X_predict_c_rms = X_predict_c_rms + X_predict_c;
    X_filt_error_c_rms = X_filt_error_c_rms + X_filter_error_c;
    X_predict_error_c_rms = X_predict_error_c_rms + X_prediction_error_c;
    norm_L2_rms = norm_L2_rms + norm_L2;
    L_fixed2_rms = L_fixed2_rms +L_fixed2;
end

X_filt_c_rms = (X_filt_c_rms/50);
X_predict_c_rms = (X_predict_c_rms/50);
X_filt_error_c_rms = (X_filt_error_c_rms/50);
X_predict_error_c_rms = (X_predict_error_c_rms/50);
norm_L2_rms = (norm_L2_rms/50);
L_fixed2_rms = (L_fixed2_rms/50);

figNo = MonteCarlo_plot('Part C - ',X_filt_c_rms,X_predict_c_rms,X_predict_error_c_rms,X_filt_error_c_rms,norm_L2_rms,figNo);

%part-d -predicted state, filtered state with fixed gain in part b
X_filt_fixed_d1_rms=0;X_predict_fixed_d1_rms=0;X_filter_error_fixed_d1_rms=0;X_prediction_error_fixed_d1_rms=0;
for i=1:50
    [X_filt_fixed_d1,X_predict_fixed_d1,X_prediction_error_fixed_d1,X_filter_error_fixed_d1,figNo] =  kalman_fixedgain('part D-1',L_fixed1_rms,X_state,Y_observation,S0,Xm0,R,Q,C,N,A,G,figNo);
    X_filt_fixed_d1_rms = X_filt_fixed_d1_rms + X_filt_fixed_d1;
    X_predict_fixed_d1_rms = X_predict_fixed_d1_rms + X_predict_fixed_d1;
    X_filter_error_fixed_d1_rms = X_filter_error_fixed_d1_rms + X_filter_error_fixed_d1;
    X_prediction_error_fixed_d1_rms = X_prediction_error_fixed_d1_rms + X_prediction_error_fixed_d1;
end

X_filt_fixed_d1_rms = (X_filt_fixed_d1_rms/50);
X_predict_fixed_d1_rms = (X_predict_fixed_d1_rms/50);
X_filter_error_fixed_d1_rms = (X_filter_error_fixed_d1_rms/50);
X_prediction_error_fixed_d1_rms = (X_prediction_error_fixed_d1_rms/50);

figNo = MonteCarlo_plot('Part D-1 ',X_filt_fixed_d1_rms,X_predict_fixed_d1_rms,X_prediction_error_fixed_d1_rms,X_filter_error_fixed_d1_rms,norm_L2_rms,figNo);

%part-d -predicted state, filtered state with fixed gain in part c
X_filt_fixed_d2_rms=0;X_predict_fixed_d2_rms=0;X_filter_error_fixed_d2_rms=0;X_prediction_error_fixed_d2_rms=0;
for i=1:50
    [X_filt_fixed_d2,X_predict_fixed_d2,X_prediction_error_fixed_d2,X_filter_error_fixed_d2,figNo] =  kalman_fixedgain('part D-2',L_fixed2_rms,X_state,Y_observation,S0,Xm0,R,2*Q,C,N,A,G,figNo);
    X_filt_fixed_d2_rms = X_filt_fixed_d2_rms + X_filt_fixed_d2;
    X_predict_fixed_d2_rms = X_predict_fixed_d2_rms + X_predict_fixed_d2;
    X_filter_error_fixed_d2_rms = X_filter_error_fixed_d2_rms + X_filter_error_fixed_d2;
    X_prediction_error_fixed_d2_rms = X_prediction_error_fixed_d2_rms + X_prediction_error_fixed_d1;    
end

X_filt_fixed_d2_rms = (X_filt_fixed_d2_rms/50);
X_predict_fixed_d2_rms = (X_predict_fixed_d2_rms/50);
X_filter_error_fixed_d2_rms = (X_filter_error_fixed_d2_rms/50);
X_prediction_error_fixed_d2_rms = (X_prediction_error_fixed_d2_rms/50);

figNo = MonteCarlo_plot('Part D-2 ',X_filt_fixed_d2_rms,X_predict_fixed_d2_rms,X_prediction_error_fixed_d2_rms,X_filter_error_fixed_d2_rms,norm_L2_rms,figNo);

%part-e -predicted state,filtered state,kalman gain norm with reduced
%initial state covariance
X_filt_e_rms=0;X_predict_e_rms=0;X_filt_error_e_rms=0;X_predict_error_e_rms=0;norm_Le_rms=0;
for i=1:50
    [X_filt_e,X_predict_e,X_prediction_error_e,X_filter_error_e,norm_Le,L_fixed_e,figNo] =  kalman('part E',X_state,Y_observation,2*eye(4),Xm0,R,Q,C,N,A,G,figNo);
    X_filt_e_rms = X_filt_e_rms + X_filt_e;
    X_predict_e_rms = X_predict_e_rms + X_predict_e;
    X_filt_error_e_rms = X_filt_error_e_rms + X_filter_error_e;
    X_predict_error_e_rms = X_predict_error_e_rms + X_prediction_error_e;
    norm_Le_rms = norm_Le_rms + norm_Le;  
end

X_filt_e_rms = (X_filt_e_rms/50);
X_predict_e_rms = (X_predict_e_rms/50);
X_filt_error_e_rms = (X_filt_error_e_rms/50);
X_predict_error_e_rms = (X_predict_error_e_rms/50);
norm_Le_rms = (norm_Le_rms/50);

figNo = MonteCarlo_plot('Part E - ',X_filt_e_rms,X_predict_e_rms,X_predict_error_e_rms,X_filt_error_e_rms,norm_Le_rms,figNo);

%part-f -predicted state,filtered state,kalman gain norm with correlated R
%and Q matrices
R_f = [5 2; 2 5];
Q_f = [10 2; 2 5];

X_filt_f_rms=0;X_predict_f_rms=0;X_filt_error_f_rms=0;X_predict_error_f_rms=0;norm_Lf_rms=0;
for i=1:50
    [X_filt_f,X_predict_f,X_prediction_error_f,X_filter_error_f,norm_Lf,L_fixed_f,figNo] =  kalman('part F',X_state,Y_observation,S0,Xm0,R_f,Q_f,C,N,A,G,figNo);
    X_filt_f_rms = X_filt_f_rms + X_filt_f;
    X_predict_f_rms = X_predict_f_rms + X_predict_f;
    X_filt_error_f_rms = X_filt_error_f_rms + X_filter_error_f;
    X_predict_error_f_rms = X_predict_error_f_rms + X_prediction_error_f;
    norm_Lf_rms = norm_Lf_rms + norm_Lf;    
end

X_filt_f_rms = sqrt((X_filt_f_rms/50).^2);
X_predict_f_rms = sqrt((X_predict_f_rms/50).^2);
X_filt_error_f_rms = sqrt((X_filt_error_f_rms/50).^2);
X_predict_error_f_rms = sqrt((X_predict_error_f_rms/50).^2);
norm_Lf_rms = sqrt((norm_Lf_rms/50).^2);

figNo = MonteCarlo_plot('Part F - ',X_filt_f_rms,X_predict_f_rms,X_predict_error_f_rms,X_filt_error_f_rms,norm_Lf_rms,figNo);

% part-g -generate a new trajectory

for k=1:50
    x_g(k)=k;
    vx_g(k)=1;
    y_g(k)=k;
    vy_g(k)=1;
end

for k=51:100
    x_g(k)=k;
    vx_g(k)=1;
    y_g(k)=0.1*k^2-200;
    vy_g(k)=0.2*k;
end

X_g(1,1,:)=x_g;
X_g(2,1,:)=vx_g;
X_g(3,1,:)=y_g;
X_g(4,1,:)=vy_g;

figure('position',rect_trajectory);
plot(x_g,y_g);
TITLE('part-G -new trajectory');
XLABEL(['FIGURE - ',num2str(figNo)]);
figNo = figNo + 1;

%Generate the observations
%section i
R_gi = 5*eye(2);
for k=1:N
    Y_gi(:,:,k) = C * X_g(:,:,k) + mvnrnd(Vm,R_gi)';
end

figure('position',rect_trajectory);;
plot(Y_gi(1,:),Y_gi(2,:));
TITLE('part -G-i - Observed new trajectory with uncorrelated R');
XLABEL(['FIGURE - ',num2str(figNo)]);
figNo = figNo + 1;

%section ii
R_gii = [5 2;2 5];
for k=1:N
    Y_gii(:,:,k) = C * X_g(:,:,k) + mvnrnd(Vm,R_gii)';
end

figure('position',rect_trajectory);;
plot(Y_gii(1,:),Y_gii(2,:));
TITLE('part -G-ii - Observed new trajectory with correlated R');
XLABEL(['FIGURE - ',num2str(figNo)]);
figNo = figNo + 1;

%%part h
Q_g = 0.1*eye(2);
S0_g = 10*eye(4);

X_filt_h1_rms=0;X_predict_h1_rms=0;X_filt_error_h1_rms=0;X_predict_error_h1_rms=0;norm_Lh1_rms=0;
for i=1:50
    [X_filt_h1,X_predict_h1,X_prediction_error_h1,X_filter_error_h1,norm_Lh1,L_fixed_h1,figNo] =  kalman('part H-i',X_g,Y_gi,S0_g,Xm0,R_gi,Q_g,C,N,A,G,figNo);
    X_filt_h1_rms = X_filt_h1_rms + X_filt_h1;
    X_predict_h1_rms = X_predict_h1_rms + X_predict_h1;
    X_filt_error_h1_rms = X_filt_error_h1_rms + X_filter_error_h1;
    X_predict_error_h1_rms = X_predict_error_h1_rms + X_prediction_error_h1;
    norm_Lh1_rms = norm_Lh1_rms + norm_Lh1;    
end

X_filt_h1_rms = (X_filt_h1_rms/50);
X_predict_h1_rms = (X_predict_h1_rms/50);
X_filt_error_h1_rms = (X_filt_error_h1_rms/50);
X_predict_error_h1_rms = (X_predict_error_h1_rms/50);
norm_Lh1_rms = (norm_Lh1_rms/50);

figNo = MonteCarlo_plot('Part H1 - ',X_filt_h1_rms,X_predict_h1_rms,X_predict_error_h1_rms,X_filt_error_h1_rms,norm_Lh1_rms,figNo);
%%%%%%%%%
X_filt_h2_rms=0;X_predict_h2_rms=0;X_filt_error_h2_rms=0;X_predict_error_h2_rms=0;norm_Lh2_rms=0;
for i=1:50
    [X_filt_h2,X_predict_h2,X_prediction_error_h2,X_filter_error_h2,norm_Lh2,L_fixed_h2,figNo] =  kalman('part H-ii',X_g,Y_gii,S0_g,Xm0,R_gii,Q_g,C,N,A,G,figNo);
    X_filt_h2_rms = X_filt_h2_rms + X_filt_h2;
    X_predict_h2_rms = X_predict_h2_rms + X_predict_h2;
    X_filt_error_h2_rms = X_filt_error_h2_rms + X_filter_error_h2;
    X_predict_error_h2_rms = X_predict_error_h2_rms + X_prediction_error_h2;
    norm_Lf_rms = norm_Lf_rms + norm_Lh2; 
end

X_filt_h2_rms = (X_filt_h2_rms/50);
X_predict_h2_rms = (X_predict_h2_rms/50);
X_filt_error_h2_rms = (X_filt_error_h2_rms/50);
X_predict_error_h2_rms = (X_predict_error_h2_rms/50);
norm_Lh2_rms = (norm_Lh2_rms/50);

figNo = MonteCarlo_plot('Part H2 - ',X_filt_h2_rms,X_predict_h2_rms,X_predict_error_h2_rms,X_filt_error_h2_rms,norm_Lh2_rms,figNo);

%%part g
Q_i = 2*eye(2);
S0_i = 10*eye(4);

X_filt_i1_rms=0;X_predict_i1_rms=0;X_filt_error_i1_rms=0;X_predict_error_i1_rms=0;norm_Li1_rms=0;
for i=1:50
    [X_filt_i1,X_predict_i1,X_prediction_error_i1,X_filter_error_i1,norm_Li1,L_fixed_i1,figNo] =  kalman('part I-i',X_g,Y_gi,S0_i,Xm0,R_gi,Q_i,C,N,A,G,figNo);
    X_filt_i1_rms = X_filt_i1_rms + X_filt_i1;
    X_predict_i1_rms = X_predict_i1_rms + X_predict_i1;
    X_filt_error_i1_rms = X_filt_error_i1_rms + X_filter_error_i1;
    X_predict_error_i1_rms = X_predict_error_i1_rms + X_prediction_error_i1;
    norm_Li1_rms = norm_Li1_rms + norm_Li1;    
end

X_filt_i1_rms = (X_filt_i1_rms/50);
X_predict_i1_rms = (X_predict_i1_rms/50);
X_filt_error_i1_rms = (X_filt_error_i1_rms/50);
X_predict_error_i1_rms = (X_predict_error_i1_rms/50);
norm_Li1_rms = (norm_Li1_rms/50);

figNo = MonteCarlo_plot('Part I-1 - ',X_filt_i1_rms,X_predict_i1_rms,X_predict_error_i1_rms,X_filt_error_i1_rms,norm_Li1_rms,figNo);

%%%%%%%%%%%%
X_filt_i2_rms=0;X_predict_i2_rms=0;X_filt_error_i2_rms=0;X_predict_error_i2_rms=0;norm_Li2_rms=0;
for i=1:50
    [X_filt_i2,X_predict_i2,X_prediction_error_i2,X_filter_error_i2,norm_Li2,L_fixed_i2,figNo] =  kalman('part I-ii',X_g,Y_gii,S0_i,Xm0,R_gii,Q_i,C,N,A,G,figNo);
    X_filt_i2_rms = X_filt_i2_rms + X_filt_i2;
    X_predict_i2_rms = X_predict_i2_rms + X_predict_i2;
    X_filt_error_i2_rms = X_filt_error_i2_rms + X_filter_error_i2;
    X_predict_error_i2_rms = X_predict_error_i2_rms + X_prediction_error_i2;
    norm_Li2_rms = norm_Li2_rms + norm_Li2;    
end

X_filt_i2_rms = (X_filt_i2_rms/50);
X_predict_i2_rms = (X_predict_i2_rms/50);
X_filt_error_i2_rms = (X_filt_error_i2_rms/50);
X_predict_error_i2_rms = (X_predict_error_i2_rms/50);
norm_Li2_rms = (norm_Li2_rms/50);

figNo = MonteCarlo_plot('Part I-2 - ',X_filt_i2_rms,X_predict_i2_rms,X_predict_error_i2_rms,X_filt_error_i2_rms,norm_Li2_rms,figNo);

