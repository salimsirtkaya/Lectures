% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------
function kiks_kiksnet(password);
global KIKS_GUI_KIKSNET_CLIENTS_CNT KIKS_GUI_HDL KIKS_MOVLOCK KIKS_OBJECT_SMALLBALL_RADIUS KIKS_OBJECT_BALL_RADIUS KIKS_LIGHTDATA KIKS_LIGHTARRAY KIKS_BALLDATA KIKS_BALLARRAY KIKSNET_ACTIVE KIKS_GUI_HDL KIKS_REMOTE_ARRAY_NEW KIKS_MMPERPIXEL KIKS_NET_PASSWORD KIKS_NET_BUFSIZ KIKS_FID KIKS_WALL_WIDTH KIKS_WALL_RENDER;

if nargin==1
    KIKS_NET_PASSWORD=password;
    if isempty(KIKS_NET_PASSWORD)
        KIKS_NET_PASSWORD='[empty_password]';
    end;
else
    KIKS_NET_PASSWORD=[];
end;

KIKS_NET_BUFSIZ=4096;
KIKS_GUI_KIKSNET_CLIENTS_CNT=0;

if(~isempty(KIKSNET_ACTIVE))
    KIKSNET_ACTIVE=[];
    return;
end;

KIKSNET_ACTIVE=1;

connection_result=kiks_kiksnet_connect;
if connection_result==-1
    kiks_kiksnet_disconnect;
    return;
end;
t0=clock;
l=0;
seconds=0;
kiks_status('Session control transferred to KiKS.',1);

while(KIKSNET_ACTIVE & tcpip_status(KIKS_FID)~=0)
    l=l+1;
    pause(0.04);
    current_seconds = round(etime(clock,t0));
    if round(etime(clock,t0))>seconds
        fixed_l = l;
        l=0;
        seconds=current_seconds;
        %kiks_status(sprintf('- monitoring KiKSnet server for %d seconds @ %d updates per second -',seconds,fixed_l));
    end;
    kiks_transmit_string(KIKS_FID,'G');
    res=kiks_recieve_string(KIKS_FID);
    
    KIKS_REMOTE_ARRAY_NEW=sscanf(res(4:end),'%f');
    kiks_update_remote;
    objstr='';
    
    if mod(l,10)==0
        set(findobj(KIKS_GUI_HDL,'Tag','t_kiksnetserver_scrollup'),'Enable','on');
        set(findobj(KIKS_GUI_HDL,'Tag','t_kiksnetserver_scrolldown'),'Enable','on');        
        kiks_transmit_string(KIKS_FID,'S');
        res=kiks_recieve_string(KIKS_FID);
        num=sscanf(res(3:end),'%d');
        h=findobj(KIKS_GUI_HDL,'tag','t_kiksnetserver_text_clients');
        set(h,'string',sprintf('%d',num));
        if KIKS_GUI_KIKSNET_CLIENTS_CNT>=num
            KIKS_GUI_KIKSNET_CLIENTS_CNT=num-1;
        end;
        for i=1:num
            st=kiks_recieve_string(KIKS_FID);
            fields=findstr(st,';');
            id=st(1:fields(1)-1);
            ipfourbyte=str2num(st(fields(1)+1:fields(2)-1));
            ip=kiks_fourbyte2ip(ipfourbyte);
            cde=st(fields(2)+1:fields(3)-1);
            score=st(fields(3)+1:fields(4)-1);
            fld=i-KIKS_GUI_KIKSNET_CLIENTS_CNT;
            if fld>=1 & fld<=4
                kiks_gui_kiksnet_clientstats(fld,id,ip,cde,score);
            end;
        end;
        emptbeg=num-KIKS_GUI_KIKSNET_CLIENTS_CNT+1;
        for i=emptbeg:4
            kiks_gui_kiksnet_clientstats(i);
        end;
    end;
end;

kiks_status('Session control returned to Matlab.',1);
t1=etime(clock,t0);
kiks_kiksnet_disconnect;
