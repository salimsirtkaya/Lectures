% clear;
%close all;
a=332;
b=268;

A=fopen('D:\DERS\PHD\VIDEO\HOMEWORK_2\KLT_V_y.txt','r');
A1=fscanf(A,'%f\t',[a b]);
A1=A1';

for i=1:(b)
    A3(i,1:a)=A1(b-i+1,1:a);
end

fclose(A);
% A1 = IMROTATE(A1,-180,'nearest');

A=fopen('D:\DERS\PHD\VIDEO\HOMEWORK_2\KLT_V_x.txt','r');
A2=fscanf(A,'%f\t',[a b]);
A2=A2';

for i=1:(b)
    A4(i,1:a)=A2(b-i+1,1:a);
end


% A2 = IMROTATE(A2,-180,'nearest');

fclose(A);

% A=fopen('OPF.txt','r');
% A3=fscanf(A,'%f',[a b]);
% A3=A3';
% fclose(A);

for i=1:b/4
    for j=1:a/4
        A5(i,j)=A3(i*4-3,j*4-3);
        A6(i,j)=A4(i*4-3,j*4-3);
    end
end

figure,
quiver(A5,A6);

