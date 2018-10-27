% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_halt
global KIKS_SIM_PAUSE KIKS_HALT_BOOL KIKS_GUI_HDL;

KIKS_HALT_BOOL=1;
KIKS_SIM_PAUSE=0;
h=findobj(KIKS_GUI_HDL,'tag','haltsim');
set(h,'Enable','off');
h=findobj(KIKS_GUI_HDL,'tag','haltsim');
set(h,'Enable','off');
h=findobj(KIKS_GUI_HDL,'tag','loadarena');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'tag','savearena');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'tag','addobj');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'tag','deleteobj');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'tag','addkhep');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'tag','deletekhep');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'tag','loadarena');
set(h,'Enable','on');
