% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_setcomplistbox(ix)
global KIKS_GUI_HDL KIKS_COMP_CELL KIKS_COMP_LIST KIKS_PROX_ACCURACY;

h=findobj(KIKS_GUI_HDL,'Tag','compspeed_popup');

set(h,'String',KIKS_COMP_CELL);
set(h,'Value',ix);