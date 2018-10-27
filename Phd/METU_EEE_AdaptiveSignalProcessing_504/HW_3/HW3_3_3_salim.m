%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #3, P.3 Exercise3   %
% Salim Sirtkaya, 112434-6               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N=500; % number of samples
p=6;    % model order
mu=0.1; % step size
gama=1; % Amplitude of noise, A


x=randn(N,1);

b=[1 0.5];
a=[1 0.9];

d = filter(b,a,x);

% unit variance gaussian noise
v=randn(N,1);

d_n = d+gama*v;

[W,E]= llms(x,d_n,mu,p);

figure;
plot(W);
TITLE('The learning curve for u=0.1, 6th order, A=1');

figure;
semilogy(E.^2);
TITLE('The error for u=0.1, 6th order filter,A=1');

w1_final=W(N,1)
w2_final=W(N,2)
w3_final=W(N,3)
w4_final=W(N,4)

K=5;

Err=0;

for k=1:K
    x=randn(N,1);
    d = filter(b,a,x);
    
    [W,E]= llms(x,d_n,mu,p);
    Err= Err + E.^2;
end

Err = Err/K;

figure;
semilogy(Err);
TITLE('Mean Square Error approximation, u=0.1');

mse = sum (Err(1:100))/100


