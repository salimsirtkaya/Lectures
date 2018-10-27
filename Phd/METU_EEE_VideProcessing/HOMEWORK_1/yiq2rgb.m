%% written by Salim SIRTKAYA , March 2005 , METU EE%%
% Convert YUV image to RGB
% I find it more reliable to convert the yiq image to yuv..

function RGB = yiq2rgb(YIQ);

% The following matrices define the transformations between RGB, YUV and YIQ
RGB2YUV = [0.299 0.587 0.114 ; -0.147 -0.289 0.436 ; 0.615 -0.515 -0.1 ];
YUV2RGB = inv(RGB2YUV);

RGB2YIQ = [0.299 0.587 0.114 ; 0.596 -0.275 -0.321 ; 0.212 -0.523 0.311];
YIQ2RGB = inv(RGB2YIQ);

YIQ2YUV= RGB2YUV*YIQ2RGB;
YUV2YIQ= RGB2YIQ*YUV2RGB;

[h w]=size(YIQ(:,:,1));

%Convert the first image to RGB space 
YIQ_raster= reshape(YIQ, h*w, 3);

YIQ_raster = double(YIQ_raster);

yuv = (YIQ2YUV * YIQ_raster.').';
yuv=uint8(yuv);

yuv= reshape(yuv,h,w,3);

RGB = yuv2rgb(yuv);

