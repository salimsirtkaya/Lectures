% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function kiks_transmit_string(fid,str)
strlen = length(str);
t=strlen;
bytes=0;
lenstr='';
while(t>0)
    bytes=bytes+1;
    t_=bitshift(t,-8);
    rest=t-bitshift(t_,8);
    lenstr=[lenstr rest];
    t=t_;
end;
sendstr = [bytes lenstr str];
while ~isempty(sendstr) & tcpip_status(fid)~=0
    sendstr=tcpip_write(fid,sendstr);
end;
