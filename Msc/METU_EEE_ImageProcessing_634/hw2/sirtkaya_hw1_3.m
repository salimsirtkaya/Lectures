% Howework2 - Question 3        Salim SIRTKAYA 1124346

clear all
close all

%3.a Low-pass filtering of Lena and testpattern images
Lena=imread('Lena.bmp');
testp=imread('testpattern.tif');

FFT_Lena=fft2(Lena);
FFT_Lena=fftshift(FFT_Lena);  %Shift zero-frequency component of fast Fourier transform to center of spectrum


FFT_testp=fft2(testp);
FFT_testp=fftshift(FFT_testp); %Shift zero-frequency component of fast Fourier transform to center of spectrum

LPF=[zeros(96,256); zeros(64,96) ones(64,64) zeros(64,96);zeros(96,256)]; 

Filt_Lena=FFT_Lena.*LPF;
LPF_Lena=ifft2(Filt_Lena);
figure(1);
imshow(uint8(real(LPF_Lena)));
title('HW2-3a  Low-pass filtered Lena image');

Filt_testp=FFT_testp.*LPF;
LPF_testp=ifft2(Filt_testp);
figure(2);
imshow(uint8(real(LPF_testp)));
title('HW2-3a  Low-pass filtered testpattern image');

% The filter designed is a Low-pass filter so it eliminates the 
% high frequency components. For example, the center part of the 
% testpattern image contains high frequency components thus the result of 
% low-pass filtering is blurring of the center part. Similarly, in Lena image 
% the edges are smoothed and the image is blurred.


%3.b Non-zero phase filtering of Lena and testpattern images
w=0:255;
w=repmat(w,256,1); %construction of w1+w2 matrix
w=2*pi*(w+w')/256; 
LPF_d=ifftshift(LPF); %swap the corner quarters of filter
LPF2=LPF_d.*exp(j*2*pi*sin(2*w));

Filt_Lena2=fft2(Lena).*LPF2;
LPF2_Lena=ifft2(Filt_Lena2);
figure(3);
imshow(uint8(real(LPF2_Lena)));
title('HW2-3b  Non-zero phase filtered Lena image');

Filt_testp2=fft2(testp).*LPF2;
LPF2_testp=ifft2(Filt_testp2);
figure(4);
imshow(uint8(real(LPF2_testp)));
title('HW2-3b  Non-zero phase filtered Lena image');

