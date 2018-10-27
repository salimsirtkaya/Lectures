function recursiveEstimator(ro2, N)

y = random('norm', 0, 1)           %a random scalar with 0 mean, 1 variance (i)
n = random('norm', 0, ro2, 1, N);   %noise vector (ii)
obs = repmat(y, 1, N) + n;          %observation vector (iii)

% Linear Minimum MSE Estimator
c = ro2 / 1; %(sum(obs.^2)/N);
SNR = 1 / c;

yCap(1) = obs(1)/(1+c);
for i = 2 : N
    yCap(i) = ((i-1+c)/(i+c))*yCap(i-1) + (obs(i)/(i+c));  
end

% Mean Estimator
yCap2(1) = obs(1);
for i = 2 : N
    yCap2(i) = ((i-1)/(i))*yCap2(i-1) + (obs(i)/(i));  
end

figure;
subplot(2,1,1), plot (yCap), grid, title('Estimation vs Number of Observations in LMMSEE');
xlabel('Number of Observations'), ylabel('Estimation');
subplot(2,1,2), plot (yCap2), grid , title('Estimation vs Number of Observations in Mean Estimator');
xlabel('Number of Observations'), ylabel('Estimation');


figure;
subplot(2,1,1), plot (yCap - y), grid, title('Estimation Error vs Number of Observations in LMMSEE');
xlabel('Number of Observations'), ylabel('Estimation Error');
subplot(2,1,2), plot (yCap2 - y), grid , title('Estimation Error vs Number of Observations in Mean Estimator');
xlabel('Number of Observations'), ylabel('Estimation Error');