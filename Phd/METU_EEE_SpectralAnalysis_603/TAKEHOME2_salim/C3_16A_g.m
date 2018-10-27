clear all;
close all;

L=256;
no_sample=256;
no_real=50;

% rearranged H(q) coeeficients for alfa = 0.05
a=[1 -1.3817 1.5632 -0.8843 0.4096];
b=[1 0.3544 0.3508 0.1736 0.2401];
RY=Generate_data(a,b,no_sample,no_real); 

for w=1:L
    H(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L)+b(4)*exp(-i*3*2*pi*w/L)+b(5)*exp(-i*4*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H(w)=H(w)*H(w)';
end

for n=1:L
    freq1(n)=2*(n-1)/L;
end

for K=1:no_real
    PY(K,:)=(abs(fft(RY(K,:))).^2)/no_sample;
end

for n=1:no_sample
    freq3(n)=2*(n-1)/no_sample;
end

PY_ave=0;
for k=1:no_real
    PY_ave=(PY_ave+PY(k,:));
end

PY_ave=PY_ave/no_real;

figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
hold;
plot(freq3(1:no_sample/2),PY_ave(1:no_sample/2)/PY_ave(1),'b','LineWidth',1.5);
TITLE('Average Periodogram Spectral Estimate of 50 realizations');
XLABEL('x pi');
YLABEL('Spectrum Estimate');


BT=bartlett(256);
no_psd=no_sample;

for K=1:no_real
    PY(K,1:no_psd)=(abs(fft((RY(K,:).*BT'),no_psd)).^2)/no_sample;
end

for n=1:no_psd
    freq(n)=2*(n-1)/no_psd;
end

PY_ave=0;
for k=1:no_real
    PY_ave=(PY_ave+PY(k,:));
end

PY_ave=PY_ave/no_real;
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
hold;
plot(freq(1:no_psd/2),PY_ave(1:no_psd/2)/PY_ave(1),'b','LineWidth',1.5);
TITLE('Average Periodogram Spectral Estimate of 50 realizations with Bartlett Window');
XLABEL('x pi');
YLABEL('Spectrum Estimate');
