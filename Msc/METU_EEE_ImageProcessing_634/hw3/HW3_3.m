% Howework3 - Question 3       Salim SIRTKAYA 1124346

clear all;
close all;

[IR,map]=imread('ir6.bmp'); %read input image
imshow(IR)  %display the image
title('Infrared image')
IR=double(IR); %convert to double 

%creation of 7x7 seperable binomial filter
B=((1/(2^6))* [1 6 15 20 15 6 1]') * ((1/(2^6))*[1 6 15 20 15 6 1]);

%low-pass filtered image with 7x7 binomial filter
% (Local Luminance Image)
Lum_IR=conv2(IR,B);

figure
imshow(Lum_IR,[]);
title('Low-pass filtered Infrared Image');

%Local Contrast Image is obtained by subtracting
%Binomial filtered image from the original image
[X Y]=size(Lum_IR);
Lum_IR=Lum_IR(1:X-6,1:Y-6);
Con_IR= IR-Lum_IR;

Con_IR_scaled = Con_IR + abs(min(min(Con_IR))); 
Con_IR_scaled = Con_IR_scaled * 255/max(max(Con_IR_scaled));

figure
imshow(Con_IR,[]);
title('Local Contrast IR Image');

%Modifying the Local Contrast Image
K_Con_IR=5+3*cos(pi*(Lum_IR-20)/64);

M_Con_IR=K_Con_IR.*Con_IR_scaled;
M_Con_IR_scaled = M_Con_IR + abs(min(min(M_Con_IR))); 
M_Con_IR_scaled = M_Con_IR_scaled * 255/max(max(M_Con_IR_scaled));


%Modifying Local Luminance
M_Lum_IR=0.8*Lum_IR+40;

OUTPUT_IR=M_Lum_IR+M_Con_IR_scaled;

figure
imshow(OUTPUT_IR,[]);
title('Local Contrast Modified IR Image');

%%COMMENTS
% This sysytem achieves Local Contrast modification by two channel processing.
% We apply different mappings to two components, Local Contrast and Local Luminance Mean.
% "It is seen that bright parts of the image is enhanced." This is due to characteristics of
% two mappings. In the mapping of Local Contrast (i.e. k=5+3*cos(pi*(x-20)/64)),
% k is large for 

