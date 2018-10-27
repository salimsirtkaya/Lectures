
%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
imshow(I),title('the original map, coordinate space')
se = strel('square',15);
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a square robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
se = strel('disk',15);
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a circular robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
se = [0 0 0 1 0 0 0
      0 0 1 1 1 0 0
      0 1 1 1 1 1 0
      1 1 1 1 1 1 1]
  
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a triangular robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
se = [0 0 0 1 0 0 0
      0 0 1 1 1 0 0
      0 1 1 1 1 1 0
      1 1 1 1 1 1 1
      1 1 1 1 1 1 1
      0 1 1 1 1 1 0
      0 0 1 1 1 0 0
      0 0 0 1 0 0 0]
  
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a rhombus robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%