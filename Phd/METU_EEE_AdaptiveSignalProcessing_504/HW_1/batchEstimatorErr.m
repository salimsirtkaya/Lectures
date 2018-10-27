function [avErrMSE, avErrME, SNR] = batchEstimatorErr(ro2, N, iter)

avErrMSE = 0;
avErrME = 0;

for i = 1:iter
    y = random('norm', 0, 1);           %a random scalar with 0 mean, 1 variance (i)
    n = random('norm', 0, ro2, 1, N);   %noise vector (ii)
    obs = repmat(y, 1, N) + n;          %observation vector (iii)
 
    % Linear Minimum MSE Estimator
    c = ro2 / 1; % E{y^2}=1, assume we know the statistics of the r.v.
    SNR = 1 / c;
    yCap = sum(obs)*(1/(N+c)); %estimation output
    
    sqErr = (y - yCap)^2;
    avErrMSE = avErrMSE + sqErr;

    % Mean Estimator
    yCap2 = sum(obs)*(1/N);
    
    sqErr2 = (y - yCap2)^2;
    avErrME = avErrME + sqErr2;
   
end

%Square of Error for estimates
avErrMSE = avErrMSE / iter; %linear minimum MSE estimator
avErrME = avErrME / iter;   %mean estimator