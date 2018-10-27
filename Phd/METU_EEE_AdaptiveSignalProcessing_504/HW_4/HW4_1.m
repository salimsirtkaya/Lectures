%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #4, P.1  %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N = 500; % number of samples
no_iter = 300 ; % number of iterations
mu= 0.005; % step size

% unit variance white gaussian noise
v = randn(N,1);

% generation of x(n)
b=1;
a=[1 -1.2728 0.81];

x = filter(b,a,v);

% Iterative w estimation  
% x(n) is approximated by w(1)x(n-1)+w(2)x(n-2)

% initialize w vector
w1(1:no_iter)=0;
w2(1:no_iter)=0;

for n=3:no_iter
    y(n) = [w1(n) w2(n)]*[x(n-1);x(n-2)];
    e(n) = x(n) - y(n);
    w1(n+1) = w1(n)+mu*e(n)*x(n-1);
    w2(n+1) = w2(n)+mu*e(n)*x(n-2);
end
    
figure;
plot(w1);
TITLE('w1(n) for mu = 0.02');

figure;
plot(w2);
TITLE('w2(n) for mu = 0.02');

%% p-vector algorithm implementation

mup=0.01;
no_iter = 200;
wp1(1:no_iter)=0;
wp2(1:no_iter)=0;
y=0;

% p vector estimation

p(1)=0;
p(2)=0;

eps=0.001;

for i=2:500
    p(1) = (p(1) + x(i)*x(i-1));
end
p(1) = p(1)/499;
%p(1) = p(1)+eps; % introduce small changes to p-vector to see the effect

for i=3:500
    p(2) = (p(2) + x(i)*x(i-2));
end
p(2) = p(2)/498;
%p(2) = p(2)+eps; % introduce small changes to p-vector to see the effect

% p = xcorr(x,'coeff');
% p= p(size(x):2*size(x)-1);

for n=3:no_iter
    y(n) = [wp1(n) wp2(n)]*[x(n-1);x(n-2)];
    wp1(n+1) = wp1(n) + mup*p(1) - mup*y(n)*x(n-1);
    wp2(n+1) = wp2(n) + mup*p(2) - mup*y(n)*x(n-2);
end

figure;
plot(wp1);
TITLE('p-vector algorithm, wp1(n) for mu = 0.008, p_vector is changed');

figure;
plot(wp2);
TITLE('p-vector algorithm, w2p(n) for mu = 0.008, p_vector is changed');