function kiks_foreground
global KIKS_FOREGROUND KIKS_PORT KIKS_GUI_HDL

h=findobj(KIKS_GUI_HDL,'tag','toggle_foreground');

if KIKS_FOREGROUND
    KIKS_FOREGROUND=[];
    return;
end;

KIKS_FOREGROUND=1;
kiks_status('Session control transferred to KiKS.',1);
set(h,'String','go passive');
drawnow;
try
    while KIKS_FOREGROUND
        try,
            pause(0.05);
            if KIKS_PORT(1)==1, ref=[-1 -1 -1 -1]; reflex = kProximity(ref); lights = kAmbient(ref); end;
            drawnow;
        catch,
            kiks_status(['??? ' lasterr]);
        end;
    end;
    KIKS_FOREGROUND=[];
    kiks_status('Session control returned to Matlab.',1);
    set(h,'String','go active');
catch
end
