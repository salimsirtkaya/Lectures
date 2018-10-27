ONE_rscl=imresize(ONE,[230,246],'bilinear');
figure;imshow(ONE_rscl,[]);
imwrite(ONE_rscl,ONE_rscl,'bmp');

TWO_rscl=imresize(TWO,[230,287],'bilinear');
figure;imshow(TWO_rscl,[]);
imwrite(TWO_rscl,TWO_rscl,'bmp');

THREE_rscl=imresize(THREE,[230,287],'bilinear');
figure;imshow(THREE_rscl,[]);
imwrite(THREE_rscl,THREE_rscl,'bmp');