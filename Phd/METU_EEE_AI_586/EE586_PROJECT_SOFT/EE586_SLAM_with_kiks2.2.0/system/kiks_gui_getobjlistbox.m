% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function nr=kiks_gui_getobjlistbox
global KIKS_GUI_HDL KIKS_SENS_LIST KIKS_PROX_ACCURACY;

h=findobj(KIKS_GUI_HDL,'Tag','objpopup');
nr=get(h,'Value');