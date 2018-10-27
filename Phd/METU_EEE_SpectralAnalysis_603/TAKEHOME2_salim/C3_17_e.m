% TakeHome Exam 
% Problem 3-17  
close all;
clear all;
L=512;
phi1=0;
phi2=0;
no_real=50;

for n=1:L
    freq1(n)=2*(n-1)/L;
end

% The original spectrum of the sequence
H=zeros(1,L/2);

H(L/2*0.24)=50*pi;
H(L/2*0.26)=12.5*pi;


% Generation of the sequence
for k=1:50
    phi1=unifrnd(0,2*pi);
    phi2=unifrnd(0,2*pi);
    e=randn(L,1);
    for (n=1:L)
      y(k,n)=10*sin(0.24*pi*n+phi1)+5*sin(0.26*pi*n+phi2)+e(n);
    end
end

BT=bartlett(L/8);

for k=1:50
    phi(:,k)=periodogramse(y(k,:)',BT,L);
end

phi_ave=0;

for k=1:50
    phi_ave=phi_ave+phi(:,k);
end

phi_ave=phi_ave/10;

% Plot the PSD estimates of Modified Yule Walker method for M=n of order=4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',1.5);
TITLE('Exercise 3-17 Part e -->Periodogram Spectral Estimator with Bartlett of size N/8');
XLABEL('x pi');
YLABEL('Periodogram Spectral Estimator');
hold;
plot(freq1(1:L/2),phi_ave(1:L/2)/10,'b','LineWidth',2.5);
for k=1:50
    plot(freq1(1:L/2),(phi(1:L/2,k))/10,'k');
end

BT=bartlett(L/4);

for k=1:50
    phi(:,k)=periodogramse(y(k,:)',BT,L);
end

phi_ave=0;

for k=1:50
    phi_ave=phi_ave+phi(:,k);
end

phi_ave=phi_ave/10;

% Plot the PSD estimates of Modified Yule Walker method for M=n of order=4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',1.5);
TITLE('Exercise 3-17 Part e -->Periodogram Spectral Estimator with Bartlett of size N/4');
XLABEL('x pi');
YLABEL('Periodogram Spectral Estimator');
hold;
plot(freq1(1:L/2),phi_ave(1:L/2)/10,'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(phi(1:L/2,k))/10,'k');
end

BT=bartlett(L/2);

for k=1:50
    phi(:,k)=periodogramse(y(k,:)',BT,L);
end

phi_ave=0;

for k=1:50
    phi_ave=phi_ave+phi(:,k);
end

phi_ave=phi_ave/10;

% Plot the PSD estimates of Modified Yule Walker method for M=n of order=4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',1.5);
TITLE('Exercise 3-17 Part e -->Periodogram Spectral Estimator with Bartlett of size N/2');
XLABEL('x pi');
YLABEL('Periodogram Spectral Estimator');
hold;
plot(freq1(1:L/2),phi_ave(1:L/2)/10,'b','LineWidth',2.5);
for k=1:50
    plot(freq1(1:L/2),(phi(1:L/2,k))/10,'k');
end


BT=bartlett(L);

for k=1:50
    phi(:,k)=periodogramse(y(k,:)',BT,L);
end

phi_ave=0;

for k=1:50
    phi_ave=phi_ave+phi(:,k);
end

phi_ave=phi_ave/10;

% Plot the PSD estimates of Modified Yule Walker method for M=n of order=4,4
figure;
plot(freq1(1:L/2),H(1:L/2),'r','LineWidth',1.5);
TITLE('Exercise 3-17 Part e -->Periodogram Spectral Estimator with Bartlett of size N');
XLABEL('x pi');
YLABEL('Periodogram Spectral Estimator');
hold;
plot(freq1(1:L/2),phi_ave(1:L/2)/10,'b','LineWidth',2.5);
for k=1:50
    plot(freq1(1:L/2),(phi(1:L/2,k))/10,'k');
end
