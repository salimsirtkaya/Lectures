% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_grid(onoff)
global KIKS_2DVISUALIZE KIKS_2DGRID KIKS_ARENA_MX

KIKS_2DGRID=onoff;
if (KIKS_2DVISUALIZE>0)
    h=findobj('Name','KiKS arena');
    figure(h);
    [y,x]=size(KIKS_ARENA_MX);
    for i=0:10:y
        plot([0 x],[i i],'b:');
    end;
    for i=0:10:x
        plot([i i],[0 y],'b:');
    end;   
end;
