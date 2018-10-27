% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_window_close
global KIKS_2DVISUALIZE KIKS_GUI_HDL KIKS_ARENA_HDL;

KIKS_2DVISUALIZE=0;

H=findobj(KIKS_GUI_HDL,'Tag','toggle2dvis');
set(H,'String','enable visualization'); 
H=findobj(KIKS_GUI_HDL,'Tag','arena_redraw');
set(H,'Enable','off');
H=findobj(KIKS_GUI_HDL,'Tag','arena_grid');
set(H,'Enable','off');
H=findobj(KIKS_GUI_HDL,'type','patch');
delete(H);
H=findobj(KIKS_GUI_HDL,'type','image');
delete(H);
kiks_gui_resize;
