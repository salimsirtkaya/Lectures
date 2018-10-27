function kiks_arena_edit_mode
global KIKS_GUI_HDL KIKS_ARENA_EDITING_MODE KIKS_COLOR_BACKGROUND;

KIKS_ARENA_EDITING_MODE=mod(KIKS_ARENA_EDITING_MODE+1,2);

h=findobj(KIKS_GUI_HDL,'tag','arena_edit_mode');
switch KIKS_ARENA_EDITING_MODE
    case 0
        set(h,'String','mode: draw');
        h=findobj(KIKS_GUI_HDL,'tag','arena_color_slider');
        set(h,'enable','on');
        v=get(h,'Value'); set(h,'BackgroundColor',[v/255 v/255 v/255]);
    case 1
        set(h,'String','mode: erase');    
        h=findobj(KIKS_GUI_HDL,'tag','arena_color_slider');
        set(h,'enable','off');
        set(h,'BackgroundColor',KIKS_COLOR_BACKGROUND);
end;