%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 706 Homework #2     %
% Salim Sirtkaya, 112434-6 %
% March , 2005, METU EE    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all;
close all;

a=332;b=220;

IM1= imread('1.BMP');
IM1 = double(IM1(11:230,11:342,1));
IM2= imread('2.BMP');
IM2 = double(IM2(11:230,11:342,1));
IM3= imread('3.BMP');
IM3 = double(IM3(11:230,11:342,1));
IM4= imread('4.BMP');
IM4 = double(IM4(11:230,11:342,1));



IM_1_2_diff = abs(IM1 -IM2);

MSE_orig = sum(sum(IM_1_2_diff.^2))/(332*220)

figure;
imshow(uint8(255-IM_1_2_diff));

% Read the optical flow vectors in x direction
A=fopen('D:\DERS\PHD\VIDEO\HOMEWORK_2\KLT1-2_V_x_5_5_3.txt','r');
Vx=fscanf(A,'%f\t',[a b]);
Vx=Vx';
fclose(A);

% Read the optical flow vectors in x direction
A=fopen('D:\DERS\PHD\VIDEO\HOMEWORK_2\KLT1-2_V_y_5_5_3.txt','r');
Vy=fscanf(A,'%f\t',[a b]);
Vy=Vy';
fclose(A);

% Warping of the second image towards the first according to the optical flow vectors

%% equate the outermost 5 pixel-width strip of warped image to image 1

Warp1(1:220,1:332)=0;
f=0;
for i=6:215
    for j=6:328
        
        if ((abs(Vx(i,j))+abs(Vy(i,j)))~=0)
            a=ceil(i-Vx(i,j));
            b=floor(i-Vx(i,j));
            c=ceil(j-Vy(i,j));
            d=floor(j-Vy(i,j));
            
            if (a == b)
                b = a - 1;
            end
            
            if (c == d)
                c = d -1;
            end
                
            
            dist1 = sqrt( (a-(i-Vx(i,j)))^2 + (c-(j-Vy(i,j)))^2 );
            dist2 = sqrt( (a-(i-Vx(i,j)))^2 + (d-(j-Vy(i,j)))^2 );
            dist3 = sqrt( (b-(i-Vx(i,j)))^2 + (c-(j-Vy(i,j)))^2 );
            dist4 = sqrt( (b-(i-Vx(i,j)))^2 + (d-(j-Vy(i,j)))^2 );        
            
            total_dist=sqrt(2);
            
            Warp1(a,c)=Warp1(a,c)+IM2(i,j)*(sqrt(2)-dist1)/total_dist;
            Warp1(a,d)=Warp1(a,d)+IM2(i,j)*(sqrt(2)-dist2)/total_dist;
            Warp1(b,c)=Warp1(b,c)+IM2(i,j)*(sqrt(2)-dist3)/total_dist;
            Warp1(b,d)=Warp1(b,d)+IM2(i,j)*(sqrt(2)-dist4)/total_dist; 
        else
            Warp1(i,j) = IM2(i,j);
        end
        
    end
end

Warp1(1:5,1:332)=IM1(1:5,1:332);
Warp1(216:220,1:332)=IM1(216:220,1:332);
Warp1(1:220,1:5)=IM1(1:220,1:5);
Warp1(1:220,328:332)=IM1(1:220,328:332);

for i=1:220
    for j=1:332
        if (Warp1(i,j)>255)
            Warp1(i,j)=255;
        end
    end
end

figure;
imshow(Warp1,[]);

IM_diff_warped = abs(IM1-Warp1);

figure;
imshow(uint8(255-IM_diff_warped));

MSE_warped = sum(sum(IM_diff_warped.^2))/(332*220)



