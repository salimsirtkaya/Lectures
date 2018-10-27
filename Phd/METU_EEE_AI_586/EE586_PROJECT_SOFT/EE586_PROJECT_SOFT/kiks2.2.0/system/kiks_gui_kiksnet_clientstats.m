function kiks_gui_kiksnet_clientstats(pos,id,ip,cde,score)
global KIKS_GUI_HDL;

if nargin>1
    H=findobj(KIKS_GUI_HDL,'tag',sprintf('t_kiksnetserver_clientstats_%d',pos));
    if ~isempty(H)
        set(H,'String',{id,cde,ip,score});
        set(findobj(KIKS_GUI_HDL,'tag',sprintf('t_kiksnetserver_clientstats_%d_callsign',pos)),'String',cde);
    end;
else
    H=findobj(KIKS_GUI_HDL,'tag',sprintf('t_kiksnetserver_clientstats_%d',pos));
    if ~isempty(H)
        set(H,'String',{''});
        set(findobj(KIKS_GUI_HDL,'tag',sprintf('t_kiksnetserver_clientstats_%d_callsign',pos)),'String','');
    end;
end;
