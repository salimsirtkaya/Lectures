%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%
% 1124346 Salim SIRTKAYA % All Rights reserved:)

% TakeHome Exam 
% Problem 2-20  Refined Methods: Variance-Resolution Tradeoff 
% We'll apply BlackmanTukey and Welch estimators for a narrowband 
% and broadband ARMA processes

%************************************************************************
%************************************************************************
%***************** PART B--  Narrowband ARMA Proces   ********************
%************************************************************************
%************************************************************************

%*************************
% PART a -- True Spectrum 
%*************************
clear all;
close all;

% Generate the data for N=256 
%H(q) coeficients
a(1)=1;a(2)=-1.6408;a(3)=2.2044;a(4)=-1.4808;a(5)=0.8145;
b(1)=1;b(2)=1.5857;b(3)=0.9604;b(4)=0;b(5)=0;

L=4096; % number of PSD samples

% The true spectrum of the sequence
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
TITLE('Exercise 2-20 PART B -->The true spectrum');
XLABEL('x pi');
YLABEL('True Spectrum');

L=256;
% Generate 50 data realizations
RY=Generate_data(a,b,L,50);

% PSD estimate using Blackman Tukey method and the Bartlett window
MM=1024;
M1=256/4;
w=Bartlett(M1);

for k=1:50
    PY_bt1(k,:)=(btse(RY(k,:),w,MM))';    
end

M2=256/16;
w=Bartlett(M2);

for k=1:50
    PY_bt2(k,:)=(btse(RY(k,:),w,MM))';    
end

for n=1:MM
    freq(n)=2*(n-1)/MM;
end

PY_mean_bt1=mean(PY_bt1(:,:));
PY_mean_bt2=mean(PY_bt2(:,:));
PY_std_bt1=std(PY_bt1(:,:));
PY_std_bt2=std(PY_bt2(:,:));

figure;
plot(freq(1:MM/2),PY_mean_bt1(1:MM/2),'LineWidth',2);
TITLE('Mean BT Spectral Estimate for M=64', 'color', 'b');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
hold;
plot(freq(1:MM/2),PY_mean_bt1(1:MM/2)+PY_std_bt1(1:MM/2),'r','LineWidth',1);
plot(freq(1:MM/2),PY_mean_bt1(1:MM/2)-PY_std_bt1(1:MM/2),'g','LineWidth',1);
hold off;

figure;
plot(freq(1:MM/2),PY_mean_bt2(1:MM/2),'LineWidth',2);
TITLE('Mean BT Spectral Estimate for M=16', 'color', 'b');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
hold;
plot(freq(1:MM/2),PY_mean_bt2(1:MM/2)+PY_std_bt1(1:MM/2),'r','LineWidth',1);
plot(freq(1:MM/2),PY_mean_bt2(1:MM/2)-PY_std_bt1(1:MM/2),'g','LineWidth',1);
hold off;

% PSD estimate using Welch method and the rectangular window

w=rectwin(M1);

for k=1:50
    PY_welch1(k,:)=welchse(RY(k,:),w,M1/2,MM)';    
end

w=rectwin(M2);

for k=1:50
    PY_welch2(k,:)=welchse(RY(k,:),w,M2/2,MM)';    
end

PY_mean_welch1=mean(PY_welch1(:,:));
PY_mean_welch2=mean(PY_welch2(:,:));
PY_std_welch1=std(PY_welch1(:,:));
PY_std_welch2=std(PY_welch2(:,:));


figure;
plot(freq(1:MM/2),PY_mean_welch1(1:MM/2),'LineWidth',2);
TITLE('Mean Welch Spectral Estimate for M=64', 'color', 'b');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
hold;
plot(freq(1:MM/2),PY_mean_welch1(1:MM/2)+PY_std_welch1(1:MM/2),'r','LineWidth',1);
plot(freq(1:MM/2),PY_mean_welch1(1:MM/2)-PY_std_welch1(1:MM/2),'g','LineWidth',1);
hold off;

figure;
plot(freq(1:MM/2),PY_mean_welch2(1:MM/2),'LineWidth',2);
TITLE('Mean Welch Spectral Estimate for M=16', 'color', 'b');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
hold;
plot(freq(1:MM/2),PY_mean_welch2(1:MM/2)+PY_std_welch1(1:MM/2),'r','LineWidth',1);
plot(freq(1:MM/2),PY_mean_welch2(1:MM/2)-PY_std_welch1(1:MM/2),'g','LineWidth',1);
hold off;
