% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_pausesim
global KIKS_SIM_STEP KIKS_SIM_PAUSE KIKS_GUI_HDL;

if (KIKS_SIM_PAUSE==0)
    KIKS_SIM_PAUSE=1;
    h=findobj(KIKS_GUI_HDL,'tag','pausesim');
    set(h,'string','>');
    h=findobj(KIKS_GUI_HDL,'tag','stepsim');
    set(h,'enable','on');
    KIKS_SIM_STEP=0;
else
    KIKS_SIM_PAUSE=0;
    h=findobj(KIKS_GUI_HDL,'tag','pausesim');
    set(h,'string','| |');    
    h=findobj(KIKS_GUI_HDL,'tag','stepsim');
    set(h,'enable','off');
    KIKS_SIM_STEP=0;
end;