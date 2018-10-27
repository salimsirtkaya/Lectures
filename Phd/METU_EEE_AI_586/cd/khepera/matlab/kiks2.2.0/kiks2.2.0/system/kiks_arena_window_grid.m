% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_window_grid
global KIKS_2DVISUALIZE KIKS_2D_GRID;

if(KIKS_2DVISUALIZE>0)
    kiks_arena_window_close;
    KIKS_2D_GRID=abs(KIKS_2D_GRID-1);
    kiks_arena_window_open;
end;
