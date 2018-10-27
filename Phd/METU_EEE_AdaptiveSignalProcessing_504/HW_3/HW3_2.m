%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #3, P.2   %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N = 200; % number of samples
A = 4; %amplitude of the sinusoid
phi = pi/4; %phase of the sinusoid

%generate the reference powerline interference
for n=1:N
    r(n)=A*cos(pi/10*n + phi);
end

% figure;
% plot(r);
% TITLE('Powerline Interference');

%generate the observations
for n=1:N
    x(n)=cos(pi/10*n);
end

w1 = A*(cos(phi)+sin(phi)/(sin(pi/10)));
w1 = w1*ones(1,N);
w2 = -1*A*sin(phi)/sin(pi/10);
w2 = w2*ones(1,N);
 
init2=[0 0];
init3 = [9 -7 0];

[W,E]= llms(x,r,1,3,init3);

figure;
plot(w1,'r');hold;
plot(w2,'m');
plot(W);
TITLE('The learning curve for u=1, third order filter');

figure;
semilogy(E.^2);
TITLE('The error for u=1, third order filter');

