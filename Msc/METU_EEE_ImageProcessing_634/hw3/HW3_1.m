% Howework3 - Question 1        Salim SIRTKAYA 1124346

clear all;
close all;

%1.a   Finding horizontal gradient image for house.bmp

[HOUSE,map]=imread('house.bmp'); %read input image
imshow(HOUSE)  %display the image
title('house image')
HOUSE=double(HOUSE); %convert to double 

h=[-3 -3 5;-3 0 5;-3 -3 5] ; %create the mask

h_imp=[5 5 5;-3 0 -3; -3 -3 -3]; %create corresponding impulse response
hor_HOUSE=conv2(HOUSE,h_imp); %obtain horizontal gradient

hor_HOUSE_scaled = hor_HOUSE + abs(min(min(hor_HOUSE)));
hor_HOUSE_scaled = hor_HOUSE_scaled * 255/max(max(hor_HOUSE_scaled));

figure
imshow(uint8(hor_HOUSE_scaled));
title('horizontal gradient image of house.bmp');

%1.b   Finding vertical gradient image for house.bmp

v=h'; %create vertical mask
v_imp=h_imp';%create corresponding impulse response
ver_HOUSE=conv2(HOUSE,v_imp);%obtain vertical gradient

%scaling is done by adding the minimum negative value of the
%gradient image to itself to guarantee that the minimum value is zero.
%than the maximum value is used to gurantee that maximum is 255
ver_HOUSE_scaled = ver_HOUSE + abs(min(min(ver_HOUSE))); 
ver_HOUSE_scaled = ver_HOUSE_scaled * 255/max(max(ver_HOUSE_scaled)); 

figure
imshow(uint8(ver_HOUSE_scaled));
title('vertical gradient image of house.bmp');

%total gradient image
tot_HOUSE=hor_HOUSE+ver_HOUSE;

%scaling
tot_HOUSE_scaled = tot_HOUSE + abs(min(min(tot_HOUSE))); 
tot_HOUSE_scaled = tot_HOUSE_scaled * 255/max(max(tot_HOUSE_scaled)); 

figure
imshow(uint8(tot_HOUSE_scaled));
title('total gradient image of house.bmp');

%1.c  Finding the edge map of house.bmp

ind_values = tot_HOUSE_scaled(:); %obtain a vector of the elements of the gradient image
a_ind_values = sort(ind_values); %sort the elements of the vector in ascending order
ind = round(size(a_ind_values) * 0.90); %find the index of the %10 threshold value exists
Threshold = a_ind_values(ind(1)); % find the threshold value
Edge_Map = ones(size(tot_HOUSE_scaled)); % make the whole image white
Edge_Map(tot_HOUSE_scaled >= Threshold) =0; % make the values that are above the threshold black
figure;
imshow(Edge_Map);
title('Edge Map of house.bmp with %10 threshold');






