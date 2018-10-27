% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_getstatlistbox
global KIKS_GUI_HDL KIKS_STAT_LIST KIKS_MAXMOVLIMIT;

h=findobj(KIKS_GUI_HDL,'Tag','stat_popup');
nr=get(h,'Value');
KIKS_MAXMOVLIMIT=KIKS_STAT_LIST(nr);
if(KIKS_MAXMOVLIMIT>0) 
    KIKS_MAXMOVLIMIT=1/KIKS_MAXMOVLIMIT;
end;
