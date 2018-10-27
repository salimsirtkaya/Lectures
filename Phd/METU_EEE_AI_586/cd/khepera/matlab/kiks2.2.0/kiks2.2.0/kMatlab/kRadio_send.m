function value=kRadio_send(ref,recvId,buf,msglen);
value=[];
if msglen>16 | msglen<0
    return;
end;
cmd=sprintf('S,%d,%d',recvId,msglen);
for i=1:msglen
    cmd = [cmd sprintf(',%d',buf(i))];
end;
for i=1:16-msglen
    cmd = [cmd ',0'];
end;
value=kTurret(ref,4,cmd);
