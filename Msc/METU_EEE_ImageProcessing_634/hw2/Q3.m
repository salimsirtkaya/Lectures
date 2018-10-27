%PROBLEM 3
%
clear all
close all

%Part a
%First  obtain the filter transfer function
H=zeros(256);
H(96:160,96:160)=1; %(pi/4)=128/4=32. Origin is at (128,128).
%
%
[im,map]=imread('lena.bmp'); %read input image
imshow(im)  %display the image
title('Lena image')
im=double(im); %convert to double 
u=ones(1,256);
u(2:2:256)=-1;%Sequence of +1-1+1-1....
checker=u'*u; % -1^(n1+n2)  (shifted to (1,1))
im_checker=im.*checker;
IM_checker=fft2(im_checker); %F.T. of image centered at (128,128)
H_IM=H.*IM_checker; % filtering in frequency domain
h_im=real(ifft2(H_IM));
h_im=h_im.*checker;
figure
imshow(uint8(h_im),map)
title('Lowpass filtered Lena image')
%
%
[im,map]=imread('testpattern.tif'); %read input image
figure
imshow(im)  %display the image
title('Testpattern')
im=double(im); %convert to double 
im_checker=im.*checker;
IM_checker=fft2(im_checker);
H_IM=H.*IM_checker; % filtering in frequency domain
h_im=real(ifft2(H_IM));
h_im=h_im.*checker;
figure
imshow(uint8(h_im),map)
title('Lowpass filtered testpattern image')
% COMMENTS
%   You can see the ringing effect around edges of the Lena image due
%   to sharp discontinuity of the ideal rectangular filter.
%   In test pattern the cutoff frequency is clearly observed. Note the contrast reversals
%   along x and y directions. The filter is not isotropic, and the behaviour along
%   45 and 135 degrees is different than alog x and y axes.
%

%Part b
% Modify the filter.
l=1:256;
   for k=1:256
      phase(k,l)=cos(2*pi*sin(2*pi*((k-128)+(l-128))/128))+i*sin(2*pi*sin(2*pi*((k-128)+(l-128))/128));
   end

H=H.*phase;
%
%
[im,map]=imread('lena.bmp'); %read input image
im=double(im); %convert to double 
im_checker=im.*checker;
IM_checker=fft2(im_checker);
H_IM=H.*IM_checker; % filtering in frequency domain
h_im=abs(ifft2(H_IM));
h_im=h_im.*checker;
figure
imshow(uint8(h_im),[])
title('Lowpass filtered Lena image, with phase distotion')

[im,map]=imread('testpattern.tif'); %read input image
im=double(im); %convert to double 
im_checker=im.*checker;
IM_checker=fft2(im_checker);
H_IM=H.*IM_checker; % filtering in frequency domain
h_im=abs(ifft2(H_IM));
h_im=h_im.*checker;
figure
imshow(uint8(h_im),[])
title('Lowpass filtered testpattern, phase distortion')



