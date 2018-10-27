function phi=Welch_salim(y,w,K,L)

% Exercise 2.20 --> The Welch method of spectral estimation.


N=length(y);     % total data length
M=length(w);     % length of each observations to split from y


S=fix((N-M+K)/K); % number of subsamples
P=mean(v.^2);     % the power of the window vector v

y=y(:);          % make y a column vector

% compute the weighted periodgram for each subsample of observations
% and sum the results

phi=zeros(L,1);
for i = 1 : S,
   phi=phi + periodogramse(y((i-1)*K+1:(i-1)*K+M),w,L);
end

phi=phi/S/P;
