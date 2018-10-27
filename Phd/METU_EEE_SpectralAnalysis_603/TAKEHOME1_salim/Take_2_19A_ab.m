%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 2-19  Bias and Variance Properties of the 
% Periodogram Spectral Estimator
% 1124346 Salim SIRTKAYA % All Rights reserved:)

%************************************************************************
%************************************************************************
%********** PART A--  BIAS PROPERTIES -- RESOLUTION AND LEAKAGE   *******
%************************************************************************
%************************************************************************

%*********************************************
% PART a -- True Spectrum & ACS using IFFT
%*********************************************


% H(q) = (1-0.95*exp(0.3*2*pi*i)*q^-1)/(1-0.99*exp(0.3*2*pi*i)*q^-1) + (1-0.95*exp(-0.3*2*pi*i)*q^-1)/(1-0.99*exp(-0.3*2*pi*i)*q^-1) 
%       +(1-0.95*exp(0.305*2*pi*i)*q^-1)/(1-0.99*exp(0.305*2*pi*i)*q^-1) + (1-0.95*exp(-0.305*2*pi*i)*q^-1)/(1-0.99*exp(-0.305*2*pi*i)*q^-1) 

% y(t)=H(q)*e(t) => y(t)=(B(q)/A(q))*e(t)

% a(1)=1;a(2)=1.775668;a(3)=2.672284;a(4)=1.740332;a(5)=0.960596;
% b(1)=4;b(2)=7.030929;b(3)=10.473195;b(4)=6.750381;b(5)=3.687136;

% H(w)=B(w)/A(w)= (b(1)+b(2)*exp(-i*w)+b(3)*exp(-i*2*w)+b(4)*exp(-i*3*w)+b(5)*exp(-i*4*w))/...
%                 (a(1)+a(2)*exp(-i*w)+a(3)*exp(-i*2*w)+a(4)*exp(-i*3*w)+a(5)*exp(-i*4*w))


% We can sample this true psd in [-pi pi] interval using a suuficiently fine grid for illustration purposes

% Lets use 2048 samples for this purpose: 
% L= number of psd samples
% spectral estimates at L frequencies w=0, 2*pi/L, ..., 2*pi(L-1)/L

clear all;
close all;

L=64;

% rearranged H(q) coeeficients for alfa = 0.05
a(1)=1;a(2)=1.775668;a(3)=2.672284;a(4)=1.740332;a(5)=0.960596;
b(1)=4;b(2)=7.030929;b(3)=10.473195;b(4)=6.750381;b(5)=3.687136;

for n=1:L
    freq1(n)=2*(n-1)/L;
end

for w=1:L
    H(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L)+b(4)*exp(-i*3*2*pi*w/L)+b(5)*exp(-i*4*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H(w)=H(w)*H(w)';
end
 

figure;
plot(freq1(1:L/2),H(1:L/2),'k');
TITLE('Exercise 2-19 PART A -->The true spectrum');
XLABEL('x pi');
YLABEL('True Spectrum');

ACS=real(ifft(H));

figure;
plot(ACS,'k');
TITLE('The ACS estimated by ifft');

%*********************************************
%*********************************************
% PART b -- Bartlett Window realization
%*********************************************
%*********************************************

N=64;

% generation of the bartlett window

BT=bartlett(N);

% Fourier transform of the Bartlett window

F_BT=abs(fft(BT,L));
figure;
plot(freq1(1:L/2),F_BT(1:L/2),'k');
TITLE('Fourier Transform of Bartlett Window of size 64');
XLABEL('x pi');

% Expected value of the periodogram estimator

PHI_e=CONV(H,F_BT)/L*2;

PHI_est=abs(PHI_e(1:L));

figure;
plot(freq1(1:L/2),PHI_est(1:L/2),'k');
TITLE('The periodogram estimate with Bartlett');
XLABEL('x pi');
YLABEL('Spectrum Estimate');


