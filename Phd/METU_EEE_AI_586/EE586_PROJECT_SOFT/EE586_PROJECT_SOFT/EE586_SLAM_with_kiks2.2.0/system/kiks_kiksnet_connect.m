% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function fid=kiksnet_connect;
global KIKS_KIKSNET_PROTOCOL_VERSION KIKS_KIKSNET_MONITORING KIKS_KIKSNET_COMMAND KIKS_GUI_HDL KIKS_BALLDATA KIKS_BALLARRAY KIKS_LIGHTARRAY KIKS_RBTARRAY KIKS_GUI_STATUS KIKS_NET_PASSWORD KIKS_FID KIKS_NET_BUFSIZ KIKS_ARENA_MASK_ORIG KIKS_ARENA_COLORMASK_ORIG;

KIKS_KIKSNET_COMMAND = '';
h=findobj(KIKS_GUI_HDL,'tag','kiksnet_edit');
server=deblank(get(h,'string'));
port=[];
if isempty(server)
    server='localhost:20002';
end;
colonPos = find(server==':');
if ~isempty(colonPos)
    port = sscanf(server(colonPos+1:end),'%d');
    server=server(1:colonPos-1);
end;
if isempty(port) port=20002; end;
if strcmp(server,'127.0.0.1')
    server='localhost';
end;

if KIKS_FID>0 kiks_kiksnet_disconnect; end;
kiks_status('<KiKSnet> connecting to server');

% delete robots
while size(KIKS_RBTARRAY>0)
    kiks_delete_robot(KIKS_RBTARRAY(1));
end;

% delete lights
%while size(KIKS_LIGHTARRAY>0)
%    kiks_delete_object(KIKS_LIGHTARRAY(1),1);
%end;
% delete balls
%while size(KIKS_BALLARRAY>0)
%    kiks_delete_object(KIKS_BALLARRAY(1),2+KIKS_BALLDATA(KIKS_BALLARRAY(1),5));
%end;

set(KIKS_GUI_HDL,'name','KiKSnet');
H=findobj(KIKS_GUI_HDL,'type','uicontrol');
KIKS_GUI_STATUS=get(H,'Visible');
H=findobj(KIKS_GUI_HDL,'style','pushbutton');
set(H,'Visible','off');
H=findobj(KIKS_GUI_HDL,'style','edit');
set(H,'Visible','off');
H=findobj(KIKS_GUI_HDL,'style','popupmenu');
set(H,'Visible','off');
H=findobj(KIKS_GUI_HDL,'style','text');
set(H,'Visible','off');
H=findobj(KIKS_GUI_HDL,'style','frame');
set(H,'Visible','off');
H=findobj(KIKS_GUI_HDL,'style','checkbox');
set(H,'Visible','off');
H=findobj(KIKS_GUI_HDL,'style','slider');
set(H,'Visible','off');
H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_server_btn');
set(H,'String','disconnect'); 
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_text');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','toggle2dvis');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','webbtn');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','licbtn');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','version');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','reginfo');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','status_dummy');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','togglelog');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','status');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','kiks_matlab_command');
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_frame');
set(H,'Position',[3 96 143 470]);
set(H,'Visible','on');
H=findobj(KIKS_GUI_HDL,'Tag','t_kiksnetserver_text_server');
set(H,'string',server);
h=findobj(KIKS_GUI_HDL);
[gui_objs,tmp]=size(h);
for i=1:gui_objs
    tag = get(h(i),'Tag');
    if strncmp(tag,'t_kiksnetserver_',16)
        set(h(i),'Visible','on');
    end;
end;

drawnow;

%arena=kiks_compressmatrix(double(KIKS_ARENA_MASK_ORIG));
colormask=kiks_compressmatrix(double(KIKS_ARENA_COLORMASK_ORIG));

KIKS_FID = tcpip_open(server,port);
if (KIKS_FID==-1 & strcmp(server,'localhost')) % start a local server if none is running
    try
        if isempty(KIKS_NET_PASSWORD)
            kiks_gui_kiksnet_password('Set administrator password');
        end;
        dos(sprintf('%sKiKSnet\\kiksnet.exe %s &',kiks_getpath,KIKS_NET_PASSWORD));
        tries=0;
        while (KIKS_FID==-1 & tries<10) % it might take a few seconds to start up KiKSnet.exe, so we try to connect for 10 seconds.
            KIKS_FID = tcpip_open(server,port);
            tries=tries+1;
            if KIKS_FID==-1
                pause(1);
            end;
        end;
    catch
        kiks_kiksnet_disconnect;
        kiks_status('Error: couldn''t start kiksnet.exe');
        return;
    end;
end;

if KIKS_FID==-1
    kiks_status(sprintf('<KiKSnet> error: could not connect to KiKSnet server %s:%d',server,port));
else    
    sendstr=uint8([0 KIKS_KIKSNET_PROTOCOL_VERSION 0]);
    while ~isempty(sendstr) & tcpip_status(KIKS_FID)~=0
        sendstr=tcpip_write(KIKS_FID,sendstr);
    end;
    res=kiks_recieve_string(KIKS_FID);
    if strcmp(res,'OK')==0
        KIKS_FID=-1;
        kiks_status(['<KiKSnet> error: ' res]);
    else    
        vfk='000000000';
        lic=-Inf;
        
        t0=clock;
        if isempty(KIKS_NET_PASSWORD)
            KIKS_NET_PASSWORD='[empty_password]';
        end;   
        cde=sprintf('%s',KIKS_NET_PASSWORD);
        kiks_transmit_string(KIKS_FID,sprintf('%s %s %d',cde,vfk,lic));
        res=kiks_recieve_string(KIKS_FID);
        
        if ~strcmp(res,'OK') % oops, try connecting with a password
            tcpip_close(KIKS_FID); % silent disconnection
            kiks_gui_kiksnet_password('Enter KiKSnet password');
            if isempty(KIKS_NET_PASSWORD)
                KIKS_NET_PASSWORD='[empty_password]';
            end;   
            KIKS_FID = tcpip_open(server,port); % reconnect
            sendstr=uint8([0 KIKS_KIKSNET_PROTOCOL_VERSION 0]);
            while ~isempty(sendstr) & tcpip_status(KIKS_FID)~=0
                sendstr=tcpip_write(KIKS_FID,sendstr);
            end;
            res=kiks_recieve_string(KIKS_FID);
            
            cde=sprintf('%s',KIKS_NET_PASSWORD);
            kiks_transmit_string(KIKS_FID,sprintf('%s %s %d',cde,vfk,lic));
            res=kiks_recieve_string(KIKS_FID);
        end;
        
        if strcmp(res,'OK')
            % OK, server accepted our serial number.
            kiks_status('<KiKSnet> setting up arena');
            kiks_transmit_var(KIKS_FID,colormask);
            
            % read arena and colormask from server
            compressed_colormask=kiks_recieve_var(KIKS_FID,'uint16','<KiKSnet> downloading arena...');
            colormask = kiks_expandmatrix(compressed_colormask);
            arena=(colormask>0);
            KIKS_KIKSNET_MONITORING=1;
            kiks_arena(arena,colormask,1);        
        else
            kiks_status(['<KiKSnet> error: ' res]);
            kiks_kiksnet_disconnect;
        end;
    end;
end;
fid=KIKS_FID;