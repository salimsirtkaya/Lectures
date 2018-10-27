%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 3-17  Zero Padding Effects on Periodogram Estimators
close all;
clear all;
L=512;
phi1=0;
phi2=0;

for n=1:L
    freq1(n)=2*(n-1)/L;
end

% Generation of the sequence
for k=1:10
    phi1=unifrnd(0,2*pi);
    phi2=unifrnd(0,2*pi);
    e=randn(L,1);
    for (n=1:L)
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

figure;
plot(freq1(1:L/2),PSD_orig/PSD_orig(1),'k');
TITLE('The original PSD of the sequence for positive freq');
XLABEL('x pi');
YLABEL('True PSD');


%%Computation of true AR polynomial from true autocorrelation sequence

%%True autocorrelation sequence calculation
for k=1:L
%     r_true(k)=-25*exp(-i*0.24*pi*k)+25*exp(i*0.24*pi*k)-6.25*exp(-i*0.26*pi*k)+6.25*exp(-i*0.26*pi*k)+1;

r_true(k)=50*cos(0.24*pi*(k-1))+12.5*cos(0.26*pi*(k-1));
end

r_true(1)=r_true(1)+1;

%AR(4)
n=4;
% form the Toeplitz covariance matrix
Rn_ar4=toeplitz(conj(r_true(1:n)));
% compute the AR coffecients
a_ar4=-(inv(Rn_ar4))*r_true(2:n+1)';
a_ar4=[1;a_ar4];

%AR(12)
n=12;
% form the Toeplitz covariance matrix
Rn_ar12=toeplitz(conj(r_true(1:n)));
% compute the AR coffecients
a_ar12=-(inv(Rn_ar12))*r_true(2:n+1)';
a_ar12=[1;a_ar12];

