%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #3, P.3 Exercise1   %
% Salim Sirtkaya, 112434-6               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N=100; % number of samples
p=3;
mu=0.1;

x=randn(N,1);

b=[1 1.8 0.81];
a=1;

d = filter(b,a,x);

%% part b
[W,E]= llms(x,d,mu,p);

figure;
plot(W);
TITLE('The learning curve for u=0.1, third order filter');

figure;
semilogy(E.^2);
TITLE('The error for u=0.1, third order filter');

w1_final=W(N,1)
w2_final=W(N,2)
w3_final=W(N,3)


% part c

K=5;

Err=0;

for k=1:K
    x=randn(N,1);
    d = filter(b,a,x);
    
    [W,E]= llms(x,d,mu,p);
    Err= Err + E.^2;
end

Err = Err/K;

figure;
semilogy(Err);
TITLE('Mean Square Error approximation, u=0.1');

excess_error = sum(Err(40:100))/60
mse = sum (Err(1:100))/100

