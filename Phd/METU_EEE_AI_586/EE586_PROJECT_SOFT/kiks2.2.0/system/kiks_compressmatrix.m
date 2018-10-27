% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res2=kiks_compressmatrix(A)

A=A';
[i,j,s]=find(A);
[m,n]=size(A);
res2=uint16([m n i' j' s']);