% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_gettimescale
global KIKS_WALL_CLOCK KIKS_GUI_HDL KIKS_TIMESCALE KIKS_ACC_LIST KIKS_updatelmp;

KIKS_updatelmp=-1;

h=findobj(KIKS_GUI_HDL,'Tag','timescale_popup');
nr=get(h,'Value');
KIKS_TIMESCALE=KIKS_ACC_LIST(nr);
if(KIKS_TIMESCALE>0)
    % disable movement limit list box
    H=findobj(KIKS_GUI_HDL,'Tag','stat_popup');
    set(H,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'Tag','compspeed_popup');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','acceleration_method');
    set(h,'value',2);
    kiks_gui_getaccmethod;
    set(h,'enable','off');
    KIKS_WALL_CLOCK=[];
else
    % enable movement limit list box
    H=findobj(KIKS_GUI_HDL,'Tag','stat_popup');
    set(H,'Enable','on');   
    h=findobj(KIKS_GUI_HDL,'Tag','compspeed_popup');
    set(h,'Enable','on');
    h=findobj(KIKS_GUI_HDL,'tag','acceleration_method');
    set(h,'enable','on');
    kiks_gui_getaccmethod;
    KIKS_WALL_CLOCK=[];
end;
