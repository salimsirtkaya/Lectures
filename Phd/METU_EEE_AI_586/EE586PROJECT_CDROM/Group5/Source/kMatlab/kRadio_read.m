function value=kRadio_read(ref);
reply=kTurret(ref,4,'R');
[value,count,errmsg] = sscanf(reply(3:end),'%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d');
