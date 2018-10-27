% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_moverobot(id, forced_time)
global KIKS_MMPERPIXEL KIKS_FID KIKS_ARENA_MX KIKS_ARENA_MASK KIKS_TIMESCALE KIKS_ROBOT_MATRIX KIKS_PROX_POS KIKS_LIGHT_POS KIKS_SPDC KIKS_SESSIONACTIVE;
global KIKS_OBJECT_SMALLBALL_MASK KIKS_OBJECT_BALL_SMALLRATIO KIKS_RBTMASK;
global KIKS_COLOR_ROBOT KIKS_AVGTIME KIKS_AVGTIME_C KIKS_GUI_HDL;
global KIKS_updatelmp KIKS_dynstp KIKS_lastwascoll KIKS_RBT_TIME KIKS_indcol KIKS_indtime KIKS_INT_LIMIT KIKS_INTERPOLATE;

if isempty(KIKS_SESSIONACTIVE) error('No KiKS session found.'); return; end;
if isempty(KIKS_updatelmp) KIKS_updatelmp=-1; end;
if isempty(KIKS_indcol) KIKS_indcol=-1; KIKS_indtime=clock; end;

starttime=KIKS_RBT_TIME(abs(id));

v_time=forced_time;

oldxp = floor(KIKS_ROBOT_MATRIX(id,1,1));
oldyp = floor(KIKS_ROBOT_MATRIX(id,1,2));
%kiks_arena_subrobot(id,oldxp,oldyp);
kiks_arena_sub_mask(oldxp,oldyp,KIKS_COLOR_ROBOT,KIKS_ROBOT_MATRIX(id,2,2));

if(KIKS_ROBOT_MATRIX(id,2,4)==0)
    kiks_calculate_moverobot(id, v_time);
elseif(KIKS_ROBOT_MATRIX(id,2,4)==1)
    lt0=KIKS_ROBOT_MATRIX(id,6,1);
    lt1=KIKS_ROBOT_MATRIX(id,6,2);
    lt2=KIKS_ROBOT_MATRIX(id,6,3);
    lt3=KIKS_ROBOT_MATRIX(id,6,4);
    lmax_speed=KIKS_ROBOT_MATRIX(id,6,5);
    lacc=KIKS_ROBOT_MATRIX(id,6,6);
    rt0=KIKS_ROBOT_MATRIX(id,7,1);
    rt1=KIKS_ROBOT_MATRIX(id,7,2);
    rt2=KIKS_ROBOT_MATRIX(id,7,3);
    rt3=KIKS_ROBOT_MATRIX(id,7,4);
    rmax_speed=KIKS_ROBOT_MATRIX(id,7,5);
    racc=KIKS_ROBOT_MATRIX(id,7,6);
    timevector = sort([lt0 lt1 lt2 lt3 rt0 rt1 rt2 rt3]);
    
    vec = [KIKS_ROBOT_MATRIX(id,5,7) KIKS_ROBOT_MATRIX(id,5,7)+v_time];
    for i=1:8
        if (timevector(i)>vec(1) & timevector(i)<vec(2))
            vec = [vec timevector(i)];
        end;
    end;
    vec = sort(vec);
    steps = size(vec,2);
    
    for i=1:(steps-1)
        if(vec(i) ~= vec(i+1))
            leftspeed = kiks_calculate_speed(lt0,lt1,lt2,lt3,lmax_speed,lacc,vec(i),vec(i+1));
            rightspeed = kiks_calculate_speed(rt0,rt1,rt2,rt3,rmax_speed,racc,vec(i),vec(i+1));
            
            KIKS_ROBOT_MATRIX(id,1,5)=leftspeed;
            KIKS_ROBOT_MATRIX(id,1,6)=rightspeed;
            
            kiks_calculate_moverobot(id, vec(i+1)-vec(i));
        end;
    end;
    
    KIKS_ROBOT_MATRIX(id,5,7)=KIKS_ROBOT_MATRIX(id,5,7)+v_time;
    
    if KIKS_ROBOT_MATRIX(id,5,7)>lt3 % left wheel movement is done
        KIKS_ROBOT_MATRIX(id,2,3)=1;
        KIKS_ROBOT_MATRIX(id,2,5)=KIKS_ROBOT_MATRIX(id,5,5)-KIKS_ROBOT_MATRIX(id,1,7);    
    end;
    if KIKS_ROBOT_MATRIX(id,5,7)>rt3 % right wheel movement is done
        KIKS_ROBOT_MATRIX(id,2,6)=1;
        KIKS_ROBOT_MATRIX(id,2,8)=KIKS_ROBOT_MATRIX(id,5,6)-KIKS_ROBOT_MATRIX(id,1,8);
    end;
    
    if KIKS_ROBOT_MATRIX(id,5,7)>rt3 & KIKS_ROBOT_MATRIX(id,5,7)>lt3
        % movement is done
        KIKS_ROBOT_MATRIX(id,1,4)=0;
    end;
end;

newxp = floor(KIKS_ROBOT_MATRIX(id,1,1));
newyp = floor(KIKS_ROBOT_MATRIX(id,1,2));

%kiks_arena_addrobot(id,newxp,newyp);
kiks_arena_add_mask(newxp,newyp,KIKS_COLOR_ROBOT,KIKS_ROBOT_MATRIX(id,2,2));