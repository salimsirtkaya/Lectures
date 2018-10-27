% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res = kiks_asciidecode(str)

res=[];
str=double(str);
[tmp,sz]=size(str);

for i=1:2:sz
    res = [res bitshift(str(i)-'A',4)+(str(i+1)-'A')];
end;