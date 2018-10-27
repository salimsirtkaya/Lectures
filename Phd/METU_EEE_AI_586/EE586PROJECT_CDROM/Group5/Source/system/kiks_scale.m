% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% downsample a matrix
function ret=kiks_scale(a,rsz,csz)

[rows,cols]=size(a);

if [rows,cols]==[rsz,csz]
    ret=a;
    return;
end;

rscale=rows/rsz;
cscale=cols/csz;

rix=round([1:rscale:rows]);
cix=round([1:cscale:cols]);
ret=a(rix,cix);
