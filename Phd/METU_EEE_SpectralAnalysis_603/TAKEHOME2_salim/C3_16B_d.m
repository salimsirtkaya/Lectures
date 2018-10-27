%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%% Computer Exercise 3-16 - d %%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
close all;
% Generate 10 realzations of data with length=256
L=256;
no_sample=256;
no_real=10;
a=[1 -1.6408 2.2044 -1.4808 0.8145];
b=[1 1.5857 0.9604];
RY=Generate_data(a,b,no_sample,no_real);

for w=1:L
    H(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H(w)=H(w)*H(w)';
end

for n=1:L
    freq1(n)=2*(n-1)/L;
end

% Estimate the parameters of the LS(ARMA) model for different K 
% (yulewalker,lsar,lsarma,modified yulewalker) for 10 realizations
for k=1:10
    [a_lsarma_1(:,k),b_lsarma_1(:,k),sig_lsarma_1(k)]=lsarma(RY(k,:),4,2,4); 
    [a_lsarma_2(:,k),b_lsarma_2(:,k),sig_lsarma_2(k)]=lsarma(RY(k,:),4,2,8); 
    [a_lsarma_3(:,k),b_lsarma_3(:,k),sig_lsarma_3(k)]=lsarma(RY(k,:),4,2,12); 
    [a_lsarma_4(:,k),b_lsarma_4(:,k),sig_lsarma_4(k)]=lsarma(RY(k,:),4,2,16); 
    
end

%Compute the power spectral densities of these estimates

for k=1:10
    %PSD estimate of LS(ARMA) method for K=4
    HH=freqz(b_lsarma_1(:,k),a_lsarma_1(:,k),L,'whole');
    PSD_lsarma_1(k,1:L)=HH';
    PSD_lsarma_1(k,1:L) = abs(PSD_lsarma_1(k,:)).^2*sig_lsarma_1(k);
    %PSD estimate of LS(AR) method for K=8
    HH=freqz(b_lsarma_2(:,k),a_lsarma_2(:,k),L,'whole');
    PSD_lsarma_2(k,1:L)=HH';
    PSD_lsarma_2(k,1:L) = abs(PSD_lsarma_2(k,1:L)).^2*sig_lsarma_2(k);
    %PSD estimate of LS(ARMA) method for K=12
    HH=freqz(b_lsarma_3(:,k),a_lsarma_3(:,k),L,'whole');
    PSD_lsarma_3(k,1:L)=HH';
    PSD_lsarma_3(k,1:L) = abs(PSD_lsarma_3(k,:)).^2*sig_lsarma_3(k);
    %PSD estimate of LS(AR) method for K=16
    HH=freqz(b_lsarma_4(:,k),a_lsarma_4(:,k),L,'whole');
    PSD_lsarma_4(k,1:L)=HH';
    PSD_lsarma_4(k,1:L) = abs(PSD_lsarma_4(k,1:L)).^2*sig_lsarma_4(k);  
end


%%Average PSD estimates
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
PSD_lsarma_1_ave=0;
for k=1:no_real
    PSD_lsarma_1_ave=(PSD_lsarma_1_ave+PSD_lsarma_1(k,:));
end
PSD_lsarma_1_ave=PSD_lsarma_1_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma_2_ave=0;
for k=1:no_real
    PSD_lsarma_2_ave=(PSD_lsarma_2_ave+PSD_lsarma_2(k,:));
end
PSD_lsarma_2_ave=PSD_lsarma_2_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma_3_ave=0;
for k=1:no_real
    PSD_lsarma_3_ave=(PSD_lsarma_3_ave+PSD_lsarma_3(k,:));
end
PSD_lsarma_3_ave=PSD_lsarma_3_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma_4_ave=0;
for k=1:no_real
    PSD_lsarma_4_ave=(PSD_lsarma_4_ave+PSD_lsarma_4(k,:));
end
PSD_lsarma_4_ave=PSD_lsarma_4_ave/no_real;



% Plot the PSD estimates of LS(ARMA) method for K=4
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order=4,2 for K=4');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma_1_ave(1:L/2)/PSD_lsarma_1_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma_1(k,1:L/2)/PSD_lsarma_1(k,1),'k');
end
% Plot the PSD estimates of LS(ARMA) method of for K=8
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order=4,2 for K=8');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma_2_ave(1:L/2)/PSD_lsarma_2_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma_2(k,1:L/2)/PSD_lsarma_2(k,1),'k');
end

% Plot the PSD estimates of LS(ARMA) method for K=4
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order=4,2 for K=12');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma_3_ave(1:L/2)/PSD_lsarma_3_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma_3(k,1:L/2)/PSD_lsarma_3(k,1),'k');
end
% Plot the PSD estimates of LS(ARMA) method of for K=8
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order=4,2 for K=16');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma_4_ave(1:L/2)/PSD_lsarma_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma_4(k,1:L/2)/PSD_lsarma_4(k,1),'k');
end