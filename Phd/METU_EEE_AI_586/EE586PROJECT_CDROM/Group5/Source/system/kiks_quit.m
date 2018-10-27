% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_quit(silent)
global KIKS_FOREGROUND KIKS_REGCODE KIKS_SESSIONACTIVE KIKS_2DVISUALIZE KiKS;
global KIKS_GUI_HDL KIKS_HISTORY_HDL KIKS_ARENA_HDL KIKS_MONITOR_WIN KIKS_MONITOR_ON;

if nargin<1
    silent=[];
end;

if KIKS_FOREGROUND
    KIKS_FOREGROUND=[];
end;
try
    [tmp,sz]=size(KIKS_MONITOR_ON);
    for i=1:sz
        if KIKS_MONITOR_ON(i)
            delete(KIKS_MONITOR_WIN(i));
        end;
    end;
catch
end;
try
    kiks_server_disconnect;
catch
end;
KIKS_SESSIONACTIVE=[];
if isempty(silent) & (strcmp(KIKS_REGCODE,'EVALUATION')==1)
    try;, web www.tstorm.seregister.php ;, catch, web www.tstorm.seregister.php;, end;
end;
a=findobj('name','KiKS');
b=findobj('name','KiKS log history');
c=findobj('name','KiKSnet');
clear global KIKS_*;
clear global KIKSNET_*;
delete(b);
delete(a);
delete(c);