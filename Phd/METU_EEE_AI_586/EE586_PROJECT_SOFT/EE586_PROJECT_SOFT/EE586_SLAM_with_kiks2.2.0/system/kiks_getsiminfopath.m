% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function k2path=kiks_getsiminfopath
kpath=which('kiks_siminfo_dist_fwd');
i=length(kpath);
while(kpath(i)~='\' & kpath(i)~='/') i=i-1; end;
k2path='';
for j=1:i
    k2path = [k2path kpath(j)];
end;