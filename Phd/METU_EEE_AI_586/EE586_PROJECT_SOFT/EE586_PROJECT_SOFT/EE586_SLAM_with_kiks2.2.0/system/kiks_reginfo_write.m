function kiks_reginfo_write

cde=upper(get(findobj(gcf,'Tag','cde'),'String'));
vfk=get(findobj(gcf,'Tag','vfk'),'String');

lictype=get(findobj(gcf,'Tag','lictype'),'Value');
i=findobj(gcf,'Tag','licno');

if(lictype==1)
    lic=0;
end;
if(lictype==2)
    lic=-i;
end;
if(lictype==3)
    lic=Inf;
end;
datapath = which('kiks_reginfo.mat');
if isempty(datapath)
    datapath = [kiks_getsystempath 'kiks_reginfo'];
end;

save(datapath,'lic','cde','vfk');
close(gcf);