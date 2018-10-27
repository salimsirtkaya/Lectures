%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 3-17  Zero Padding Effects on Periodogram Estimators
close all;
clear all;
L=512;
phi1=0;
phi2=0;
no_real=10;

for n=1:L
    freq1(n)=2*(n-1)/L;
end

% The original spectrum of the sequence
H=zeros(1,L/2);

for k=1:L
    freq(k)=(k-1)/L;
end

H(L/2*0.24)=50*pi;
H(L/2*0.26)=12.5*pi;


% Generation of the sequence
for k=1:10
    phi1=unifrnd(0,2*pi);
    phi2=unifrnd(0,2*pi);
    e=randn(L,1);
    for (n=1:L)
      y(k,n)=10*sin(0.24*pi*n+phi1)+5*sin(0.26*pi*n+phi2)+e(n);
    end
end

for k=1:10
    [a_yw_4(:,k),sig_yw_4(k)]=yulewalker(y(k,:),4);
    [a_yw_12(:,k),sig_yw_12(k)]=yulewalker(y(k,:),32);
    [a_lsar_4(:,k),sig_lsar_4(k)]=lsar(y(k,:),4);
    [a_lsar_12(:,k),sig_lsar_12(k)]=lsar(y(k,:),32);    
    [a_myw1_4(:,k),gamma_myw1_4(:,k)]=mywarma(y(k,:),4,4,4);
    [a_myw1_12(:,k),gamma_myw1_12(:,k)]=mywarma(y(k,:),32,32,32);    
    [a_myw2_4(:,k),gamma_myw2_4(:,k)]=mywarma(y(k,:),4,4,8);  
    [a_myw2_12(:,k),gamma_myw2_12(:,k)]=mywarma(y(k,:),12,12,24);
    [a_lsarma1_4(:,k),b_lsarma1_4(:,k),sig_lsarma1_4(k)]=lsarma(y(k,:),4,4,4); 
    [a_lsarma1_12(:,k),b_lsarma1_12(:,k),sig_lsarma1_12(k)]=lsarma(y(k,:),32,32,32); 
    [a_lsarma2_4(:,k),b_lsarma2_4(:,k),sig_lsarma2_4(k)]=lsarma(y(k,:),4,4,8); 
    [a_lsarma2_12(:,k),b_lsarma2_12(:,k),sig_lsarma2_12(k)]=lsarma(y(k,:),12,12,24); 
end

%Compute the power spectral densities of these estimates

