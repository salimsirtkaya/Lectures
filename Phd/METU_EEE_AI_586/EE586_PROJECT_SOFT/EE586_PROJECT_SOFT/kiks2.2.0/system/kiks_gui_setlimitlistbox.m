% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_setlimitlistbox(val)
global KIKS_GUI_HDL KIKS_INT_LIMIT KIKS_INT_CELL;

if nargin<1
    val=4;
end;   

h=findobj(KIKS_GUI_HDL,'Tag','limit_popup');
set(h,'String',KIKS_INT_CELL);
set(h,'Value',val);