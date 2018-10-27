%1.b   Determining the threshold manually

% Manual Thresholding for one.bmp
ONE_thr=ONE>=60;

figure;
imshow(ONE_thr);

% Manual Thresholding for two.bmp
TWO_thr=TWO>=40;

figure;
imshow(TWO_thr);

% Manual Thresholding for three.bmp
THREE_thr=THREE>=65;

figure;
imshow(THREE_thr);
