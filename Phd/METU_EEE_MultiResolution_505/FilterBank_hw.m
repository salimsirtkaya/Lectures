%% EE505 homework - FilterBanks
clear all;
close all;
N=512;

for i=1:N
    PSD_x(i) = 1 + cos(2*pi*((i-1)-N/2)/N);
end

figure;
plot(PSD_x);

PSD_X = repmat(PSD_x,1,31);

figure;
plot(PSD_X);

H0_window = [zeros(1,N/2-N/2/8) ones(1,N/8) zeros(1,N/2-N/2/8)];

figure;
plot(H0_window);

H0_W = repmat(H0_window,1,31);

PSD_X0 = PSD_X.*H0_W;

figure;
plot(PSD_X0);




