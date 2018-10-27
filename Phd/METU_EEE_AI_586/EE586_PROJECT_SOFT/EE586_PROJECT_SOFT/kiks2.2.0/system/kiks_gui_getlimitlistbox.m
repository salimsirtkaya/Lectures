% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_getlimitlistbox
global KIKS_GUI_HDL KIKS_INT_LIMIT KIKS_INT_LIST;

h=findobj(KIKS_GUI_HDL,'Tag','limit_popup');
nr=get(h,'Value');
KIKS_INT_LIMIT=KIKS_INT_LIST(nr);