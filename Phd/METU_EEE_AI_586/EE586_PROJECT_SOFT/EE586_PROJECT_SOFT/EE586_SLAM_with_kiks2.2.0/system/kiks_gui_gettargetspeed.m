% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_gettargetspeed
global KIKS_COMPUTER_SPEED KIKS_COMPUTER_SPEED_SIM KIKS_WALL_CLOCK KIKS_GUI_HDL KIKS_TIMESCALE KIKS_ACC_LIST KIKS_updatelmp;

h=findobj(KIKS_GUI_HDL,'Tag','speed_target');
nr=get(h,'Value');

h=findobj(KIKS_GUI_HDL,'Tag','acceleration_method');
str=get(h,'string');

str{2}=sprintf('target speed: %.0f%%',nr);
set(h,'string',str);
KIKS_COMPUTER_SPEED_SIM = KIKS_COMPUTER_SPEED*(nr/100);