%*********************************************
%*********************************************
% PART c -- Periodogram Spectral Estimates
%*********************************************
%*********************************************
% 1124346 Salim SIRTKAYA % All Rights reserved:)

% Generate the data

clear all;
close all;
no_real=50;
no_sample=64;

% rearranged H(q) coeeficients for alfa=0.05
a(1)=1;a(2)=1.775668;a(3)=2.672284;a(4)=1.740332;a(5)=0.960596;
b(1)=4;b(2)=7.030929;b(3)=10.473195;b(4)=6.750381;b(5)=3.687136;


RY=Generate_data(a,b,no_sample,no_real);

% Periodogram spectral estimation for each realization

for K=1:no_real
    PY(K,:)=(abs(fft(RY(K,:))).^2)/no_sample;
end

for n=1:no_sample
    freq3(n)=2*(n-1)/no_sample;
end

figure;

plot(freq3(1:no_sample/2),PY(1,1:no_sample/2),'k');
hold
for t=1:9
    plot(freq3(1:no_sample/2),PY(5*t,1:no_sample/2),'k');
end

TITLE('Periodogram Spectral Estimates of 10 realizations');
XLABEL('x pi');
YLABEL('Spectrum Estimate');

PY_ave=0;
for k=1:no_real
    PY_ave=(PY_ave+PY(k,:));
end

PY_ave=PY_ave/no_real;
figure;
plot(freq3(1:no_sample/2),PY_ave(1:no_sample/2),'k');
TITLE('Average Periodogram Spectral Estimate of 50 realizations');
XLABEL('x pi');
YLABEL('Spectrum Estimate');










