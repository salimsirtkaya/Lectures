%% written by Salim SIRTKAYA , March 2005 , METU EE%%

% This is a general function that reads binary data from a cif video 
% and puts it into ordered matrices Y,U,V
% "filename" specifies the cif video to be read
% "index" specifies the order of the frame to be read in the video sequence
% w specifies the width of the image
% h specifies the height of the image

function YUV = read_cif(filename,index,w,h)

%Read the raw video in CIF format
fid=fopen(filename,'r');

% Upsampling matrix for U and V components
UpS= [1, 1;1, 1];

Total_p=w*h+w*h/2; % Number of total bytes for Y ,U and V components for each frame

%Go to the pointer which is specified by input index
status = fseek(fid,Total_p*index,'bof'); 

if (status==-1)
    disp('The pointer cannot be moved');
end

w2=w/2;
h2=h/2;

% Seperate Y , U and V components from the video stream
% and put them into matrix format

% read Y component
Y_raster = fread(fid, w*h, 'uchar');
YUV(:,:,1)=reshape(Y_raster,w,h).';

% read U component and upsample it 
U_raster = fread(fid, w/2*h/2, 'uchar');
YUV(:,:,2)=kron(reshape(U_raster,w/2,h/2).',UpS);

% read V component and upsample it
V_raster = fread(fid, w/2*h/2, 'uchar');
YUV(:,:,3)=kron(reshape(V_raster,w/2,h/2).',UpS);

fclose(fid);



