% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_window_clear
global KIKS_2DVISUALIZE;

if(KIKS_2DVISUALIZE>0)  
    a=findobj('Type','line'); % clean up lines
    delete(a);
end;

