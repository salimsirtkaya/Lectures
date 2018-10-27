% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function kiks_spawn_object(pos,num)
global KIKS_OBJECT_SMALLBALL_RADIUS KIKS_OBJECT_BALL_SMALLRATIO KIKS_ARENA_HDL KIKS_MMPERPIXEL KIKS_OBJECT_BALL_UPD KIKS_OBJECT_BALL_RADIUS KIKS_BALL_HDL KIKS_BALLARRAY KIKS_BALLDATA KIKS_2DVISUALIZE KIKS_LIGHTARRAY KIKS_LIGHT_HDL KIKS_LIGHTDATA KIKS_ROUNDOBJARRAY KIKS_ROUNDOBJDATA KIKS_GUI_HDL KIKS_WALL_WIDTH KIKS_ARENA_MX KIKS_ARENA_MASK;
if nargin<2 num=kiks_gui_getobjlistbox; end;

if num==1 % light
    newobjid=1;
    [rows,cols]=size(KIKS_LIGHTARRAY);
    
    ok=1;
    while(ok==1)
        ok=0;
        for i=1:cols,
            if(KIKS_LIGHTARRAY(i)==newobjid)
                ok=1;
            end
        end
        if (ok==1) newobjid=newobjid+1; end;
    end;
    
    KIKS_LIGHTARRAY(cols+1) = newobjid;
    
    [ys,xs]=size(KIKS_ARENA_MASK);
    ys=ys*KIKS_MMPERPIXEL;
    xs=xs*KIKS_MMPERPIXEL;
    if(nargin<1 | isempty(pos)) % place object at random position
        KIKS_LIGHTDATA(newobjid,1)=KIKS_WALL_WIDTH+rand*(xs-KIKS_WALL_WIDTH*2);
        KIKS_LIGHTDATA(newobjid,2)=KIKS_WALL_WIDTH+rand*(ys-KIKS_WALL_WIDTH*2);
        %KIKS_LIGHTDATA(newobjid,1)=KIKS_WALL_WIDTH+rand*(xs-KIKS_WALL_WIDTH*2);
        %KIKS_LIGHTDATA(newobjid,2)=KIKS_WALL_WIDTH+rand*(ys-KIKS_WALL_WIDTH*2);
        %while(max(max(KIKS_ARENA_MX(round(KIKS_LIGHTDATA(newobjid,2))-15:round(KIKS_LIGHTDATA(newobjid,2))+15,round(KIKS_LIGHTDATA(newobjid,1))-15:round(KIKS_LIGHTDATA(newobjid,1)+15))))>0 | max(max(KIKS_ARENA_MASK(round(KIKS_LIGHTDATA(newobjid,2))-15:round(KIKS_LIGHTDATA(newobjid,2))+15,round(KIKS_LIGHTDATA(newobjid,1))-15:round(KIKS_LIGHTDATA(newobjid,1)+15))))>0)
        %   KIKS_LIGHTDATA(newobjid,1)=KIKS_WALL_WIDTH+rand*(xs-KIKS_WALL_WIDTH*2);
        %   KIKS_LIGHTDATA(newobjid,2)=KIKS_WALL_WIDTH+rand*(ys-KIKS_WALL_WIDTH*2);
        %end
    else
        KIKS_LIGHTDATA(newobjid,1)=pos(1)+KIKS_WALL_WIDTH;
        KIKS_LIGHTDATA(newobjid,2)=pos(2)+KIKS_WALL_WIDTH;
    end;
    
    while(max(max(KIKS_ARENA_MASK(floor(((KIKS_LIGHTDATA(newobjid,2))-15)/KIKS_MMPERPIXEL):floor(((KIKS_LIGHTDATA(newobjid,2))+15)/KIKS_MMPERPIXEL), ... 
            floor(((KIKS_LIGHTDATA(newobjid,1))-15)/KIKS_MMPERPIXEL):floor(((KIKS_LIGHTDATA(newobjid,1)+15))/KIKS_MMPERPIXEL))))>0)
        KIKS_LIGHTDATA(newobjid,1)=KIKS_WALL_WIDTH+rand*(xs-KIKS_WALL_WIDTH*2);
        KIKS_LIGHTDATA(newobjid,2)=KIKS_WALL_WIDTH+rand*(ys-KIKS_WALL_WIDTH*2);
    end;
    
    
    if (KIKS_2DVISUALIZE>0)
        figure(KIKS_GUI_HDL);
        KIKS_LIGHT_HDL(newobjid)=kiks_patch_light(newobjid);
        kiks_draw_light(newobjid);
    end;
    %   newxp = floor(KIKS_LIGHTDATA(newobjid,1));
    %   newyp = floor(KIKS_LIGHTDATA(newobjid,2));
    %   kiks_arena_addlight(newobjid,newxp,newyp);
