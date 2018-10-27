%PROBLEM 1
%Part a
clear all
close all
[im,map]=imread('lena.bmp'); %read input image
imshow(im)  %display the image
title('Lena image')
im=double(im); %convert to double 
histo=zeros(256,1); %initialize histogram

for i=1:256
    for j=1:256
        histo(im(i,j)+1)=histo(im(i,j)+1)+1;
    end
end

figure
plot(histo)
title('Histogram of the input image')
%Note: Due to indexing convention of Matlab histogram levels
%   are shifted by 1 unit.

%^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
%  Part b
% Uniform quantization to 8 levels
% Levels are 16+(256/8)*(n-1),  n=1:8
tran_level(1)=0;
for i=2:8
    tran_level(i)=round((i-1)*256/8);
end
tran_level(9)=256;
for i=1:8
    rec_level(i)=(tran_level(i)+tran_level(i+1))/2;
end
rec_level
tran_level
%quantiztion table
q_map=ones(256,1);

for i=1:8
    q_map(tran_level(i)+1:tran_level(i+1))=rec_level(i);
end
% Now quantize the Lena image
im_uni_q=q_map(im+1);%"+1" due to indexing convention of Matlab
figure
imshow(im_uni_q,map) %use the color-map of input Lena image
title('Uniform quantized Lena-image to 8 levels')

%^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
%Part c
%8 level optimum mean square quantizer designed for Gaussian density 

im_mean=mean(im(:));
im_std=std(im(:));

%Transition levels
tran_level(1)=0;
tran_level(2)=im_mean-1.748*im_std;
tran_level(3)=im_mean-1.05*im_std;
tran_level(4)=im_mean-0.5006*im_std;
tran_level(5)=im_mean;
tran_level(6)=im_mean+0.5006*im_std;
tran_level(7)=im_mean+1.05*im_std;
tran_level(8)=im_mean+1.748*im_std;
tran_level(9)=256;

%Reconstruction levels
rec_level(1)=im_mean-2.152*im_std;
rec_level(2)=im_mean-1.344*im_std;
rec_level(3)=im_mean-0.7561*im_std;
rec_level(4)=im_mean-0.2451*im_std;
rec_level(5)=im_mean+0.2451*im_std;
rec_level(6)=im_mean+0.7561*im_std;
rec_level(7)=im_mean+1.344*im_std;
rec_level(8)=im_mean+2.152*im_std;

%quantiztion table
q_map=ones(256,1);

for i=1:8
    q_map(round(tran_level(i))+1:round(tran_level(i+1)))=round(rec_level(i));
end
% Now quantize the Lena image
im_Gaus_q=q_map(im+1);%"+1" due to indexing convention of Matlab

% Now quantize the Lena image
im_Gaus_q=q_map(im+1);%"+1" due to indexing convention of Matlab
figure
imshow(im_Gaus_q,map) %use the color-map of input Lena image
title('Output of 8 level optimum quantizer for Gaussian density')




%This is not an optimum quantizer. 
%It would be optimum if Lena image had Gaussian density


% Part d

% PSNR for part b
error_square=(im-im_uni_q).*(im-im_uni_q);
noise_power=sum(error_square(:))/65536;
 PSNR_b=10*log10(65536/noise_power);
 
 %PSNR for part c
 error_square=(im-im_Gaus_q).*(im-im_Gaus_q);
 noise_power=sum(error_square(:))/65536;
  PSNR_c=10*log10(65536/noise_power);
  
  disp(['PSNR (part_b) = ' num2str(PSNR_b) ' dB'])
disp(['PSNR (part_c) = ' num2str(PSNR_c) ' dB'])
disp('PSNR is lower for uniform quantization. ')




        
    
    
    
    