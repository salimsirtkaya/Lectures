%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 4-9  Zero Padding Effects on Periodogram Estimators
close all;
clear all;
L=1024;
N=64
phi1=0;
phi2=0;

for n=1:L
    freq1(n)=2*(n-1)/L;
end

% Generation of the sequence
for k=1:50
    phi1=unifrnd(-pi,pi);
    phi2=unifrnd(-pi,pi);
    e=randn(N,1);
    for (n=1:N)
      y(k,n)=10*sin(0.24*pi*n+phi1)+5*sin((0.26*pi*n+phi2))+e(n);
    end
end

% The original spectrum of the sequence
PSD_orig=ones(1,L/2);

for k=1:L
    freq(k)=(k-1)/L;
end

PSD_orig(L/2*0.24)=50*pi;
PSD_orig(L/2*0.26)=12.5*pi;

% figure;
% plot(freq1(1:L/2),PSD_orig/PSD_orig(1),'k');
% TITLE('The original PSD of the sequence for positive freq');
% XLABEL('x pi');
% YLABEL('True PSD');

% True ACS
for k=1:L
    r_true(k)=50*cos(0.24*pi*(k-1))+12.5*cos(0.26*pi*(k-1));
end

r_true(1)=r_true(1)+1;

% estimation of the frequencies with music method
w_music_true=music_true(r_true,4,5)/pi

% estimation of the frequencies with minnorm method
w_minnorm_true=minnorm_true(r_true,4,5)/pi

% estimation of the frequencies with esprit method
w_esprit_true=esprit_true(r_true,4,5)/pi

% estimation of the frequencies with esprit method
w_hoyw_true=hoyw_true(r_true,4,12,12)/pi
