% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_monitorclsreq
global KIKS_MONITOR_ON;

name=get(gcf,'Name');
num=abs(sscanf(name,'Port %d'));
KIKS_MONITOR_ON(num)=0;
delete(gcf);
