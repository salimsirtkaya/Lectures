%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #3, P.3 Exercise2   %
% Salim Sirtkaya, 112434-6               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N=100; % number of samples
p=5;    % model order
mu=0.1; % step size
gama=0.1;

x=randn(N,1);

b=[1 1.8 0.81];
a=1;

d = filter(b,a,x);

% unit variance gaussian noise
v=randn(N,1);

d_n = d+gama*v;

%% part b
[W,E]= llms(x,d_n,mu,p);

figure;
plot(W);
TITLE('The learning curve for u=0.1, 5th order, gama=0.1 ');

figure;
semilogy(E.^2);
TITLE('The error for u=0.1, 5th order filter, gama=0.1');

w1_final=W(N,1)
w2_final=W(N,2)
w3_final=W(N,3)
w4_final=W(N,4)


