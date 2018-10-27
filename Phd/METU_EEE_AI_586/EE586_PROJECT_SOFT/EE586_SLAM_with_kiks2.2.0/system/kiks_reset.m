% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res = kiks_reset(rndobjects)
global KIKS_COLOR_ROBOT KIKS_ROBOT_MATRIX KIKS_OBJECT_BALL KIKS_OBJECT_SMALLBALL KIKS_BALLDATA KIKS_RBTARRAY KIKS_BALLARRAY KIKS_ROUNDOBJARRAY KIKS_LIGHTARRAY KIKS_LIGHTDATA;
global KIKS_CHK_ROBOT_MATRIX KIKS_CHK_OBJECT_BALL KIKS_CHK_OBJECT_SMALLBALL KIKS_CHK_BALLDATA KIKS_CHK_KHEPARRAY KIKS_CHK_BALLARRAY KIKS_CHK_ROUNDOBJARRAY KIKS_CHK_LIGHTARRAY KIKS_CHK_LIGHTDATA;
global KIKS_CHECKPOINT;

if ~isempty(KIKS_CHECKPOINT)
    [rows,cols]=size(KIKS_RBTARRAY);
    for i=1:cols
        xp = floor(KIKS_ROBOT_MATRIX(abs(KIKS_RBTARRAY(i)),1,1));
        yp = floor(KIKS_ROBOT_MATRIX(abs(KIKS_RBTARRAY(i)),1,2));
        %kiks_arena_subrobot(abs(KIKS_RBTARRAY(i)),xp,yp);
        kiks_arena_sub_mask(xp,yp,KIKS_COLOR_ROBOT,KIKS_ROBOT_MATRIX(abs(KIKS_RBTARRAY(i)),2,2));
    end;
    [rows,cols]=size(KIKS_BALLARRAY);
    for i=1:cols
        id=KIKS_BALLARRAY(i);
        xp=KIKS_BALLDATA(id,1);
        yp=KIKS_BALLDATA(id,2);
        kiks_arena_subball(id,floor(xp),floor(yp));
    end;
    
    KIKS_ROBOT_MATRIX=KIKS_CHK_ROBOT_MATRIX; 
    KIKS_OBJECT_BALL=KIKS_CHK_OBJECT_BALL; 
    KIKS_OBJECT_SMALLBALL=KIKS_CHK_OBJECT_SMALLBALL; 
    KIKS_BALLDATA=KIKS_CHK_BALLDATA;
    KIKS_RBTARRAY=KIKS_CHK_KHEPARRAY;
    KIKS_BALLARRAY=KIKS_CHK_BALLARRAY; 
    KIKS_LIGHTARRAY=KIKS_CHK_LIGHTARRAY;
    KIKS_LIGHTDATA=KIKS_CHK_LIGHTDATA;
    
    [rows,cols]=size(KIKS_RBTARRAY);
    for i=1:cols
        xp = floor(KIKS_ROBOT_MATRIX(abs(KIKS_RBTARRAY(i)),1,1));
        yp = floor(KIKS_ROBOT_MATRIX(abs(KIKS_RBTARRAY(i)),1,2));
        %kiks_arena_addrobot(abs(KIKS_RBTARRAY(i)),xp,yp);
        kiks_arena_add_mask(xp,yp,KIKS_COLOR_ROBOT,KIKS_ROBOT_MATRIX(abs(KIKS_RBTARRAY(i)),2,2));

        kiks_draw_robot(KIKS_RBTARRAY(i));
    end;
    [rows,cols]=size(KIKS_BALLARRAY);
    for i=1:cols
        id=KIKS_BALLARRAY(i);
        xp=KIKS_BALLDATA(id,1);
        yp=KIKS_BALLDATA(id,2);
        kiks_arena_addball(id,floor(xp),floor(yp));
        kiks_draw_ball(KIKS_BALLARRAY(i));
    end;
    [rows,cols]=size(KIKS_LIGHTARRAY);
    for i=1:cols
        id=KIKS_LIGHTARRAY(i);
        xp=KIKS_LIGHTDATA(id,1);
        xy=KIKS_LIGHTDATA(id,1);
        kiks_draw_light(KIKS_LIGHTARRAY(i));
    end;
end;