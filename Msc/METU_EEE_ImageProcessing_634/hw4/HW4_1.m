% Howework4 - Question 1                       Salim SIRTKAYA 1124346

% *************  INVERSE FILTERING  ******************

clear all;
close all;

[b_oto,map]=imread('b_otopark.bmp'); %read input image
figure
imshow(b_oto)  %display the image
title('blurred otopark image')  % the amount of blur is 11 pixels
b_oto=double(b_oto); %convert to double 

%*****************************************************
%part a...  Pseudo Inverse Filtering of blurred image
%*****************************************************

% Blurring filter 
filt=ones(1,11)/11;
Filt=fft(filt,256); % we take 256 point fft to make calculations easier in freq domain

figure
plot(abs(Filt))
title('Blurring Transfer Function')

% Output of the Deblurring filtering 
B_OTO= fft2(b_oto);
Filt=ones(256,1)*Filt;  % to handle 2D image we make the filter 2D without changing characteristics in
                        % horizontal dimensions

% Making the transfer function of the pseudo-inverse filter equal to zero 
% if the blur transfer function falls below 0.1
I_Filt=1./Filt;
K=abs(Filt)>0.1;
PI_Filt=K.*I_Filt;

figure
plot(abs(PI_Filt(1,1:256)))
title('Pseudo Inverse (Deblurring) Transfer Function')

DB_OTO=B_OTO.*PI_Filt;

db_oto = abs(ifft2(DB_OTO));
figure
imshow(db_oto,[0 255])
title('Pseudo-Inverse Filtered Image')

%*************************************************************
%part b...  Realization in space domain using Hamming window
%*************************************************************

% Obtain the hamming window using matlab function hamming
h_win = hamming(41);

% Obtain the 2-D filter from hamming window
% "fwind1" function of MATLAB is used to obtain a 2D FIR 
% filter using a 1D window function(hamming). 
h_filt = fwind1(I_Filt,h_win);

figure
H_filt=fft2(h_filt);
plot(abs(H_filt(1,1:41)))
title('Hfilt along x obtained with hamming window')

H_OTO=filter2(h_filt,b_oto);

figure
imshow(H_OTO,[]);
title('Space Domain Filtered Image')


%*************  COMMENTS *************

% The filter in part_a is more effective in reducing the blurring 
% than the filter in part_b. This is because the filter in part_b is
% a FIR filter and is a kind of approximation to the filter in part_a.
