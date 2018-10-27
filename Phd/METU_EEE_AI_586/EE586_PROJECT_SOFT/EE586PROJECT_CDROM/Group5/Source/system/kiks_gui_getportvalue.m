% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function num=kiks_gui_getportvalue
global KIKS_GUI_HDL;

h=findobj(KIKS_GUI_HDL,'Tag','kheppopup');
s=get(h,'String');
v=get(h,'Value');

[y,x]=size(s);

for i=1:y,
    f(i)={sprintf('str%d',i)};
end;
sc=cell2struct(s,f,1);
str=getfield(sc,sprintf('str%d',v));
num=abs(sscanf(str,'Port %d'));
