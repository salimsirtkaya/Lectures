%1.a   Finding the histogram
figure;
imshow('one.bmp');
figure;
imshow('two.bmp');
figure;
imshow('three.bmp');

% Histogram for one.bmp
ONE=imread('one.bmp');
ONE=double(ONE);
Hist1=zeros(255,1);
for m=1:373
    for n=1:400
       Hist1(1+ONE(m,n),1)=Hist1(ONE(m,n)+1,1)+1;
   end 
end
figure;
stem(Hist1);
title('Histogram of one.bmp');

% Histogram for two.bmp
TWO=imread('two.bmp');
TWO=double(TWO);
Hist2=zeros(255,1);
for m=1:320
    for n=1:400
       Hist2(1+TWO(m,n),1)=Hist2(TWO(m,n)+1,1)+1;
   end 
end
figure;
stem(Hist2);
title('Histogram of two.bmp');

% Histogram for three.bmp
THREE=imread('three.bmp');
THREE=double(THREE);
Hist3=zeros(255,1);
for m=1:320
    for n=1:400
       Hist3(1+THREE(m,n),1)=Hist3(THREE(m,n)+1,1)+1;
   end 
end
figure;
stem(Hist3);
title('Histogram of three.bmp');