for k=1:10
    % PSD estimate of the yule walker method for order=4
    HH1=freqz(1,a_yw_4(:,k),L,'whole');
    PSD_yw_4(k,1:L)=abs(HH1');
    % PSD estimate of the yule walker method for order=8
    HH2=freqz(1,a_yw_12(:,k),L,'whole');
    PSD_yw_12(k,1:L)=abs(HH2');
    
    %PSD estimate of LS(AR) method for order=4
    HH3=freqz(1,a_lsar_4(:,k),L,'whole');
    PSD_lsar_4(k,1:L)=abs(HH3');
    %PSD estimate of LS(AR) method for order=8
    HH4=freqz(1,a_lsar_12(:,k),L,'whole');
    PSD_lsar_12(k,1:L)=abs(HH4');
    
    %PSD estimate of LS(ARMA) method for order=4
    HH5=freqz(b_lsarma1_4(:,k),a_lsarma1_4(:,k),L,'whole');
    PSD_lsarma1_4(k,1:L)=abs(HH5');
    %PSD estimate of LS(AR) method for order=12
    HH6=freqz(b_lsarma1_12(:,k),a_lsarma1_12(:,k),L,'whole');
    PSD_lsarma1_12(k,1:L)=abs(HH6');
    %PSD estimate of LS(ARMA) method for order=4
    HH7=freqz(b_lsarma2_4(:,k),a_lsarma2_4(:,k),L,'whole');
    PSD_lsarma2_4(k,1:L)=abs(HH7');
    %PSD estimate of LS(AR) method for order=8
    HH8=freqz(a_lsarma2_12(:,k),a_lsarma2_12(:,k),L,'whole');
    PSD_lsarma2_12(k,1:L)=abs(HH8');
    
    
    %PSD estimate of Modified Yule Walker Method with M=n and order=4,4
    PSD_myw1_4(k,1:L)=argamse(gamma_myw1_4(:,k),a_myw1_4(:,k),L)';
    %PSD estimate of Modified Yule Walker Method with M=n and order=8,8
    PSD_myw1_12(k,1:L)=argamse(gamma_myw1_12(:,k),a_myw1_12(:,k),L)';
    %PSD estimate of Modified Yule Walker Method with M=2n and order=4,4
    PSD_myw2_4(k,1:L)=argamse(gamma_myw2_4(:,k),a_myw2_4(:,k),L)';
    %PSD estimate of Modified Yule Walker Method with M=2n and order=8,8
    PSD_myw2_12(k,1:L)=argamse(gamma_myw2_12(:,k),a_myw2_12(:,k),L)';
end

%%Average PSD estimates
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
PSD_yw_4_ave=0;
for k=1:no_real
    PSD_yw_4_ave=(PSD_yw_4_ave+PSD_yw_4(k,:));
end
PSD_yw_4_ave=PSD_yw_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_yw_12_ave=0;
for k=1:no_real
    PSD_yw_12_ave=(PSD_yw_12_ave+PSD_yw_12(k,:));
end
PSD_yw_12_ave=PSD_yw_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsar_4_ave=0;
for k=1:no_real
    PSD_lsar_4_ave=(PSD_lsar_4_ave+PSD_lsar_4(k,:));
end
PSD_lsar_4_ave=PSD_lsar_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsar_12_ave=0;
for k=1:no_real
    PSD_lsar_12_ave=(PSD_lsar_12_ave+PSD_lsar_12(k,:));
end
PSD_lsar_12_ave=PSD_lsar_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma1_4_ave=0;
for k=1:no_real
    PSD_lsarma1_4_ave=(PSD_lsarma1_4_ave+PSD_lsarma1_4(k,:));
end
PSD_lsarma1_4_ave=PSD_lsarma1_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma1_12_ave=0;
for k=1:no_real
    PSD_lsarma1_12_ave=(PSD_lsarma1_12_ave+PSD_lsarma1_12(k,:));
end
PSD_lsarma1_12_ave=PSD_lsarma1_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma2_4_ave=0;
for k=1:no_real
    PSD_lsarma2_4_ave=(PSD_lsarma2_4_ave+PSD_lsarma2_4(k,:));
end
PSD_lsarma2_4_ave=PSD_lsarma2_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma2_12_ave=0;
for k=1:no_real
    PSD_lsarma2_12_ave=(PSD_lsarma2_12_ave+PSD_lsarma2_12(k,:));
end
PSD_lsarma2_12_ave=PSD_lsarma2_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw1_4_ave=0;
for k=1:no_real
    PSD_myw1_4_ave=(PSD_myw1_4_ave+PSD_myw1_4(k,:));
end
PSD_myw1_4_ave=PSD_myw1_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw1_12_ave=0;
for k=1:no_real
    PSD_myw1_12_ave=(PSD_myw1_12_ave+PSD_myw1_12(k,:));
end
PSD_myw1_12_ave=PSD_myw1_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw2_4_ave=0;
for k=1:no_real
    PSD_myw2_4_ave=(PSD_myw2_4_ave+PSD_myw2_4(k,:));
end
PSD_myw2_4_ave=PSD_myw2_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw2_12_ave=0;
for k=1:no_real
    PSD_myw2_12_ave=(PSD_myw2_12_ave+PSD_myw2_12(k,:));
end
PSD_myw2_12_ave=PSD_myw2_12_ave/no_real;

% Plot the PSD estimates of Yule Walker method for order=4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->Yule Walker Estimate of order 4');
XLABEL('x pi');
YLABEL('Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_yw_4_ave(1:L/2)/PSD_yw_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_yw_4(k,1:L/2)/PSD_yw_4(k,1),'k');
end

% Plot the PSD estimates of Yule Walker method for order=8
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->Yule Walker Estimate of order 32');
XLABEL('x pi');
YLABEL('Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_yw_12_ave(1:L/2)/PSD_yw_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_yw_12(k,1:L/2)/PSD_yw_12(k,1),'k');
end

% Plot the PSD estimates of LS(AR) method of order 4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->LS(AR) Estimate of order 4');
XLABEL('x pi');
YLABEL('LS(AR) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsar_4_ave(1:L/2)/PSD_lsar_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsar_4(k,1:L/2)/PSD_lsar_4(k,1),'k');
end
% Plot the PSD estimates of LS(AR) method of order 8
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->LS(AR) Estimate of order 32');
XLABEL('x pi');
YLABEL('LS(AR) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsar_12_ave(1:L/2)/PSD_lsar_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsar_12(k,1:L/2)/PSD_lsar_12(k,1),'k');
end

% Plot the PSD estimates of Modified Yule Walker method for M=n of order=4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->Modified Yule Walker Estimate for order=4,4 and M=n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw1_4_ave(1:L/2)/PSD_myw1_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw1_4(k,1:L/2))/PSD_myw1_4(k,1),'k');
end
% Plot the PSD estimates of Modified Yule Walker method for M=n of order=8,8
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->Modified Yule Walker Estimate for order=32,32 and M=n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw1_12_ave(1:L/2)/PSD_myw1_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw1_12(k,1:L/2))/PSD_myw1_12(k,1),'k');
end

% Plot the PSD estimates of Modified Yule Walker method for M=2n of order =4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->Modified Yule Walker Estimate for order=4,4 and M=2n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw2_4_ave(1:L/2)/PSD_myw2_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw2_4(k,1:L/2))/PSD_myw2_4(k,1),'k');
end
% Plot the PSD estimates of Modified Yule Walker method for M=2n of order =8,8
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->Modified Yule Walker Estimate for order=12,12 and M=2n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw2_12_ave(1:L/2)/PSD_myw2_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw2_12(k,1:L/2))/PSD_myw2_12(k,1),'k');
end

% Plot the PSD estimates of LS(ARMA) method of order=4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->LS(ARMA) Estimate of order=4,4 for K=n');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma1_4_ave(1:L/2)/PSD_lsarma1_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma1_4(k,1:L/2)/PSD_lsarma1_4(k,1),'k');
end
% Plot the PSD estimates of LS(ARMA) method of order=4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->LS(ARMA) Estimate of order=4,4 for K=2n');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma2_4_ave(1:L/2)/PSD_lsarma2_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma2_4(k,1:L/2)/PSD_lsarma2_4(k,1),'k');
end
% Plot the PSD estimates of LS(ARMA) method of order=8,8
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->LS(ARMA) Estimate of order=32,32 for K=n');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma1_12_ave(1:L/2)/PSD_lsarma1_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma1_12(k,1:L/2)/PSD_lsarma1_12(k,1),'k');
end
% Plot the PSD estimates of LS(ARMA) method of order=8,8
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',2.5);
TITLE('Exercise 3-17 Part d -->LS(ARMA) Estimate of order=12,12 for K=2n');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma2_12_ave(1:L/2)/PSD_lsarma2_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma2_12(k,1:L/2)/PSD_lsarma2_12(k,1),'k');
end

%%POLE-ZERO PLOTS

figure;
hold;
for k=1:10
    zplane(1,a_yw_4(:,k)');
end
TITLE('Exercise 3-17 Part d -->Pole-Zero Plot for the YW method n=4');

figure;
hold;
for k=1:10
    zplane(1,a_yw_12(:,k)');
end
TITLE('Exercise 3-17 Part d -->Pole-Zero Plot for the YW method n=12');

figure;
hold;
for k=1:10
    zplane(1,a_lsar_4(:,k)');
end
TITLE('Exercise 3-17 Part d -->Pole-Zero Plot for the LSAR method n=4');

figure;
hold;
for k=1:10
    zplane(1,a_lsar_12(:,k)');
end
TITLE('Exercise 3-17 Part d -->Pole-Zero Plot for the LSAR method n=12');

figure;
hold;
for k=1:10
    zplane(1,a_lsarma1_4(:,k)');
end
TITLE('Exercise 3-17 Part d -->LSARMA method n=4, m=4, K=n');


figure;
hold;
for k=1:10
    zplane(1,a_lsarma2_4(:,k)');
end
TITLE('Exercise 3-17 Part d -->LSARMA method n=4, m=4, K=2n');

figure;
hold;
for k=1:10
    zplane(1,a_lsarma1_12(:,k)');
end
TITLE('Exercise 3-17 Part d -->LSARMA method n=32, m=32, K=n');

figure;
hold;
for k=1:10
    zplane(1,a_lsarma2_12(:,k)');
end
TITLE('Exercise 3-17 Part d -->LSARMA method n=12, m=12, K=2n');

figure;
hold;
for k=1:10
    zplane(1,a_myw1_4(:,k)');
end
TITLE('Exercise 3-17 Part d -->MYWARMA method n=4, m=4, M=n');

figure;
hold;
for k=1:10
    zplane(1,a_myw2_4(:,k)');
end
TITLE('Exercise 3-17 Part d -->MYWARMA method n=4, m=4, M=2n');

figure;
hold;
for k=1:10
    zplane(1,a_myw1_12(:,k)');
end
TITLE('Exercise 3-17 Part d -->MYWARMA method n=32, m=32, M=n');

figure;
hold;
for k=1:10
    zplane(1,a_myw2_12(:,k)');
end
TITLE('Exercise 3-17 Part d -->MYWARMA method n=12, m=12, M=2n');