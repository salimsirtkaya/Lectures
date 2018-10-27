% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function fid=kiks_server_connect
global KIKS_KIKSNET_PROTOCOL_VERSION KIKS_GUI_COLOR KIKS_KIKSNET_COMMAND KIKS_KIKSNET_PING_COUNT KIKS_KIKSNET_PING KIKS_REMOTE_ARRAY KIKS_ROUNDOBJARRAY KIKS_LIGHTARRAY KIKS_BALLARRAY KIKS_CALLSIGNS KIKS_VISUALIZE KIKS_ROBOT_MATRIX KIKS_ARENA_MASK KIKS_RBTARRAY KIKS_WALL_WIDTH KIKS_ARENA_MASK_ORIG KIKS_ARENA_COLORMASK_ORIG KIKS_NET_BUFSIZ KIKS_ACC_CELL KIKS_GUI_HDL KIKS_FID;
h=findobj(KIKS_GUI_HDL,'tag','kiksnet_edit');
server=get(h,'string');
if isempty(server)
    server='localhost:20002';
end;
port=[];
colonPos = find(server==':');
if ~isempty(colonPos)
    port = sscanf(server(colonPos+1:end),'%d');
    server=server(1:colonPos-1);
end;
if isempty(port) port=20002; end;

if KIKS_FID>0 kiks_server_disconnect; end;
KIKS_REMOTE_ARRAY=[];
KIKS_KIKSNET_COMMAND = '';
try
    KIKS_FID = tcpip_open(server,port);
    sendstr=uint8([0 KIKS_KIKSNET_PROTOCOL_VERSION 0]);
    while ~isempty(sendstr) & tcpip_status(KIKS_FID)~=0
        sendstr=tcpip_write(KIKS_FID,sendstr);
    end;
    res=kiks_recieve_string(KIKS_FID);
    if strcmp(res,'OK')==0
        KIKS_FID=-1;
        kiks_status(res);
    end;
catch
    KIKS_FID=-1;
end;

if KIKS_FID==-1
    kiks_error(sprintf('Could not connect to KiKSnet server %s:%d',server,port));
else      
    KIKS_KIKSNET_PING=0;
    KIKS_KIKSNET_PING_COUNT=[];
    set(h,'enable','off');
    vfk='n/a';
    lic=0;
    H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_btn');
    set(H,'String','disconnect from server'); 
    set(H,'Callback','kiks_server_disconnect;'); 
    H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_edit');
    set(H,'Enable','off');
    H=findobj(KIKS_GUI_HDL,'Tag','kiksnet_edit');
    set(H,'Enable','off'); 
    h=findobj(KIKS_GUI_HDL,'tag','loadarena');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','savearena');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','addobj');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','deleteobj');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','addkhep');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','deletekhep');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','loadarena');
    set(h,'Enable','off'); 
    %    h=findobj(KIKS_GUI_HDL,'tag','simulate_popup');
    %    set(h,'Enable','off'); 
    h=findobj(KIKS_GUI_HDL,'tag','kiksnet_server_btn');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','arena_reset');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','arena_checkpoint');
    set(h,'Enable','off');
    h=findobj(KIKS_GUI_HDL,'Tag','timescale_popup');
    set(h,'String',KIKS_ACC_CELL);
    set(h,'Value',1);
    set(h,'Visible','off');
    kiks_gui_gettimescale;
    h=findobj(KIKS_GUI_HDL,'Tag','speed_target');
    set(h,'String',KIKS_ACC_CELL);
    set(h,'Value',100);
    kiks_gui_gettimescale;
    set(h,'Visible','off');
    h=findobj(KIKS_GUI_HDL,'Tag','limit_popup');
    set(h,'Value',8);
    kiks_gui_getlimitlistbox;
    set(h,'Visible','off');
    h=findobj(KIKS_GUI_HDL,'Tag','stat_popup');
    set(h,'Visible','off');
    h=findobj(KIKS_GUI_HDL,'Tag','acceleration_method');
    set(h,'Visible','off');
    
    % Enable KiKSnet GUI stuff
    h=findobj(KIKS_GUI_HDL,'Tag','text_time_mode');
    set(h,'Visible','off');
    h=findobj(KIKS_GUI_HDL,'Tag','text_time_acceleration_method');
    set(h,'String','KiKSnet server');
    h=findobj(KIKS_GUI_HDL,'Tag','text_movement_limit');
    set(h,'String','client-server roundtrip time');
    h=findobj(KIKS_GUI_HDL,'Tag','text_interpolation_limit');
    set(h,'Visible','off');
    
    h=findobj(KIKS_GUI_HDL,'Tag','t_kiksnet_text_server');
    set(h,'String',server);
    h=findobj(KIKS_GUI_HDL);
    [gui_objs,tmp]=size(h);
    for i=1:gui_objs
        tag = get(h(i),'Tag');
        if strncmp(tag,'t_kiksnet_',10)
            set(h(i),'Visible','on');
        end;
    end;
    
    try
        load kiks_reginfo;
    catch
        cde='UNREGISTERED';
    end;
    
    kiks_transmit_string(KIKS_FID,sprintf('%s %s %d',cde,vfk,lic));
    tic;
    res=kiks_recieve_string(KIKS_FID);
    if strcmp(res,'OK')
        % OK, server accepted our serial number. Let's recieve arena and colormask.
        t=toc-0.1; % ping time, can't detect less than 10 ms. Connection always takes at least 0.1 second (delay built into server).
        compressed_colormask=kiks_recieve_var(KIKS_FID,'uint16','downloading arena...');
        colormask = kiks_expandmatrix(compressed_colormask);
        arena=(colormask>0);
        kiks_arena(arena,colormask,1);
        kiks_transmit_string(KIKS_FID,sprintf('C'));
        res=kiks_recieve_string(KIKS_FID);
        
        callsign=sscanf(res,'C %s');
        h=findobj(KIKS_GUI_HDL,'tag','radioid');
        set(h,'string',callsign);
        kiks_status(sprintf('Connected to %s:%d.',server,port));          
    else
        kiks_status(sprintf('Error: Connection with %s:%d refused.\nServer replied: ''%s''',server,port,res));
        kiks_server_disconnect;
    end;
end;
fid=KIKS_FID;