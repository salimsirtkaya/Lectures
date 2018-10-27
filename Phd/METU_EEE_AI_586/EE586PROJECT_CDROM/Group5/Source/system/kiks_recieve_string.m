% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function res=kiks_recieve_string(fid)
global KIKS_NET_BUFSIZ;
res=[];
ok=0;
while ok~=1 & tcpip_status(fid)~=0
    [res,ok]=tcpip_readln(fid,KIKS_NET_BUFSIZ);
    if (ok~=1)
        pause(0.001);
    end;
end;