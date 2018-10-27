% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_setstatlistbox(val)
global KIKS_GUI_HDL KIKS_STAT_CELL KIKS_STAT_LIST;
if nargin<1
    val=4;
else
    KIKS_MAXMOVLIMIT=KIKS_STAT_LIST(val);
end;

h=findobj(KIKS_GUI_HDL,'Tag','stat_popup');
set(h,'String',KIKS_STAT_CELL);
set(h,'Value',val);