%****************************************************************
%****************************************************************
% PART d -- Periodogram Spectral Estimates with Bartlett Window
%****************************************************************
%****************************************************************

% 1124346 Salim SIRTKAYA % All Rights reserved:)

clear all;
close all;
% Generate the data
no_real=50;
no_sample=256;
alfa=0.008;


z1=0.95*exp(i*2*pi*0.3);
z2=0.95*exp(i*2*pi*(0.3+alfa));
p1=0.99*exp(i*2*pi*0.3);
p2=0.99*exp(i*2*pi*(0.3+alfa));

% Generation of the filter coefficients
a(1)=1;
a(2)=-(p1+p1'+p2+p2');
a(3)=(p2*p2'+(p1+p1')*(p2+p2')+p1*p1');64*16

a(4)=-((p1+p1')*p2*p2'+(p2+p2')*p1*p1');
a(5)=(p1*p1'*p2*p2');

b(1)=4;
b(2)=-(z1+z1'+z2+z2'+3*p1+3*p1'+3*p2+3*p2');
b(3)=(p2*p2'+(z1+p1')*(p2+p2')+z1*p1'+p2*p2'+(z1'+p1)*(p2+p2')+z1'*p1...
    +p1'*p2'+(z2+p1)*(p1'+p2')+z2*p1+p1'*p2+(z2'+p1)*(p1'+p2)+z2'*p1);

b(4)=-((z1+p1')*p2*p2'+(p2+p2')*z1*p1'+(z1'+p1)*p2*p2'+(p2+p2')*z1'*p1...
    +(z2+p1)*p1'*p2'+(p1'+p2')*z2*p1+(z2'+p1)*p1'*p2+(p1'+p2)*z2'*p1);

b(5)=(z1*p1'*p2*p2'+z1'*p1*p2*p2'+z2*p1*p1'*p2'+z2'*p1*p1'*p2);

b=real(b);

no_psd=no_sample*8;

% Generate the data
RY=Generate_data(a,b,no_sample,no_real);

% Generate the bartlett window

BT=bartlett(256);

% The true spectrum
L=no_psd;
for w=1:L
    H_true(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L)+b(4)*exp(-i*3*2*pi*w/L)+b(5)*exp(-i*4*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H_true(w)=H_true(w)*H_true(w)';
end


% Estimate the PSD using windowed periodogram

for K=1:no_real
    PY(K,1:no_psd)=(abs(fft((RY(K,:).*BT'),no_psd)).^2)/no_sample;
end

for n=1:no_psd
    freq(n)=2*(n-1)/no_psd;
end
figure;
plot(freq(1:no_psd/2),H_true(1:no_psd/2),'k');
TITLE('True spectrum with 256 points');
XLABEL('x pi');
YLABEL('True Spectrum');

figure;
plot(freq(1:no_psd/2),PY(1,1:no_psd/2),'k');
hold
for t=1:9
    plot(freq(1:no_psd/2),PY(5*t,1:no_psd/2),'k');
end

TITLE('Periodogram Spectral Estimates of 10 realizations');
XLABEL('x pi');
YLABEL('Spectrum Estimate');

PY_ave=0;
for k=1:no_real
    PY_ave=(PY_ave+PY(k,:));
end

PY_ave=PY_ave/no_real;
figure;
plot(freq(1:no_psd/2),PY_ave(1:no_psd/2),'k');
TITLE('Average Periodogram Spectral Estimate of 50 realizations');
XLABEL('x pi');
YLABEL('Spectrum Estimate');











