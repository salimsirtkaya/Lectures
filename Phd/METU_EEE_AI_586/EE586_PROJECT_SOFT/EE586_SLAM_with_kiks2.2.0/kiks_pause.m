function kiks_pause(ptime)
% -----------------------------------------------
%  (c) 2000 Theodor Storm (theodor@tstorm.se)
%  http://www.tstorm.se
% -----------------------------------------------
global KIKS_PHYS_PORT KIKS_PAUSETIME KIKS_TIMESCALE KIKS_RBTARRAY KIKS_PORT;
if abs(max(max(KIKS_PHYS_PORT)))>0
    pause(ptime);
else
    if isempty(KIKS_PAUSETIME) KIKS_PAUSETIME=0; end;
    if isempty(KIKS_TIMESCALE)
        % KiKS inactive, just pause
        pause(ptime);
    else
        if KIKS_TIMESCALE>=0
            % update world during pause time
            [rows,cols]=size(KIKS_RBTARRAY);
            if cols>0
                ref=[-KIKS_RBTARRAY(1) -KIKS_RBTARRAY(1) -KIKS_RBTARRAY(1) -KIKS_RBTARRAY(1)];
                t0=kiks_ktime(-KIKS_RBTARRAY(1));     
                while kiks_ktime(-KIKS_RBTARRAY(1))-t0<ptime
                    KIKS_PAUSETIME=KIKS_PAUSETIME+0.05;
                end;
            else
                pause(ptime);
            end;
        else
            [rows,cols]=size(KIKS_RBTARRAY);
            if cols>0
                KIKS_PAUSETIME=KIKS_PAUSETIME+ptime;
            else
                pause(ptime);
            end;
        end;
    end;
end;

