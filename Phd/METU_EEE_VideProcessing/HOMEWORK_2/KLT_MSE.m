%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 706 Homework #2     %
% Salim Sirtkaya, 112434-6 %
% March , 2005, METU EE    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function KLT_MSE(Image1,Image2,file1,file2,a,b)


a=a-20;
b=b-20;

IM1= imread(Image1);
IM1 = double(IM1(11:b+10,11:a+10,1));
IM2= imread(Image2);
IM2 = double(IM2(11:b+10,11:a+10,1));


IM_1_2_diff = abs(IM1 -IM2);

MSE_orig = sum(sum(IM_1_2_diff.^2))/(a*b)

figure;
imshow(uint8(255-IM_1_2_diff));

% Read the optical flow vectors in x direction
A=fopen(file1,'r');
Vx=fscanf(A,'%f\t',[a b]);
Vx=Vx';
fclose(A);

% Read the optical flow vectors in x direction
A=fopen(file2,'r');
Vy=fscanf(A,'%f\t',[a b]);
Vy=Vy';
fclose(A);

% Warping of the second image towards the first according to the optical flow vectors

%% equate the outermost 5 pixel-width strip of warped image to image 1

Warp1(1:b,1:a)=0;

for i=11:b-9
    for j=11:a-9
        
        if ((abs(Vx(i,j))+abs(Vy(i,j)))~=0)
            x1=ceil(i-Vx(i,j));
            x2=floor(i-Vx(i,j));
            y1=ceil(j-Vy(i,j));
            y2=floor(j-Vy(i,j));
            
            if (x1 == x2)
                x2 = x1 - 1;
            end
            
            if (y1 == y2)
                y2 = y1 - 1;
            end
                
            
            dist1 = sqrt( (x1-(i-Vx(i,j)))^2 + (y1-(j-Vy(i,j)))^2 );
            dist2 = sqrt( (x1-(i-Vx(i,j)))^2 + (y1-(j-Vy(i,j)))^2 );
            dist3 = sqrt( (x2-(i-Vx(i,j)))^2 + (y2-(j-Vy(i,j)))^2 );
            dist4 = sqrt( (x2-(i-Vx(i,j)))^2 + (y2-(j-Vy(i,j)))^2 );        
            
            total_dist=sqrt(2);
            
            Warp1(x1,y1)=Warp1(x1,y1)+IM2(i,j)*(sqrt(2)-dist1)/total_dist;
            Warp1(x1,y2)=Warp1(x1,y2)+IM2(i,j)*(sqrt(2)-dist2)/total_dist;
            Warp1(x2,y1)=Warp1(x2,y1)+IM2(i,j)*(sqrt(2)-dist3)/total_dist;
            Warp1(x2,y2)=Warp1(x2,y2)+IM2(i,j)*(sqrt(2)-dist4)/total_dist; 
        else
            Warp1(i,j) = IM2(i,j);
        end
        
    end
end

Warp1(1:10,1:a)=IM1(1:10,1:a);
Warp1(b-9:b,1:a)=IM1(b-9:b,1:a);
Warp1(1:b,1:10)=IM1(1:b,1:10);
Warp1(1:b,a-9:a)=IM1(1:b,a-9:a);

for i=1:b
    for j=1:a
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

MSE_warped = sum(sum(IM_diff_warped.^2))/(a*b)



