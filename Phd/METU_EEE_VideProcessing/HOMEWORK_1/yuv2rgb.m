%% written by Salim SIRTKAYA , March 2005 , METU EE%%
% Convert YUV image to RGB

function RGB = yuv2rgb(YUV);

% The following matrices define the transformations between RGB and YUV
RGB2YUV = [0.299 0.587 0.114 ; -0.147 -0.289 0.436 ; 0.615 -0.515 -0.1 ];
YUV2RGB = inv(RGB2YUV);

[h w]=size(YUV(:,:,1));

%Convert the first image to RGB space 
YUV_raster= reshape(YUV, h*w, 3);

YUV_raster = double(YUV_raster);

YUV_raster(:, 2 : 3) = YUV_raster(:, 2 : 3) - 127;

% Convert YUV image to RGB anf YIQ
rgb = (YUV2RGB * YUV_raster.').';
% Clip the values >255 or <0 for RGB
for i = 1 : 1 : size(rgb(:))
	if rgb(i) < 0
		rgb(i) = 0;
	elseif rgb(i) > 255
		rgb(i) = 255;
	end
end

rgb=uint8(rgb);

RGB = reshape(rgb,h,w,3);

