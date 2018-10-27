% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function res=kiks_server_request(id)
global KIKS_SPDC KIKS_GUI_HDL KIKS_KIKSNET_PING KIKS_KIKSNET_PING_COUNT KIKS_NET_BUFSIZ KIKS_FID KIKS_ROBOT_MATRIX KIKS_MMPERPIXEL KIKS_KIKSNET_COMMAND KIKS_KIKSNET_REPLY;

res='';
KIKS_KIKSNET_REPLY='';
if ~isempty(KIKS_KIKSNET_COMMAND) KIKS_KIKSNET_COMMAND = ['CMD:' KIKS_KIKSNET_COMMAND]; end;
if KIKS_FID>-1 
    tic;
    req=sprintf('R 1 %.3f %.3f %.3f %.3f %.3f %.3f %.3f %s',KIKS_ROBOT_MATRIX(id,1,1),KIKS_ROBOT_MATRIX(id,1,2),KIKS_ROBOT_MATRIX(id,1,3),KIKS_ROBOT_MATRIX(id,6,7)*KIKS_SPDC,KIKS_ROBOT_MATRIX(id,6,8)*KIKS_SPDC,KIKS_ROBOT_MATRIX(id,2,2),KIKS_ROBOT_MATRIX(id,2,1),KIKS_KIKSNET_COMMAND);
    kiks_transmit_string(KIKS_FID,req); 
    res=kiks_recieve_string(KIKS_FID);
    if ~isempty(KIKS_KIKSNET_COMMAND)
        KIKS_KIKSNET_REPLY = deblank(kiks_recieve_string(KIKS_FID));
    end;
    KIKS_KIKSNET_PING=KIKS_KIKSNET_PING+toc; KIKS_KIKSNET_PING_COUNT=KIKS_KIKSNET_PING_COUNT+1;
    if (isempty(KIKS_KIKSNET_PING_COUNT) | KIKS_KIKSNET_PING_COUNT>10)
        h=findobj(KIKS_GUI_HDL,'tag','t_kiksnet_text_ping');
        if ~isempty(KIKS_KIKSNET_PING_COUNT)
            t=floor((KIKS_KIKSNET_PING*1000)/KIKS_KIKSNET_PING_COUNT);
        else
            t=floor((KIKS_KIKSNET_PING*1000));
        end;
        if t>=10 set(h,'String',sprintf('%d ms',t)); else set(h,'String','<10 ms'); end;
        KIKS_KIKSNET_PING=0;
        KIKS_KIKSNET_PING_COUNT=0;
    end;
end;
KIKS_KIKSNET_COMMAND='';