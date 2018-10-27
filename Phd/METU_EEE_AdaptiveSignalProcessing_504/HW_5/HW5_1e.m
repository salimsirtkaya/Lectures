%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #5, P.1-e   %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all;
close all;

N = 200; % number of samples

% unit variance white gaussian noise
v = randn(N,1);

% generation of x(n)
b=1;
a1=[1 -1.2728 0.81];
a2=[1 0 0.81];

%desired signal
x(1:50) = filter(b,a1,v(1:50));
x(51:100)=filter(b,a2,v(51:100));
x(101:200)=filter(b,a1,v(101:200));

% Apply LMS
[W_lms,E] = llms(x,x,0.008,2);

figure;
plot(W_lms(:,1));
TITLE('LMS result - w1');
figure; 
plot(W_lms(:,2))
TITLE('LMS result - w2 ');

% Apply growing window RLS
[W_gwRLS, alpha] = rls(x,x,2,1);

figure;
plot(W_gwRLS(:,1));
TITLE('Growing Window RLS - w1');
figure; 
plot(W_gwRLS(:,2))
TITLE('Growing Window RLS - w2 ');

% Apply weighted RLS
[W_wRLS, alpha] = rls(x,x,2,0.95);
figure;
plot(W_wRLS(:,1));
TITLE('Weighted RLS - w1 for lambda = 0.95');
figure; 
plot(W_wRLS(:,2))
TITLE('Weighted RLS - w2 for lambda = 0.95');

% Apply sliding window RLS
[W_swRLS, alpha] = rls_sliding(x,x,2,25,1);

figure;
plot(W_swRLS(:,1));
TITLE('Sliding Window RLS - w1');
figure; 
plot(W_swRLS(:,2))
TITLE('Sliding Window RLS - w2 ');