HH=freqz(1,a_ar4,L,'whole');
PSD_ar_4=abs(HH');

HH2=freqz(1,a_ar12,L,'whole');
PSD_ar_12=abs(HH2');

figure;
plot(freq1(1:L/2),PSD_orig,'r');
TITLE('Exercise 3-17 PART B -->AR Estimate of order 4');
YLABEL('AR Estimate');
hold;

plot(freq1(1:L/2),PSD_ar_4(1:L/2),'k');

figure;
plot(freq1(1:L/2),PSD_orig,'r');
TITLE('Exercise 3-16 PART B -->AR Estimate of order 12');
YLABEL('AR Estimate');
hold;
plot(freq1(1:L/2),PSD_ar_12(1:L/2),'k');

%ARMA(4,4)

%myw_arma for M=8
% form the r vector and R matrix in equation (3.7.1)
m=4;
n=4;
M=4;
r1=r_true(m+2:m+M+1);
if ((m-n+1)>=0)
   R1=toeplitz(r_true(m+1:m+M),r_true(m+1:-1:m-n+2).');
else
   R1=toeplitz(r_true(m+1:m+M),[r_true(m+1:-1:1);conj(r_true(2:abs(m-n+1)+1))].');
end

% compute the AR coffecients

a_mywar_4=-(inv(conj(R1')*R1))*(conj(R1')*r1'); 
a_mywar_4=[1;a_mywar_4];

HH3=freqz(1,a_mywar_4,L,'whole');
PSD_mywar_4=abs(HH3');

figure;
plot(freq1(1:L/2),PSD_mywar_4(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->MYW Estimate of order (4,4) for M=4');
YLABEL('AR Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r');


%myw_arma for M=8
% form the r vector and R matrix in equation (3.7.1)
m=4;
n=4;
M=8;
r2=r_true(m+2:m+M+1);
if ((m-n+1)>=0)
   R2=toeplitz(r_true(m+1:m+M),r_true(m+1:-1:m-n+2).');
else
   R2=toeplitz(r_true(m+1:m+M),[r_true(m+1:-1:1);conj(r_true(2:abs(m-n+1)+1))].');
end

% compute the AR coffecients

a_mywar2_4=-(inv(conj(R2')*R2))*(conj(R2')*r2'); 
a_mywar2_4=[1;a_mywar2_4];

HH4=freqz(1,a_mywar2_4,L,'whole');
PSD_mywar2_4=abs(HH4');

figure;
plot(freq1(1:L/2),PSD_mywar2_4(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->MYW Estimate of order (4,4) for M=8');
YLABEL('AR Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r');

%LSARMA for K=4 and K=8
[a_lsarma_4,b_lsarma_4,sig_lsarma_4]=lsarma(y(1,:),4,4,4);
[a_lsarma2_4,b_lsarma2_4,sig_lsarma2_4]=lsarma(y(1,:),4,4,8);

    %PSD estimate of LS(ARMA) method for order=4
    HH5=freqz(1,a_lsarma_4,L,'whole');
    PSD_lsarma_4=abs(HH5');
    %PSD estimate of LS(AR) method for order=8
    HH6=freqz(1,a_lsarma2_4,L,'whole');
    PSD_lsarma2_4=abs(HH6');
figure;
plot(freq1(1:L/2),PSD_lsarma_4(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order (4,4) for K=4');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r'); 

figure;
plot(freq1(1:L/2),PSD_lsarma2_4(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order (4,4) for K=8');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r');   

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%ARMA(12,12)

% form the r vector and R matrix in equation (3.7.1)
m=12;
n=12;
M=12;
r3=r_true(m+2:m+M+1);
if ((m-n+1)>=0)
   R3=toeplitz(r_true(m+1:m+M),r_true(m+1:-1:m-n+2).');
else
   R3=toeplitz(r_true(m+1:m+M),[r_true(m+1:-1:1);conj(r_true(2:abs(m-n+1)+1))].');
end

% compute the AR coffecients

a_mywar_12=-(inv(conj(R3')*R3))*(conj(R3')*r3'); 
a_mywar_12=[1;a_mywar_12];

HH8=freqz(1,a_mywar_12,L,'whole');
PSD_mywar_12=abs(HH8');

figure;
plot(freq1(1:L/2),PSD_mywar_12(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->MYW Estimate of order (12,12) for M=12');
YLABEL('AR Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r');


%myw_arma for M=16
% form the r vector and R matrix in equation (3.7.1)
m=12;
n=12;
M=24;
r4=r_true(m+2:m+M+1);
if ((m-n+1)>=0)
   R4=toeplitz(r_true(m+1:m+M),r_true(m+1:-1:m-n+2).');
else
   R4=toeplitz(r_true(m+1:m+M),[r_true(m+1:-1:1);conj(r_true(2:abs(m-n+1)+1))].');
end

% compute the AR coffecients

a_mywar2_12=-(inv(conj(R4')*R4))*(conj(R4')*r4'); 
a_mywar2_12=[1;a_mywar2_12];

HH9=freqz(1,a_mywar2_12,L,'whole');
PSD_mywar2_12=abs(HH9');

figure;
plot(freq1(1:L/2),PSD_mywar2_12(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->MYW Estimate of order (12,12) for M=24');
YLABEL('AR Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r');

%LSARMA for K=4 and K=8
[a_lsarma_12,b_lsarma_12,sig_lsarma_12]=lsarma(y(1,:),12,12,12);
[a_lsarma2_12,b_lsarma2_12,sig_lsarma2_12]=lsarma(y(1,:),12,12,24);

    %PSD estimate of LS(ARMA) method for order=4
    HH10=freqz(1,a_lsarma_12,L,'whole');
    PSD_lsarma_12=abs(HH10');
    %PSD estimate of LS(AR) method for order=8
    HH11=freqz(1,a_lsarma2_12,L,'whole');
    PSD_lsarma2_12=abs(HH11');
figure;
plot(freq1(1:L/2),PSD_lsarma_12(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order (12,12) for K=12');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r'); 

figure;
plot(freq1(1:L/2),PSD_lsarma2_12(1:L/2),'k');
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order (12,12) for K=24');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_orig,'r'); 

%%%ROOT calculations

tt1=1/pi*angle(roots(a_ar4));
tt2=1/pi*angle(roots(a_ar12));
tt3=1/pi*angle(roots(a_lsarma_4));
tt4=1/pi*angle(roots(a_lsarma2_4));
tt5=1/pi*angle(roots(a_lsarma_12));
tt6=1/pi*angle(roots(a_lsarma2_12));
tt7=1/pi*angle(roots(a_mywar_4));
tt8=1/pi*angle(roots(a_mywar2_4));
tt9=1/pi*angle(roots(a_mywar_12));
tt10=1/pi*angle(roots(a_mywar2_12));







