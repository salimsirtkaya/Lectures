% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_window_open
global KIKS_2DVISUALIZE KIKS_GUI_HDL KIKS_ARENA_HDL;

figure(KIKS_GUI_HDL);
KIKS_2DVISUALIZE=1;
kiks_arena_window_init;
H=findobj(KIKS_GUI_HDL,'Tag','toggle2dvis');
set(H,'String','disable visualization'); 
H=findobj(KIKS_GUI_HDL,'Tag','arena_redraw');
set(H,'Enable','on');
H=findobj(KIKS_GUI_HDL,'Tag','arena_grid');
set(H,'Enable','on');

kiks_gui_resize(648);