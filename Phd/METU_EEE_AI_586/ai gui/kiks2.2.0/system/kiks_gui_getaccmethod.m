% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_getaccmethod
global KIKS_WALL_CLOCK KIKS_GUI_HDL KIKS_TIMESCALE KIKS_ACC_LIST KIKS_updatelmp;

h=findobj(KIKS_GUI_HDL,'Tag','acceleration_method');
nr=get(h,'Value');

if(nr==1)
    % disable movement limit list box
    H=findobj(KIKS_GUI_HDL,'Tag','speed_target');
    set(H,'Enable','off');
    set(H,'Visible','off');
    H=findobj(KIKS_GUI_HDL,'Tag','compspeed_popup');
    set(H,'Enable','on');
    set(H,'Visible','on');
    kiks_gui_getcomplistbox;
else
    % enable movement limit list box
    H=findobj(KIKS_GUI_HDL,'Tag','speed_target');
    set(H,'Enable','on');
    set(H,'Visible','on');
    H=findobj(KIKS_GUI_HDL,'Tag','compspeed_popup');
    set(H,'Enable','off');
    set(H,'Visible','off');
    kiks_gui_gettargetspeed;
end;
