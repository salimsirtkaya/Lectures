% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function ret=kiks_server_disconnect
global KIKS_RBTARRAY KIKS_FID KIKS_GUI_HDL
if KIKS_FID>=0
    tcpip_close(KIKS_FID);
    kiks_status('disconnected from KiKSnet server.');
end;
h=findobj(KIKS_GUI_HDL,'tag','kiksnet_server_btn');
set(h,'Enable','on'); 
H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_btn');
set(h,'Enable','on');
set(H,'String','connect to KiKSnet server'); 
set(H,'Callback','kiks_server_connect;'); 
H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_edit');
set(H,'Enable','on');
H=findobj(KIKS_GUI_HDL,'Tag','callsign');
set(H,'Enable','on');
h=findobj(KIKS_GUI_HDL,'Tag','timescale_popup');
set(h,'Visible','on');
h=findobj(KIKS_GUI_HDL,'Tag','speed_target');
set(h,'Visible','on');
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
h=findobj(KIKS_GUI_HDL,'tag','radioid');
set(h,'string','n/a');
h=findobj(KIKS_GUI_HDL,'Tag','limit_popup');
set(h,'Visible','on'); 
h=findobj(KIKS_GUI_HDL,'tag','simulate_popup');
set(h,'Enable','on'); 
h=findobj(KIKS_GUI_HDL,'tag','arena_reset');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'tag','arena_checkpoint');
set(h,'Enable','on');
h=findobj(KIKS_GUI_HDL,'Tag','stat_popup');
set(h,'Visible','on');
h=findobj(KIKS_GUI_HDL,'Tag','acceleration_method');
set(h,'Visible','on');

% Disable KiKSnet GUI stuff
h=findobj(KIKS_GUI_HDL,'Tag','text_time_mode');
set(h,'Visible','on');
h=findobj(KIKS_GUI_HDL,'Tag','text_time_acceleration_method');
set(h,'String','time acceleration method');
h=findobj(KIKS_GUI_HDL,'Tag','text_movement_limit');
set(h,'String','movement limit');
h=findobj(KIKS_GUI_HDL,'Tag','text_interpolation_limit');
set(h,'Visible','on');

h=findobj(KIKS_GUI_HDL);
[gui_objs,tmp]=size(h);
for i=1:gui_objs
    tag = get(h(i),'Tag');
    if strncmp(tag,'t_kiksnet_',10)
        set(h(i),'Visible','off');
    end;
end;
h=findobj(KIKS_GUI_HDL,'tag','t_kiksnet_text_ping');
set(h,'String','?');

kiks_delete_remote;
KIKS_FID=-1;
if isempty(KIKS_RBTARRAY)
    kiks_spawn_robot;
end;
