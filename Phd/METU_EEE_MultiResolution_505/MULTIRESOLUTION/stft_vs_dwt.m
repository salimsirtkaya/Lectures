%% EE505 
%% Comparison of Short Time Fourier Transform with Discrete Wavelet Transform 
%% (using Haar and Sinc mother wavelets)

clear all;
close all;

for n=1:100
    s(n)=0.0002*n^2;
end

for n=101:250
    s(n)=-0.5+500/(0.1*n^2);
end

for n=251:400
    s(n)=3+0.5*sin(n*pi*25/180);
end

for n=401:550
    s(n)=2.5;
end

for n=551:750
    s(n)=-1+sin(n*pi*15/180);
end

% figure;
% plot(s);
% TITLE('Original signal s(t)');
% 
% figure;
% [STFT,f_stft,t_stft] = specgram(s,32,1,32);
% 
% imagesc(t_stft,f_stft,20*log10(abs(STFT))), axis xy, colormap(jet);

% F = SCAL2FRQ(s,'haar',1);


scales = [1:1:10];
wname = 'dmey';
level = 5;
figure; 
coefs_haar = cwt(s,scales,wname,'plot', 'absglb'); ax = gca; colorbar;


[C,L] = wavedec(s,level,wname);

A = appcoef(C,L,wname,level);
D = detcoef(C,L,level);

X = idwt(A,D,wname);

figure;
plot(X);
err = norm(X-s)

 