% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_vis2dtoggle
global KIKS_2DVISUALIZE KIKS_GUI_HDL;
if isempty(KIKS_2DVISUALIZE)
    return;
end;

if(KIKS_2DVISUALIZE==0) 
    KIKS_2DVISUALIZE=1;
    kiks_arena_window_open;
else
    KIKS_2DVISUALIZE=0;
    kiks_arena_window_close;
end
