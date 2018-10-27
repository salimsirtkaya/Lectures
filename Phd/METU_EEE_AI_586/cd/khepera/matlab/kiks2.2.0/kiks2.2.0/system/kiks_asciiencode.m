% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res = kiks_asciiencode(data)

data = double(data);
res = '';
[tmp,sz]=size(data);

for i=1:sz
    res=strcat(res,char('A'+bitshift(data(i),-4,8)));
    res=strcat(res,char('A'+bitshift(bitshift(data(i),4,8),-4,8)));
end;