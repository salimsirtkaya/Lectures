%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #4, P.1  %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N = 500; % number of samples
no_iter = 200 ; % number of iterations
mu= 0.02; % step size

% unit variance white gaussian noise
v = randn(N,1);

% generation of x(n)
b=[1 0 0];
a=[1 -1.2728 0.81];

x = filter(b,a,v);

figure;
plot(x);
TITLE('x(n)');

% Iterative w estimation  
% x(n) is approximated by w(1)x(n-1)+w(2)x(n-2)

% initialize w vector
w1(1:no_iter)=0;
w2(1:no_iter)=0;

for n=3:no_iter
    y(n) = [w1(n) w2(n)]*[x(n);x(n-1)];
    e(n) = x(n) - y(n);
    w1(n+1) = w1(n)+mu*e(n)*x(n-1);
    w2(n+1) = w2(n)+mu*e(n)*x(n-2);
end
    
figure;
plot(w1);
TITLE('w1(n)');

figure;
plot(w2);
TITLE('w2(n)');
    