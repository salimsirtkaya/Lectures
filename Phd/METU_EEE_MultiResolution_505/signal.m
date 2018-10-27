%signal generation
clear all;
close all;
N = 512*8;
L = 8;

for i=1:N
    X(1,i)=i;
    X(2,i)=0.7*cos(5*pi*(i-N/2)/N)+1+abs(4*(i-N)/N)-abs(1.3*(i-N)/N);
end

for i=N/4:N/2
    X(2,i)=X(2,i)+0.87*sin(6*pi*(i-N/2)/N);
end

plot(X(2,:))

for k=1:N/L
    X_s(1,k)=k;
end

X_s(2,:) = decimate(X(2,:),L);

