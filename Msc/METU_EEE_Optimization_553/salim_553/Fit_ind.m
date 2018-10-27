function [fitness]=Fit_ind(member)
global x0;
A=[0 1 0 0 0; 0 -16 -9.8178 0 623.16; 0 0 0 1 0; -8.7478 0.15147 -3.2745 -0.02575 0; 0 -144740 0 0 -475];
B=[0 0 0 0 250]';
C=eye(5);
D=[0 0 0 0 0]';
mult=[2^5 2^4 2^3 2^2 2 1];
Kd=[100+sum(member(1:6).*mult),-30+sum(member(7:12).*mult),sum(member(13:18).*mult),-10+sum(member(19:24).*mult),0];
%%%%%%%biaslar ve eksiler!!!

%Kd=[Kd,0];
A_fed=A-B*Kd;
B_fed=zeros(5,1);
sys_fed=ss(A_fed,B_fed,C,D);
t=0:0.01:20;
[y,t,x]=initial(sys_fed,x0,t);
%fitness=1/(sum(abs(x(7001:8001,1)))/max(abs(x(:,1)))+sum(abs(x(7001:8001,2)))/max(abs(x(:,2)))+sum(abs(x(7001:8001,3)))/max(abs(x(:,3)))+sum(abs(x(7001:8001,4)))/max(abs(x(:,4)))+sum(abs(x(7001:8001,5)))/max(abs(x(:,5))));
fitness=1/sum(sum(abs(x(1001:2001,:))));