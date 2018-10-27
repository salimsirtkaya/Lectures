function kiks_setmode(mode)
global KIKS_ACTIVE_MODE

if nargin
    KIKS_ACTIVE_MODE=1;
    try
        disp('Keyboard control transferred to KiKS.');
        while KIKS_SESSIONACTIVE
            pause(0.01);
        end;
    catch
        disp('Keyboard control returned to Matlab.');
    end;
else
    KIKS_ACTIVE_MODE=[];
end;