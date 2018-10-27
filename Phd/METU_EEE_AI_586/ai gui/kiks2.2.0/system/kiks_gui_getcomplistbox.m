% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_getcomplistbox
global KIKS_GUI_HDL KIKS_COMP_LIST KIKS_COMPUTER_SPEED_SIM;

h=findobj(KIKS_GUI_HDL,'Tag','compspeed_popup');
nr=get(h,'Value');
KIKS_COMPUTER_SPEED_SIM=KIKS_COMP_LIST(nr);