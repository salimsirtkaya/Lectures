%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 2-17  Zero Padding Effects on Periodogram Estimators
close all;
clear all;
N=64;
phi1=0;
phi2=0;

% White Gaussian Noise with variance 1
e=randn(N,1);

% Generation of the sequence
for (n=1:N)
  y(n)=10*sin(0.2*2*pi*n+phi1)+5*sin((0.2+1/N)*2*pi*n)+e(n);
end

figure;
plot(y,'k');
TITLE('The sequence under concern for N=64');

% The original spectrum of the sequence
PSD_orig=ones(1,640);

for i=1:640
    freq(i)=(i-1)/640;
end

PSD_orig(640*0.4)=50*pi;
PSD_orig(640*(0.4+2/N))=12.5*pi;

figure;
plot(freq,PSD_orig,'k');
TITLE('The original PSD of the sequence for positive freq');
XLABEL('x pi');
YLABEL('True PSD');

periodogram_salim(y,N,0);
periodogram_salim(y,N,1);
periodogram_salim(y,N,3);
periodogram_salim(y,N,5);
periodogram_salim(y,N,7);