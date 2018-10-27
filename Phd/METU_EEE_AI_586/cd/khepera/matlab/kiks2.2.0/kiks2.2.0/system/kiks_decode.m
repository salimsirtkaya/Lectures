%   [cmd,values] = kiks_decode(dastr)
%   Decodes a message from 'CMD,arg1,arg2,arg3<endline>' - format to
%   [CMD arg1 arg2 arg3] - format.
%
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function [cmd,values] = kiks_decode(dastr)
cmd = dastr(1);
i = 3;
numstr = '';
values = [];
pos = 1;

while(i<=size(dastr,2))
    if (dastr(i)~=',' & dastr(i)~=char(10) & dastr(i)~=char(13))
        numstr = [numstr dastr(i)];
    else
        nr=str2num(numstr);
        if ~isempty(nr)
            values(1,pos) = nr;
        end;
        
        numstr = '';
        pos = pos+1;
    end;
    i=i+1;
end;
