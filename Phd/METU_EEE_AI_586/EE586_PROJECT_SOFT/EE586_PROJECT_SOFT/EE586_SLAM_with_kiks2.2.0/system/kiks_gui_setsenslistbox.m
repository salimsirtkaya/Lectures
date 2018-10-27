% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_setsenslistbox
global KIKS_GUI_HDL KIKS_SENS_CELL KIKS_PROX_ACCURACY;

h=findobj(KIKS_GUI_HDL,'Tag','proxsens_popup');
set(h,'String',KIKS_SENS_CELL);
set(h,'Value',4);