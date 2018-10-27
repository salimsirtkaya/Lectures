% [ready_to_send message_recieved send_failed]=kRadio_status(ref);
function res=kRadio_status(ref);
res='';
reply=kTurret(ref,4,'F');
[value,count,errmsg] = sscanf(reply(3:end),'%d');
if (value)
    res=[bitget(value,1) bitget(value,2) bitget(value,3)];
end;