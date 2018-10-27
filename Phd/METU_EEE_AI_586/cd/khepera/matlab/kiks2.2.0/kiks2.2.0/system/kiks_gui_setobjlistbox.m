% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_setobjlistbox
global KIKS_GUI_HDL KIKS_OBJS_CELL KIKS_PROX_ACCURACY;

h=findobj(KIKS_GUI_HDL,'Tag','objpopup');
set(h,'String',KIKS_OBJS_CELL);
set(h,'Value',1);