%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #5, P.1-a   %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N = 200; % number of samples

% unit variance white gaussian noise
v = randn(N,1);

% generation of x(n)
b=1;
a=[1 -1.2728 0.81];

%desired signal
x = filter(b,a,v);

% RLS Implementation

[W,alpha] = rls(x,x,2,1);

plot(W(:,1));
TITLE('RLS - w1 for lambda = 1');
figure; 
plot(W(:,2))
TITLE('RLS - w2 for lambda = 1');