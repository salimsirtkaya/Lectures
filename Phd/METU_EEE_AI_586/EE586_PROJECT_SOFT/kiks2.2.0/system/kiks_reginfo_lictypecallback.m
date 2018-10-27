function kiks_reginfo_lictypecallback

h=findobj(gcf,'Tag','lictype');
v=get(h,'Value');
i=findobj(gcf,'Tag','licno');
j=findobj(gcf,'Tag','licno_txt');
if(v==2),
    set(i,'Visible','on');
    set(j,'Visible','on');
else,
    set(i,'Visible','off');
    set(j,'Visible','off');
end;