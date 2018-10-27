function value=kLinLight(ref)
reply=kTurret(ref,2,'L');
[value,count,errmsg] = sscanf(reply(3:end),'%d,%d'); % cmd=='L'
