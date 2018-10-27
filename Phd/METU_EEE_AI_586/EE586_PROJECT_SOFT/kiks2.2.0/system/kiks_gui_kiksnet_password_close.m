function kiks_gui_kiksnet_password_close(f)
global KIKS_NET_PASSWORD;

KIKS_NET_PASSWORD=get(findobj(f,'tag','passwd'),'string');
if isempty(KIKS_NET_PASSWORD)
    KIKS_NET_PASSWORD='[empty_password]';
end;
close(f);