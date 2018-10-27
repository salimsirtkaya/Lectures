% Howework4 - Question 3                       Salim SIRTKAYA 1124346

% *************  Blind Deconvolution  ****************** (Comments are at the end)

clear all;
close all;

[lstr1,map]=imread('lester1.bmp'); %read input image 
figure
imshow(lstr1)  %display the image
title('Blurred Lester image')  % the amount of blur is unknown
lstr1=double(lstr1); %convert to double 

%read lester2.bmp
[lstr2,map]=imread('lester2.bmp');
lstr2=double(lstr2);

% In blind-deconvolution method blurring function (B) and the original image 
% are unknowns. But we can assume that B is smooth (due to turbulence, slight defocus)

% In the estimation of B, we'll make use of a different view of the same scene.
% To eliminate the effects of the details we'll pass this image from a low pass filter
% 
B_2=((1/(2^6))* [1 6 15 20 15 6 1]') * ((1/(2^6))*[1 6 15 20 15 6 1]);
L_lstr1=conv2(lstr1,B_2,'same');

L_LSTR1=abs(fft2(L_lstr1));

% Smoothing filter is applied to the input image (lester1.bmp) to eliminate high freq components 
% Let's use 11x11 binomial filter for smoothing operation

%creation of 11x11 seperable binomial filter
binom=((1/(2^10))* [1 10 45 120 210 252 210 120 45 10 1]') * ((1/(2^10))*[1 10 45 120 210 252 210 120 45 10 1]); 

% smoothed lester2.bmp
L_lstr2=conv2(lstr2,binom,'same');

L_LSTR2=abs(fft2(L_lstr2));

% Construction of B
B=L_LSTR1./L_LSTR2;

figure
colormap(jet(64))
mesh(B);
title('Blurring transfer function estimated using Blind-Deconvolution')

LS=fft2(lstr1);

imag=LS./B;

im=abs(ifft2(imag));

figure
imshow(uint8(im),[0 255])
title('Output image obtained with Blind-Deconvolution method')

%****************          COMMENTS       *********************

% In Blind Deconvolution method the phase information of the input(lester1.bmp)
% and the similar image (lester2.bmp) is not use. Because even if the magnitude 
% responses of two similar scenes are similar their phase terms vary significantly.
% This method reduces the blurring significantly but it increases noise present in the image.




