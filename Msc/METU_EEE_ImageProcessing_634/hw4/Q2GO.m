% EE634 Homework #4	%
%  Gökhan ÖZZAMAN   	%  
%     130530-9     	%
%%%%%%%%%%%%%%%%%%%%%%
% Q2
close all;
clear all;
[im,map] = imread('nb_otopark.bmp');
figure;
imshow(im,map);
title('Original Noisy and Blurred Image');

[r c] = size(im);
Auto_corr = ifft2(((fft2(im)).^2) / (r*c));

%Hamming Window
Window_Ham=zeros(1,256);
for i=-20:20
   Window_Ham(1,i+128)=0.54+0.46*cos(pi*i/20);
end
Hamming_w = Window_Ham'*Window_Ham;
Observed_Spectrum = fft2(Auto_corr.*Hamming_w);

%Deblur Transfer Function

blur_func(1:11) = 1/11;
deblur = 1./fft(blur_func,256);%Inverse of the Blur Function
deblur(abs(deblur) > 10) = 0;
Deblur_tr_func = ones(256,1)*deblur;

%Wiener Filter
Noise_PSD = 225;
Wiener_F = Observed_Spectrum./(Observed_Spectrum + Noise_PSD);
I = fft2(im);
Noiseless = I.*Wiener_F;
n = ifft2(Noiseless);
n_abs = abs(n);
figure;
imshow(n_abs,map);title('Noise reduced by Wiener Filtering');
result= Noiseless.*Deblur_tr_func;
result= abs(ifft2(result));
figure;
imshow(result,map);
title('Blur removed after noise cancellation');
%Comments
%BLackman-Tukey estimator is implemented in this part, but the results are not satisfactory
%since image mean is not taken into account and no local calculation over the image 
%boundary is done, this not an adaptive process. Size of the window affects the results
%in a way that smaller the size results in better smoothing but trade off is decresing
%resolution.