% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function ret=kiksnet_disconnect
global KIKS_KIKSNET_MONITORING KIKS_FID KIKS_GUI_STATUS KIKS_GUI_HDL KIKSNET_ACTIVE
KIKSNET_ACTIVE=[];
KIKS_KIKSNET_MONITORING=[];
if KIKS_FID>=0
   tcpip_close(KIKS_FID);
end;
KIKS_FID=-1;
delete(findobj(KIKS_GUI_HDL,'tag','kiksnet_clientstats'));
set(KIKS_GUI_HDL,'name','KiKS');
H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_server_btn');
set(H,'String','administrate KiKSnet server');
H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_frame');
set(H,'Position',[3 472 143 94]);
H=findobj(KIKS_GUI_HDL,'type','uicontrol');
for i=1:size(H)
    set(H(i),'Visible',char(KIKS_GUI_STATUS(i)));
end;
h=findobj(KIKS_GUI_HDL);
[gui_objs,tmp]=size(h);
for i=1:gui_objs
    tag = get(h(i),'Tag');
    if strncmp(tag,'t_kiksnetserver_',16)
        set(h(i),'Visible','off');
    end;
end;

kiks_delete_remote;
kiks_spawn_robot;
drawnow;
kiks_status('<KiKSnet> Disconnected from KiKSnet server.');