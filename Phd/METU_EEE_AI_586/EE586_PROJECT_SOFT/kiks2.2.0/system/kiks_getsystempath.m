function k2path=kiks_getsystempath
kpath=which('kiks');
i=length(kpath);
while(kpath(i)~='\' & kpath(i)~='/') i=i-1; end;
k2path='';
for j=1:i
    k2path = [k2path kpath(j)];
end;

