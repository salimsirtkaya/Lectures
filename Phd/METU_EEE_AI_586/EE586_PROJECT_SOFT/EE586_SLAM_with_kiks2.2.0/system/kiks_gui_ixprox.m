% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_ixprox
global KIKS_AVAIL_NNET KIKS_PROX_USEARRAY KIKS_GUI_HDL

if KIKS_AVAIL_NNET==1
    h=findobj(KIKS_GUI_HDL,'Tag','indexprox_chk');
    nr=get(h,'Value');
    
    KIKS_PROX_USEARRAY=nr;
else
    h=findobj(KIKS_GUI_HDL,'Tag','indexprox_chk');
    set(h,'Enable','off');
    KIKS_PROX_USEARRAY=1;
end;
