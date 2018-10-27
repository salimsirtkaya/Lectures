%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 2-19  Bias and Variance Properties of the 
% Periodogram Spectral Estimator
% 1124346 Salim SIRTKAYA % All Rights reserved:)

%************************************************************************
%************************************************************************
%******************* PART B--  VARIANCE PROPERTIES   ********************
%************************************************************************
%************************************************************************

%*************************
% PART a -- True Spectrum 
%*************************

clear all;
close all;

L=4096;

%H(q) coeficients
a(1)=1;a(2)=-1.3817;a(3)=1.5632;a(4)=-0.8843;a(5)=0.4096;
b(1)=1;b(2)=0.3544;b(3)=0.3508;b(4)=0.1736;b(5)=0.2401;

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
TITLE('Exercise 2-19 PART B --> The true spectrum phi(w)');
XLABEL('x pi');
YLABEL('True Spectrum');
