% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function [res,ver] = kiks_checkversion
global KIKS_REGCODE;

res=0;
ver=0;
stopit=0;
try
    request = ['GET /currentversion.htm HTTP/1.0' 13 10 'Host: www.tstorm.se' 13 10 13 10];
    fid=tcpip_open('www.tstorm.se',80);
    kiks_status('Checking for available updates');
    if fid~=-1
        while(~isempty(request)) request=tcpip_write(fid,request); end;
        str=[];
        t0=clock;
        lines=0;
        version=[];
        pause(1/3);
        kiks_status('Checking for available updates.');
        pause(1/3);
        kiks_status('Checking for available updates..');
        pause(1/3);
        kiks_status('Checking for available updates...');
        
        str = tcpip_read(fid,1024);
        if tcpip_status(fid)~=0 tcpip_close(fid); end;       
        if ~isempty(str) 
            rs = findstr(str,'KiKS');
            if ~isempty(rs)
                version = str(rs+5:end);
            end;
        end;
        if ~isempty(version)
            ver=deblank(version);
            res=1;
        end;
        kiks_status('Checking for available updates... done.');
    else
        kiks_status('Checking for available updates... failed. No internet connection?');
    end;
catch
    kiks_status('Warning: Could not find tcp/ip tools.');
end;