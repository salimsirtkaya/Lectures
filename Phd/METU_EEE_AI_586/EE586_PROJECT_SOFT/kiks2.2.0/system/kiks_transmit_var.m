% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function str=kiks_transmit_var(fid,var)

if strcmp(class(var),'uint16')~=1
    error('<KiKS> kiks_transmit_var: only UINT16 variables are supported.');
    return;
end;

[tmp,len] = size(var);
t=len*2;
bytes=0;
lenstr=uint8([]);
while(t>0)
    bytes=bytes+1;
    t_=bitshift(t,-8);
    rest=t-bitshift(t_,8);
    lenstr=[lenstr rest];
    t=t_;
end;
sendstr = uint8([bytes lenstr]);
while ~isempty(sendstr) & tcpip_status(fid)~=0
    sendstr=tcpip_write(fid,sendstr);
end;
while ~isempty(var) & tcpip_status(fid)~=0
    var=tcpip_write(fid,var);
end;