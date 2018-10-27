% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function res=kiks_recieve_var(fid,type,str)
res=[];
bytes=[];
lenstr=[];

if nargin<3
    str='Reading from socket...';
end;

while isempty(bytes) & tcpip_status(fid)~=0
    bytes=tcpip_read(fid,1,'uint8');
    if isempty(bytes)
        pause(0.001);
    end;
end;
%bytes

recieved=0;
while recieved<bytes & tcpip_status(fid)~=0
    lenstr=[lenstr; tcpip_read(fid,bytes-recieved,'uint8')];
    [recieved,tmp]=size(lenstr);
end;

msglen=0;
for i=1:bytes
    msglen=msglen+bitshift(lenstr(i),8*(i-1));
end;

ints=round(msglen/2);
recieved=0;
last_percent=0;
kiks_status(sprintf('%s\n',str));
while recieved<ints & tcpip_status(fid)~=0
    percent=round((recieved/ints)*100);
    if percent>last_percent
        kiks_status(sprintf('%s %d%%\n',str,percent));
        last_percent=percent;
    end;
    rd=tcpip_read(fid,ints-recieved,type);
    res=[res; rd];
    [recieved,tmp]=size(res);
    if (length(rd)==0)
        pause(0.001);
    end;
end;
kiks_status(sprintf('%s %d bytes recieved.',str,recieved*2));