

%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze.bmp');
%a=imread('maze2.bmp');
I=rgb2gray(a);
%I=double(I);
imshow(I)
se = strel('square',40);
b = imerode(I,se);
[x,y]=size(b);
figure,imshow(b)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%now find the white%%%%% 
%%%%%%%regions' centers%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%here we took a block of 10 pixels... we test if there is a white squares
%inside this block... if there exist take any pixel to be the center


k=1;

for i=1:x       %here we r testing blocks of 10x10 pixels
    for j=1:y
     
        if (b(i,j)==255)&(b(i,j-1)==0)&(b(i-1,j)==0)
            m(1,k)=i+1;
            m(2,k)=j+2;
            k=k+1;
        end
     
    

    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       after getting the centers
%       we will draw Voronoi diagram
%       using m and n vectors
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
r=1:k-1
xx=m(1,r)
yy=m(2,r)
hold on
voronoi(yy,xx)










