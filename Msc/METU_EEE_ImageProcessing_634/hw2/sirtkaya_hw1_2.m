% Howework2 - Question 2        Salim SIRTKAYA 1124346

clear all
close all

%2.a multiplying Lena.bmp with (-1)^(n1+n2)
Lena=double(imread('Lena.bmp'));
Base=[1 -1;-1 1];
Minus=repmat(Base,128,128); % construct the desired -1^(n1+n2) matrix by replicating the base matrix
Lena2=Lena.*Minus;

%2.b Taking DFT of Lena.bmp 
FFT_Lena=fft2(Lena2);
Lena3=log(1+abs(FFT_Lena));
figure(1);
mesh(Lena3);
title('HW2-2b  log(1+abs(DFT(Lena*(-1)exp(n1+n2))))');
%2.c Taking the complex conjugate of the transform
Comp_con= conj(FFT_Lena);

%2.d Computing the inverse transform
IF_Lena=ifft2(Comp_con);

%2.e
RIF_Lena=real(IF_Lena);
RIF_Lena=RIF_Lena.*Minus;
figure(2);
imshow(uint8(RIF_Lena));
title('HW2-2e  Reconstructed Lena image');

% In 2.b  multiplying with -1^(n1+n2) results in pi amount of shift in frequency domain,
% this is because -1 can be represented as exp(pi*j) and from the Fourier transform properties
% multiplication with exp(x) results in x amount of shift in frequency domain. 
% { x(n1,n2)*exp(a*n1)*exp(b*n2)-->X(w1-a,w2-b)  where x(n1,n2)-->X(w1,w2)
% In the original figures frequency response, most part of the information was around zero. In the resulting
% log(1+abs(DFT)) the frequency response is shifted to the center due to above told property.

% In 2.e The image is symmetric to the original image with respect to origin. This is because 
% Conjugating the frequrency  response of the filter results in x(-n1,-n2) in spatial domain
% { X'(w1,w2)--> x'(-n1,-n2) where X(w1,w2)-->x(n1,n2)}. Since x is real the recostructed image is
% just the symmetric of the original.



