%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 706 Homework #1     %
% Salim Sirtkaya, 112434-6 %
% March , 2005, METU EE    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all;close all;

% The following matrices define the transformations between RGB, YUV and YIQ
RGB2YUV = [0.299 0.587 0.114 ; -0.147 -0.289 0.436 ; 0.615 -0.515 -0.1 ];
YUV2RGB = inv(RGB2YUV);

RGB2YIQ = [0.299 0.587 0.114 ; 0.596 -0.275 -0.321 ; 0.212 -0.523 0.311];
YIQ2RGB = inv(RGB2YIQ);

YIQ2YUV= RGB2YUV*YIQ2RGB;
YUV2YIQ= RGB2YIQ*YUV2RGB;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fs=3.04; % Sampling frequency = 352*288 / (1/30) = 3.04 MHz

YUV1 = read_cif('football.cif',0,352,288); %read first frame of the cif video

% Convert the first frame to RGB space for display purposes
RGB1 = yuv2rgb(YUV1);

% Convert the first image to YIQ space
YIQ1 = yuv2yiq(YUV1);

% Display the original RGB formatted frame
figure;
imshow(RGB1);
title('Original Image (RGB formatted)');

% Display the original frames' Y component
figure;
imshow(uint8(YUV1(:,:,1)));
title('Y component of the original image');

% Frequency Spectrum of the Y component of the first frame
Y1=YIQ1(:,:,1);
Y1=Y1';
Y1_raster=Y1(:);

figure;
spectrum(double(Y1_raster),1024,0,'',fs*10^6);
title('Spectrum - Y component of the first frame');

% Frequency Spectrum of the I component of the first frame
I1=YIQ1(:,:,2);
I1=I1';
I1_raster=I1(:);

figure;
spectrum(double(I1_raster),1024,0,'',fs*10^6);
title('Spectrum - I component of the first frame');

% Frequency Spectrum of the Q component of first frame
Q1=YIQ1(:,:,3);
Q1=Q1';
Q1_raster=Q1(:);
 
figure;
spectrum(double(Q1_raster),1024,0,'',fs*10^6);
title('Spectrum - Q component of the first frame');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%% MULTIPLEXING THE YIQ SIGNAL TO COMPOSITE %%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Form the coefficients for low-pass and band pass filters
% A butterworth filter of order 4 is used to construct the low-pass and band-pass filters
coef=4;
[b_lp0,a_lp0]=butter(coef,(0.75)/(fs/2)); % The low-pass filter used instead of the comb filter
[b_lp1,a_lp1]=butter(coef,(1)/(fs/2)); % Low-pass filter-1 for Y component
[b_lp2,a_lp2]=butter(coef,(0.4)/(fs/2)); % Low-pass filter-2 for I component
[b_lp3,a_lp3]=butter(coef,(0.3)/(fs/2));  % Low-pass filter-3 for Q component

[b_bp,a_bp]=butter(coef,[(0.7)/(fs/2), (1.3)/(fs/2)]); % Band-pass filter for QAM-I&Q components

%Low-pass filter the Y,I and Q components
Y_lp=filter(b_lp1,a_lp1,double(Y1_raster));
I_lp=filter(b_lp2,a_lp2,double(I1_raster));
Q_lp=filter(b_lp3,a_lp3,double(Q1_raster));
% 
%QAM modulation of low-pass filtered I and Q components
fc=1.05; % the carrier freq is chosen as 0.97 MHz
Amp=1;

% QAM_IQ = modulate(I_lp,fc*10^6,fs*10^6,'qam',Q_lp) ;

t = (0:352*288-1)*(1/(30*352*288));
cos_qam = Amp * cos(2*pi*fc*10^6*t');
sin_qam = Amp * sin(2*pi*fc*10^6*t');

QAM_IQ = I_lp.*cos_qam + Q_lp.*sin_qam;

figure;
spectrum(QAM_IQ,1024,0,'',fs*10^6);
title('Spectrum of QAM I+Q');

% Band-pass filtering of the QAM I+Q
QAM_IQ_bp=filter(b_bp,a_bp,QAM_IQ);
figure;
spectrum(QAM_IQ_bp,1024,0,'',fs*10^6);
title('Band-pass filtered Spectrum of QAM I+Q');
%form the composite video
C = Y_lp + QAM_IQ_bp;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%% DEMULTIPLEXING THE COMPOSITE SIGNAL TO YIQ %%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Y_rec = filter(b_lp0,a_lp0,C) ;
C2 = C-Y_rec;

Y_rec = (reshape(Y_rec,352,288));
Y_rec=Y_rec';

figure;
imshow(uint8(Y_rec));
title('Recovered Y component');

%Recover the QAM I+Q 

% [I_dqam Q_dqam] = demod(C2, fc*10^6,fs*10^6,'qam');
I_dqam = C2 .* (2*Amp*cos_qam);
Q_dqam = C2 .* (2*Amp*sin_qam);

%%%%%%%%%%%%%%%%%%% I component %%%%%%%%%%%%%%%%%%%%%%%%
I_rec = filter(b_lp2,a_lp2,I_dqam);

figure;
spectrum(double(I_rec),1024,0,'',fs*10^6);
title('Spectrum of the recovered I component');

I_rec = (reshape(I_rec,352,288));
I_rec=I_rec';

%%%%%%%%%%%%%%%%%%% Q component %%%%%%%%%%%%%%%%%%%%%%%%
Q_rec = filter(b_lp3,a_lp3,Q_dqam);

figure;
spectrum(double(Q_rec),1024,0,'',fs*10^6);
title('Spectrum of the recovered Q component');

Q_rec = (reshape(Q_rec,352,288));
Q_rec = Q_rec';
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

YIQ_rec(:,:,1) = Y_rec;
YIQ_rec(:,:,2) = I_rec;
YIQ_rec(:,:,3) = Q_rec;

RGB_rec=yiq2rgb(YIQ_rec);

figure;
imshow(RGB_rec);
title('Recovered color image');



