%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #5, P.1-b   %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N = 500; % number of samples
K = 100; % number of trials

% RLS Implementation

for i=1:K
    % unit variance white gaussian noise
    v = randn(N,1);
    % generation of x(n)
    b=1;
    a=[1 -1.2728 0.81];
    
    %desired signal
    x = filter(b,a,v);
    
    [W,alpha(i,:)] = rls(x,x,2,0.90);    
end

for i=1:K
    for n=1:N-1
        err(n)=sum(alpha(:,n).^2);
    end
end

err = err/K;

plot(err);
TITLE('Learning Curve for RLS, no of trials =100, lambda = 0.90');