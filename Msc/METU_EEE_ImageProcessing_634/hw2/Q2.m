%PROBLEM#2
clear all
close all
[im,map]=imread('lena.bmp'); %read input image
imshow(im)  %display the image
title('Lena image')
im=double(im); %convert to double 
%
%Part a
u=ones(1,256);
u(2:2:256)=-1;%Sequence of +1-1+1-1....
checker=u'*u; % -1^(n1+n2)  (shifted to (1,1))
im_checker=im.*checker;
%
%Part b
IM_checker=fft2(im_checker);
figure
imshow(log10(1+abs(IM_checker)),[ ]) %display scaled to range 0-255
title('logFFT of Lena, shifted to center')
%
%Part c
IM_checker=conj(IM_checker);
%
%Part d
im_inv=real(ifft2(IM_checker));
%
%Part e
im_inv=im_inv.*checker;
figure
imshow(uint8(im_inv))
title('resulting image')

%%%%%%%%%%%%%%%%%%%%%%%
%EXPLANATION
%   Multiplication  by (-1)^(n1+n2) is same as multiplying with 
%   exp{-j[2*pi*n1*(N/2)/N + 2*pi*n2*(N/2)/N]} which corresponds to
%   shifting the transform by an amount N/2 along w1  and along w2.

%   Complex conjugating transform of the image corresponds to flipping 
%   the image in space domain along both axes, or rotating the image around 
%   origin by 180 degrees.
%   Since ifft of the shifted transform results in complex multiplication by
%   exp{-j[2*pi*n1*(N/2)/N + 2*pi*n2*(N/2)/N]} or equivalently by (-1)^(n1+n2)
%   we correct the image by multiplying with (-1)^(n1+n2).