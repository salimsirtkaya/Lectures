% Howework4 - Question 2                       Salim SIRTKAYA 1124346

% *************  Wiener filtering of degraded noisy images  ******************

clear all;
close all;

[nb_oto,map]=imread('nb_otopark.bmp'); %read input image 
figure
imshow(nb_oto)  %display the image
title('Noisy and Blurred otopark image')  % the amount of blur is 11 pixels
nb_oto=double(nb_oto); %convert to double 

%*****************************************************
% Estimation of Power Spectral Density using Blackman-Tukey method
%*****************************************************
[x,y]=size(nb_oto);

NB_OTO=fft2(nb_oto);

% Estimation of autocorrelation using fft 
R_nboto=ifft2(NB_OTO.^2)/(x*y);

% construction of hamming window using MATLAB function "hamming"
h_win=hamming(x)*hamming(y)';

S_nboto=fft2(R_nboto.*h_win,256,256);
S_nboto=abs(S_nboto);

% Power spectral Density of gaussian noise with std=15
S_gaus=225;

% In the cascade structure first we make the noise removal 
R_OTO= NB_OTO.*(S_nboto./(S_nboto+S_gaus));

r_oto=abs(ifft2(R_OTO));

figure
imshow(r_oto,[]);
title('Noise is removed using optimum filter')

% The second part of the cascade structure is deblurring with pseudo inverse filtering

% Construction of Pseudo Inverse Filter (same in question 1)
filt=ones(1,11)/11;
Filt=fft(filt,256); 
Filt=ones(256,1)*Filt;
I_Filt=1./Filt;
K=abs(Filt)>0.1;
PI_Filt=K.*I_Filt;

% Aplly the filter
F_OTO = R_OTO.*PI_Filt;

f_oto = abs(ifft2(F_OTO));
figure
imshow(f_oto, [0 255])
title('Output of the cascade filter')

%**************  COMMENTS  *********************************

% The result is not satisfactory since it has a lot of noise. This is because, in our cascade 
% filter structure image is assumed to be zero-mean. We should have taken into account the contributions of the mean component.
% And also the structure is not adaptive since no local calculations are taken into 
% account. Also the size of the hamming window is an important parameter in the result such that 
% if we have chosen a smaller window size, the estimator will be smoother. But in this case there
% will be resolution loss.