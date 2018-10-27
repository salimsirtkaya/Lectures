% Howework2 - Question 1        Salim SIRTKAYA 1124346

clear all;
close all;

%1.a   Finding histogram for Lena.bmp
LENA=imread('Lena.bmp');
Hist=zeros(256,1);
for m=1:256
    for n=1:256
       Hist(LENA(m,n),1)=Hist(LENA(m,n),1)+1;
   end 
end
figure(1);
stem(Hist);
title('HW2-1a  Histogram of Lena image');

%1.b   Uniform Quantization of Lena.bmp
%   L=8   256/8=32.    0 32 64 96 128 160 192 224 255 are the transition levels
%   16 48 80 112 144 176 208 240 are the reconstruction levels  { Ri=(Ti + Ti+1)/2  }
     
LUT1= [16*ones(32,1) ; 48*ones(32,1) ; 80*ones(32,1) ; 
      112*ones(32,1) ; 144*ones(32,1) ; 176*ones(32,1);
      208*ones(32,1) ; 208*ones(32,1) ; 240*ones(32,1)];

Q_uniform=LUT1(LENA);
figure(2);
imshow(uint8(Q_uniform));
title('HW2-1b  8 level uniform quantizated Lena image');

%1.c  Optimum Mean Square Quantization of Lena.bmp
% The transition levels are found as    40  73  100  124  148  174  207
% The reconstruction levels are found as   20 59 87  111  135  159  187  226

Lena=double(LENA);
deviation=std2(Lena);
median=mean2(Lena);
tk=[-1.748 -1.05 -0.5006 0 0.5006  1.05 1.748];
tk=double(tk);
TR=deviation*tk+median; %calculation of transition levels
TR=round(TR);
rc=[-2.152 -1.344 -0.7561 -0.2451 0.2451 0.7561 1.344 2.152];
rc=double(rc);
RC=deviation*rc+median; % calculation of reconstruction levels

LUT2= [RC(1)*ones(TR(1),1) ; RC(2)*ones(TR(2)-TR(1),1) ; RC(3)*ones(TR(3)-TR(2),1) ; 
       RC(4)*ones(TR(4)-TR(3),1) ; RC(5)*ones(TR(5)-TR(4),1) ; RC(6)*ones(TR(6)-TR(5),1);
       RC(7)*ones(TR(7)-TR(6),1) ; RC(8)*ones(255-TR(7),1) ];
   
Q_optimum=LUT2(LENA);
figure(3);
imshow(uint8(Q_optimum));
title('HW2-1c  8 level optimum quantizated Lena image');

% This is an optimum quantizer. Because the quantiation levels are 
% chosen such that they are concentrated on the most data carrying part of the image.
% It is assumed that the image has a gaussian distribution. This assumption
% is natural.

%1.d Calculation of PSNR

% Peak SNR calculation for uniform quantizer
N_uniform=sum(sum(abs(Lena-Q_uniform)));
N_uniform_av=N_uniform/(256*256);
PSNR_uniform=10*log(255*255/N_uniform_av)

%Peak SNR calculation for optimum quantizer
N_optimum=sum(sum(abs(Lena-Q_optimum)));
N_optimum_av=N_optimum/(256*256);
PSNR_optimum=10*log(255*255/N_optimum_av)