elseif num==2 | num==3 % ball or cylinder2
    cylinder=num-2;
    newobjid=1;
    [rows,cols]=size(KIKS_BALLARRAY);
    
    ok=1;
    while(ok==1)
        ok=0;
        for i=1:cols,
            if(KIKS_BALLARRAY(i)==newobjid)
                ok=1;
            end
        end
        if (ok==1) newobjid=newobjid+1; end;
    end;
    
    KIKS_BALLARRAY(cols+1) = newobjid;
    
    [ys,xs]=size(KIKS_ARENA_MASK);
    ys=ys*KIKS_MMPERPIXEL;
    xs=xs*KIKS_MMPERPIXEL;
    if(nargin<1 | isempty(pos)) % place object at random position
        %KIKS_BALLDATA(newobjid,1)=KIKS_WALL_WIDTH+rand*(xs-KIKS_WALL_WIDTH*2);
        %KIKS_BALLDATA(newobjid,2)=KIKS_WALL_WIDTH+rand*(ys-KIKS_WALL_WIDTH*2);
        %while(max(max(KIKS_ARENA_MX(round(KIKS_BALLDATA(newobjid,2))-KIKS_OBJECT_BALL_RADIUS:round(KIKS_BALLDATA(newobjid,2))+KIKS_OBJECT_BALL_RADIUS,round(KIKS_BALLDATA(newobjid,1))-KIKS_OBJECT_BALL_RADIUS:round(KIKS_BALLDATA(newobjid,1)+KIKS_OBJECT_BALL_RADIUS))))>0 | max(max(KIKS_ARENA_MASK(round(KIKS_BALLDATA(newobjid,2))-KIKS_OBJECT_BALL_RADIUS:round(KIKS_BALLDATA(newobjid,2))+KIKS_OBJECT_BALL_RADIUS,round(KIKS_BALLDATA(newobjid,1))-KIKS_OBJECT_BALL_RADIUS:round(KIKS_BALLDATA(newobjid,1)+KIKS_OBJECT_BALL_RADIUS))))>0)
        %   KIKS_BALLDATA(newobjid,1)=KIKS_WALL_WIDTH+rand*(xs-KIKS_WALL_WIDTH*2);
        %   KIKS_BALLDATA(newobjid,2)=KIKS_WALL_WIDTH+rand*(ys-KIKS_WALL_WIDTH*2);
        %end
        
        KIKS_BALLDATA(newobjid,1)=round(xs/2);
        KIKS_BALLDATA(newobjid,2)=round(ys/2);
    else
        KIKS_BALLDATA(newobjid,1)=pos(1)+KIKS_WALL_WIDTH;
        KIKS_BALLDATA(newobjid,2)=pos(2)+KIKS_WALL_WIDTH;
    end
    theRadius=KIKS_OBJECT_BALL_RADIUS;
    if cylinder theRadius=KIKS_OBJECT_SMALLBALL_RADIUS; end;
    while(max(max(KIKS_ARENA_MASK(floor(((KIKS_BALLDATA(newobjid,2))-theRadius)/KIKS_MMPERPIXEL):floor(((KIKS_BALLDATA(newobjid,2))+theRadius)/KIKS_MMPERPIXEL), ... 
            floor(((KIKS_BALLDATA(newobjid,1))-theRadius)/KIKS_MMPERPIXEL):floor(((KIKS_BALLDATA(newobjid,1)+theRadius))/KIKS_MMPERPIXEL))))>0)
        KIKS_BALLDATA(newobjid,1)=KIKS_WALL_WIDTH+rand*(xs-KIKS_WALL_WIDTH*2);
        KIKS_BALLDATA(newobjid,2)=KIKS_WALL_WIDTH+rand*(ys-KIKS_WALL_WIDTH*2);
    end;
    
    KIKS_BALLDATA(newobjid,3)=0; % speed
    KIKS_BALLDATA(newobjid,4)=rand*2*pi; % angle
    KIKS_BALLDATA(newobjid,5)=cylinder; % is this a cylinder?
    KIKS_OBJECT_BALL_UPD(newobjid)=0;
    newxp = floor(KIKS_BALLDATA(newobjid,1));
    newyp = floor(KIKS_BALLDATA(newobjid,2));
    kiks_arena_addball(newobjid,newxp,newyp);   
    
    if (KIKS_2DVISUALIZE>0)
        figure(KIKS_GUI_HDL);
        KIKS_BALL_HDL(newobjid)=kiks_patch_ball(newobjid);
        kiks_draw_ball(newobjid);
    end;
    
end;
kiks_checkpoint;