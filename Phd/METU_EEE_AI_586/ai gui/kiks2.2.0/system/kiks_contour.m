% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res=kiks_contour(m)

res = bwmorph(m,'remove');
%b=filter2([0 1/4 0; 1/4 -1 1/4; 0 1/4 0],m);
%res=(b<0);

%inpolygon
