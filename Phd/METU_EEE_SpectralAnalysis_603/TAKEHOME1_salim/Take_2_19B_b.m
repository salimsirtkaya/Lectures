%*****************************
% PART b -- Variance analysis 
%*****************************
% 1124346 Salim SIRTKAYA % All Rights reserved:)

clear all;close all;
% Generate the data for N=64; N=256; N= 1024;
%H(q) coeeficients
a(1)=1;a(2)=-1.3817;a(3)=1.5632;a(4)=-0.8843;a(5)=0.4096;
b(1)=1;b(2)=0.3544;b(3)=0.3508;b(4)=0.1736;b(5)=0.2401;

RY_64=Generate_data(a,b,64,50);
RY_256=Generate_data(a,b,256,50);
RY_1024=Generate_data(a,b,1024,50);

% Periodogram spectral estimation for each realization

for K=1:50
    PY_64(K,:)=(abs(fft(RY_64(K,:))).^2)/64;
    PY_256(K,:)=(abs(fft(RY_256(K,:))).^2)/256;
    PY_1024(K,:)=(abs(fft(RY_1024(K,:))).^2)/1024;
end

% Sample mean of the estimates
PY_mean_64=mean(PY_64(:,:));
PY_mean_256=mean(PY_256(:,:));
PY_mean_1024=mean(PY_1024(:,:));

PY_std_64=std(PY_64(:,:));
PY_std_256=std(PY_256(:,:));
PY_std_1024=std(PY_1024(:,:));

% Generation of the frequencies
for n=1:64
    freq64(n)=2*(n-1)/64;
end
for n=1:256
    freq256(n)=2*(n-1)/256;
end
for n=1:1024
    freq1024(n)=2*(n-1)/1024;
end

% plot the sample means
figure;
plot(freq64(1:32),PY_mean_64(1:32),'LineWidth',2);
TITLE('Average Periodogram Spectral Estimate of 50 realizations for N=64', 'color', 'b');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
hold;
plot(freq64(1:32),PY_mean_64(1:32)+PY_std_64(1:32),'r','LineWidth',1);
plot(freq64(1:32),PY_mean_64(1:32)-PY_std_64(1:32),'g','LineWidth',1);
hold off;

figure;
plot(freq256(1:128),PY_mean_256(1:128),'LineWidth',2);
TITLE('Average Periodogram Spectral Estimate of 50 realizations for N=256', 'color', 'b');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
hold;
plot(freq256(1:128),PY_mean_256(1:128)+PY_std_256(1:128),'r','LineWidth',1);
plot(freq256(1:128),PY_mean_256(1:128)-PY_std_256(1:128),'g','LineWidth',1);
hold off;

figure;
plot(freq1024(1:512),PY_mean_1024(1:512),'LineWidth',2);
TITLE('Average Periodogram Spectral Estimate of 50 realizations for N=1024', 'color', 'b');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
hold;
plot(freq1024(1:512),PY_mean_1024(1:512)+PY_std_1024(1:512),'r','LineWidth',1);
plot(freq1024(1:512),PY_mean_1024(1:512)-PY_std_1024(1:512),'g','LineWidth',1);
hold off;


%****************************************
% PART c -- Variance analysis comparison
%****************************************

%H(q) coeficients
a(1)=1;a(2)=-1.3817;a(3)=1.5632;a(4)=-0.8843;a(5)=0.4096;
b(1)=1;b(2)=0.3544;b(3)=0.3508;b(4)=0.1736;b(5)=0.2401;
L=64;
for n=1:L
    freq1(n)=2*(n-1)/L;
end

for w=1:L
    H64(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L)+b(4)*exp(-i*3*2*pi*w/L)+b(5)*exp(-i*4*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H64(w)=H64(w)*H64(w)';
end

VAR_H64=H64.^2;

figure;
plot(freq1(1:L/2),VAR_H64(1:L/2),'k');
TITLE('Variance for N=64');


figure;
plot(freq1(1:L/2),PY_std_64(1:L/2)./H64(1:L/2),'k');
TITLE('std(estimate(PHI))/PHI for N=64');

%for  Number of samples=1024
L=256;
for n=1:L
    freq1(n)=2*(n-1)/L;
end

for w=1:L
    H256(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L)+b(4)*exp(-i*3*2*pi*w/L)+b(5)*exp(-i*4*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H256(w)=H256(w)*H256(w)';
end

VAR_H256=H256.^2;

figure;
plot(freq1(1:L/2),VAR_H256(1:L/2),'k');
TITLE('Variance for N=256');


figure;
plot(freq1(1:L/2),PY_std_256(1:L/2)./H256(1:L/2),'k');
TITLE('std(estimate(PHI))/PHI for N=256');

%for  Number of samples=1024
L=1024;
for n=1:L
    freq1(n)=2*(n-1)/L;
end

for w=1:L
    H1024(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L)+b(4)*exp(-i*3*2*pi*w/L)+b(5)*exp(-i*4*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H1024(w)=H1024(w)*H1024(w)';
end

VAR_H1024=H1024.^2;

figure;
plot(freq1(1:L/2),VAR_H1024(1:L/2),'k');
TITLE('Variance for N=1024');


figure;
plot(freq1(1:L/2),PY_std_1024(1:L/2)./H1024(1:L/2),'k');
TITLE('std(estimate(PHI))/PHI for N=1024');
