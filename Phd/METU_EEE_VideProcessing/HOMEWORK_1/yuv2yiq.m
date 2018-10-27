%% written by Salim SIRTKAYA , March 2005 , METU EE%%
% Convert YUV image to YIQ

function YIQ = yuv2rgb(YUV);

% The following matrices define the transformations between RGB, YUV and YIQ
RGB2YUV = [0.299 0.587 0.114 ; -0.147 -0.289 0.436 ; 0.615 -0.515 -0.1 ];
YUV2RGB = inv(RGB2YUV);

RGB2YIQ = [0.299 0.587 0.114 ; 0.596 -0.275 -0.321 ; 0.212 -0.523 0.311];
YIQ2RGB = inv(RGB2YIQ);

YIQ2YUV= RGB2YUV*YIQ2RGB;
YUV2YIQ= RGB2YIQ*YUV2RGB;

[h w]=size(YUV(:,:,1));

%Convert the first image to RGB space 
YUV_raster= reshape(YUV, h*w, 3);

YUV_raster = double(YUV_raster);

% YUV_raster(:, 2 : 3) = YUV_raster(:, 2 : 3) - 127;

% Convert YUV image to RGB anf YIQ
yiq = (YUV2YIQ * YUV_raster.').';
% % Clip the values >255 or <0 for RGB
% for i = 1 : 1 : size(yiq(:))
% 	if yiq(i) < 0
% 		yiq(i) = 0;
% 	elseif yiq(i) > 255
% 		yiq(i) = 255;
% 	end
% end

yiq=uint8(yiq);

YIQ = reshape(yiq,h,w,3);





