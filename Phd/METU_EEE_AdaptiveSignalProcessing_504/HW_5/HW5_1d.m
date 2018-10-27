%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #5, P.1-d   %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Sliding window RLS results

close all;
clear all;

N = 500; % number of samples

% unit variance white gaussian noise
v = randn(N,1);

% generation of x(n)
b=1;
a=[1 -1.2728 0.81];

%desired signal
x = filter(b,a,v);

% RLS Implementation

[W,alpha] = rls_sliding(x,x,2,50,1);

plot(W(:,1));
TITLE('Sliding Window RLS - w1');
figure; 
plot(W(:,2))
TITLE('Sliding Window RLS - w2');