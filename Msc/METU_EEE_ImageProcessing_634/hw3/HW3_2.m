% Howework3 - Question 2       Salim SIRTKAYA 1124346

clear all;
close all;

[CMAN,map]=imread('CMAN.tif'); %read input image
imshow(CMAN)  %display the image
title('Cameraman image')
CMAN=double(CMAN); %convert to double 

%creation of 9x9 seperable binomial filter
B=((1/(2^8))* [1 8 28 56 70 56 28 8 1]') * ((1/(2^8))*[1 8 28 56 70 56 28 8 1]); 

%creation of Laplacian operator
L=[0 1 0;1 -4 1;0 1 0];

%creation of LoG operator
LoG=conv2(B,L);

%impulse response of LoG operator
Imp_LoG=freqz2(LoG);

figure
imshow(Imp_LoG,[]);
title('Impulse response of LoG operator with BF of size 9x9');

%LoG filtered image
LoG_CMAN=conv2(CMAN,LoG); 

figure
imshow(LoG_CMAN,[]);
title('LoG filtered Cameraman image with BF of size 9x9');

%finding the zero-crossings of the LoG filtered Cameraman Image
[X Y] = size(LoG_CMAN); % get the size of the LoG filtered image
x = 2:X-1; % since we'll look for the neighbouring pixel values
y = 2:Y-1; % the outermost part of the image is ommited

%For zero crossing detection we should look for change in the sign of neighbouring pixel
%locations of each pixel. We consider only the horiontal and vertical neighbours. If any 
%one of the neighbouring pixels has opposite sign, the candidate will be an zero crossing point.
Z_cross = ones(X-2,Y-2)-(( LoG_CMAN(x,y) < 0 & LoG_CMAN(x,y+1) > 0) ...		
                           |( LoG_CMAN(x,y) < 0 & LoG_CMAN(x+1,y) > 0)...	
                           |( LoG_CMAN(x-1,y) > 0 & LoG_CMAN(x,y) < 0)...	
                           |( LoG_CMAN(x,y-1) > 0 & LoG_CMAN(x,y) < 0));
figure
imshow(Z_cross,[]);
title('Zero crossing map with BF of size 9x9');

%Using binomial filter of size 7x7

%creation of 7x7 seperable binomial filter
B_2=((1/(2^6))* [1 6 15 20 15 6 1]') * ((1/(2^6))*[1 6 15 20 15 6 1]);

%creation of LoG operator
LoG_2=conv2(B_2,L);

%impulse response of LoG_2 operator
Imp_LoG_2=freqz2(LoG_2);

figure
imshow(Imp_LoG_2,[]);
title('Impulse response of LoG operator with BF of size 7x7');

%LoG filtered image
LoG_CMAN_2=conv2(CMAN,LoG_2); 

figure
imshow(LoG_CMAN_2,[]);
title('LoG filtered Cameraman image with BF of size 7x7');

%finding the zero-crossings of the LoG filtered Cameraman Image
[X Y] = size(LoG_CMAN_2);% get the size of the LoG filtered image
x = 2:X-1; % since we'll look for the neighbouring pixel values
y = 2:Y-1; % the outermost part of the image is ommited

%For zero crossing detection we should look for change in the sign of neighbouring pixel
%locations of each pixel. We consider only the horiontal and vertical neighbours. If any 
%one of the neighbouring pixels has opposite sign, the candidate will be an zero crossing point.
Z_cross_2 = ones(X-2,Y-2)-(( LoG_CMAN_2(x,y) < 0 & LoG_CMAN_2(x,y+1) > 0)...	
                             |( LoG_CMAN_2(x,y) < 0 & LoG_CMAN_2(x+1,y) > 0)...	
                             |( LoG_CMAN_2(x-1,y) > 0 & LoG_CMAN_2(x,y) < 0)...	
                             |( LoG_CMAN_2(x,y-1) > 0 & LoG_CMAN_2(x,y) < 0));
figure
imshow(Z_cross_2,[]);
title('LoG filtered Cameraman image with BF of size 7x7');

% It is seen that if we apply binomial filter of size 9x9 we get better results.
% This is due to the fact that, since there is no check on the magnitude of f'(x,y)
% any small ripple in f(x,y) will generate an edge point..So it is very sensitive to noise.
% A smoothing filter is desirable to suppress the noise and give better edge detection.
% Thus 9x9 binomial filter is a better smoothing filter than 7x7 binomial filter





