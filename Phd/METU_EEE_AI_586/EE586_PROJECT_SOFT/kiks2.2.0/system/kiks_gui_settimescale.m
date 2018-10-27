% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_settimescale
global KIKS_GUI_HDL KIKS_ACC_LIMIT KIKS_ACC_CELL KIKS_TIMESCALE;

h=findobj(KIKS_GUI_HDL,'Tag','acc_popup');
set(h,'String',KIKS_ACC_CELL);
set(h,'Value',2);