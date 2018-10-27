% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_setdiod(id,dnr,status)
global KIKS_RBTDIOD_HDL;

a=get(KIKS_RBTDIOD_HDL(id,dnr+1),'Facecolor');
set(KIKS_RBTDIOD_HDL(id,dnr+1),'Visible','off');
set(KIKS_RBTDIOD_HDL(id,dnr+1),'Tag','deleteme');

switch status
    case 0
        KIKS_RBTDIOD_HDL(id,dnr+1)=KIKS_RBTdiodpatch(id,[0.3 0.9 0.3]);
    case 1
        KIKS_RBTDIOD_HDL(id,dnr+1)=KIKS_RBTdiodpatch(id,[1 0.4 0.4]);
    case 2
        if(a==[1 0.4 0.4])
            KIKS_RBTDIOD_HDL(id,dnr+1)=KIKS_RBTdiodpatch(id,[0.3 0.9 0.3]);
        else
            KIKS_RBTDIOD_HDL(id,dnr+1)=KIKS_RBTdiodpatch(id,[1 0.4 0.4]);
        end;
end;

kiks_draw_robot(id);