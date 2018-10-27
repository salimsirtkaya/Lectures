%%%%%%%%%%%%%%%%%  EE603 SPECTRAL ESTIMATION  %%%%%%%%%%%%%%%%%%

% TakeHome Exam 
% Problem 6-12  Comparison of Spatial Spectral Estimators
%%% Part a %%%%
close all;
clear all;

theta=[0 15];
P=[1 1;1 1];
N=100;
sig2=1;
M=10;
d=0.5;
L=2;
% Generate the ULA data

for k=1:50
    Y(k,:,:)=uladata(theta,P,N,sig2,M,d);    
end

for g=1:2880
    time(g)=(g-1440)/16;
end

figure;
hold;
TITLE('DOA estimate with Capon method');
XLABEL('x degrees');
for k=1:50
    Y1(:,:)=Y(k,:,:);
    % estimate the DOAs with Capon method
    phi(k,:,:)=capon_sp(Y1,2880,d);  
    plot(time,phi(k,:,:));
   
    % estimate the DOAs with Root MUSIC method
    doa_rm(k,:,:)=2880*(root_music_doa(Y1,L,d)+90)/180;
    
    % estimate the DOAs with ESPRIT
    doa_esprt(k,:,:)=2880*(esprit_doa(Y1,L,d)+90)/180;
end

for i=1:2880
    DUMMY1(i)=0;
    DUMMY2(i)=0;
end

%plot root music results
for k=1:50
    DUMMY1(round(doa_rm(k,1)))=1;
    DUMMY1(round(doa_rm(k,2)))=1;       
end

figure;
plot(time,DUMMY1);
TITLE('DOA estimate with Root MUSIC method');
XLABEL('x degrees');

%plot root music results
for k=1:50
    DUMMY2(round(doa_esprt(k,1)))=1;
    DUMMY2(round(doa_esprt(k,2)))=1;       
end

figure;
plot(time,DUMMY2);
TITLE('DOA estimate with ESPRIT method');
XLABEL('x degrees');
