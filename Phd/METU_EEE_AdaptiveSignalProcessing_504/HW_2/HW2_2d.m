%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #2, P.2d    %
% Salim Sirtkaya, 112434-6      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
close all;

c = unifrnd(zeros(2048,1),50*ones(2048,1));
v1 = unifrnd(-10*ones(2048,1),10*ones(2048,1));
v2 = unifrnd(-15*ones(2048,1),15*ones(2048,1));
v3 = unifrnd(-20*ones(2048,1),20*ones(2048,1));

m1 = c + v1;
m2 = c + v2;
m3 = c + v3; 