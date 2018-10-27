% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_getsenslistbox
global KIKS_GUI_HDL KIKS_SENS_LIST KIKS_PROX_ACCURACY;

h=findobj(KIKS_GUI_HDL,'Tag','proxsens_popup');
nr=get(h,'Value');
KIKS_PROX_ACCURACY=KIKS_SENS_LIST(nr);