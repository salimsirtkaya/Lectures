% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res2=kiks_expandmatrix(vec)
vec=double(vec)';
m=vec(1);
n=vec(2);
[tmp,sz]=size(vec);
points=round((sz-2)/3);
start=3;
i=vec(start:start+points-1)';
start=start+points;
j=vec(start:start+points-1)';
start=start+points;
s=vec(start:start+points-1)';

res2=full(sparse(i,j,s,m,n)');