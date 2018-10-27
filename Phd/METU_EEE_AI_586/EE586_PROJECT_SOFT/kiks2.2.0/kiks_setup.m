function kiks_setup

% Update Matlab path
kpath=which('kiks_setup');
i=length(kpath);
while(kpath(i)~='\' & kpath(i)~='/') i=i-1; end;
k2path='';
for j=1:i
    k2path = [k2path kpath(j)];
end;
kikspath=k2path;
systempath=[k2path 'system'];
siminfopath=[k2path 'siminfo'];
kmatlabpath=[k2path 'kMatlab'];
turretspath=[k2path 'turrets'];
robotspath=[k2path 'robots'];
path(kmatlabpath,path);
path(siminfopath,path);
path(robotspath,path);
path(turretspath,path);
path(systempath,path);
path(kikspath,path);
t=clock;

kiks_calibrate;

pathtool;
msgbox('KiKS has updated the Matlab path settings and opened the Path Browser window. Be sure to save these settings for future sessions.');
path(path);