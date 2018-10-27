function periodogram_salim(y,N,Z)
% Implementation of the periodogram estimator
% y --> The sequence under concern
% N --> Number of samples taken from the sequence
% Z --> Number of zero paddings=ZxN
 

V=N+N*Z; % number of FFT points after zero padding

PSD_period=(abs(fft(y,V)).^2)/64;

for i=1:V
    freq1(i)=2*(i-1)/V;
end

figure;
plot(freq1(1:V/2),PSD_period(1:V/2),'k');
TITLE(['The periodogram estimate for the sequence with # of zero paddings = Nx', int2str(Z)]);
XLABEL('x pi');
YLABEL('PSD Estimate');

