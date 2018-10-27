%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 4-9  Resolution Properties of Subspace Methods for Estimation of Line Spectra
close all;
clear all;
L=1024;
N=64
phi1=0;
phi2=0;

for n=1:L
    freq1(n)=2*(n-1)/L;
end

% Generation of the sequence with infinite SNR
for k=1:50
    phi1=unifrnd(-pi,pi);
    phi2=unifrnd(-pi,pi);
 %   e=randn(N,1);
    for (n=1:N)
      y(k,n)=10*sin(0.24*pi*(n-1)+phi1)+5*sin((0.26*pi*(n-1)+phi2));
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

for k=1:50
    % estimation of the frequencies with music method
    w_music(:,k)=music(y(k,:),4,12);
    
    % estimation of the frequencies with minnorm method
    w_minnorm(:,k)=minnorm(y(k,:),4,12);
    
    % estimation of the frequencies with esprit method
    w_esprit(:,k)=esprit(y(k,:),4,12);
    
    % estimation of the frequencies with esprit method
    w_hoyw(:,k)=hoyw(y(k,:),4,4,4);
end

w_music_mean=mean(w_music')/pi
w_music_var=var(w_music')/pi

w_minnorm_mean=mean(w_minnorm')/pi
w_minnorm_var=var(w_minnorm')/pi

w_esprit_mean=mean(w_esprit')/pi
w_esprit_var=var(w_esprit')/pi

w_hoyw_mean=mean(w_hoyw')/pi
w_hoyw_var=var(w_hoyw')/pi
