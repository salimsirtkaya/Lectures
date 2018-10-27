% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_settimescale(tscale)
global KIKS_GUI_HDL;

if(tscale==1 | tscale==2)
    h=findobj(KIKS_GUI_HDL,'Tag','timescale_popup');
    nr=get(h,'Value');
    set(h,'Value',tscale);
    kiks_gui_gettimescale;
end;

