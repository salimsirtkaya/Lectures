% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_update_remote_objects
global KIKS_OBJECT_BALL_MASK_COL KIKS_OBJECT_BALL_RADIUS KIKS_OBJECT_SMALLBALL_MASK KIKS_OBJECT_SMALLBALL_RADIUS KIKS_ARENA_MASK KIKS_ARENA_COLORMASK KIKS_OBJECT_SMALLBALL_MASK_COL KIKS_REMOTE_OBJECTS_BALL KIKS_REMOTE_OBJECTS_CYLINDER KIKS_2DVISUALIZE KIKS_CYLINDER_HDL KIKS_OBJECT_SMALLBALL KIKS_OBJECT_BALL KIKS_BALL_HDL KIKS_LIGHT_HDL KIKS_LIGHTARRAY KIKS_MMPERPIXEL KIKS_LIGHTDATA KIKS_OBJECT_LIGHT KIKS_WALL_RENDER KIKS_WALL_WIDTH KIKS_REMOTE_OBJECTS_ARRAY_NEW KIKS_REMOTE_OBJECTS_ARRAY KIKS_REMOTE_OBJECTS_LIGHTS KIKS_REMOTE_OBJECTS_BALLS KIKS_REMOTE_OBJECTS_CYLINDERS;
if isempty(KIKS_REMOTE_OBJECTS_LIGHTS) KIKS_REMOTE_OBJECTS_LIGHTS=0; end;
if isempty(KIKS_REMOTE_OBJECTS_BALLS) KIKS_REMOTE_OBJECTS_BALLS=0; end;
if isempty(KIKS_REMOTE_OBJECTS_CYLINDERS) KIKS_REMOTE_OBJECTS_CYLINDERS=0; end;
lights=0;
balls=0;
cylinders=0;
[vectorsize,tmp]=size(KIKS_REMOTE_OBJECTS_ARRAY_NEW);
step=0;
while step<vectorsize
    step=step+1;
    type=KIKS_REMOTE_OBJECTS_ARRAY_NEW(step);
    step=step+1;
    radius=KIKS_REMOTE_OBJECTS_ARRAY_NEW(step);
    step=step+1;
    xp=KIKS_REMOTE_OBJECTS_ARRAY_NEW(step);
    step=step+1;
    yp=KIKS_REMOTE_OBJECTS_ARRAY_NEW(step);
    if(type==1) 
        lights=lights+1;
        if lights>KIKS_REMOTE_OBJECTS_LIGHTS
            KIKS_LIGHT_HDL(lights)=kiks_patch_light(lights);
            KIKS_LIGHTARRAY = [KIKS_LIGHTARRAY lights];
            KIKS_REMOTE_OBJECTS_LIGHTS=lights;
        end;
        kx = xp/KIKS_MMPERPIXEL;
        ky = yp/KIKS_MMPERPIXEL;      
        KIKS_LIGHTDATA(lights,1)=xp;
        KIKS_LIGHTDATA(lights,2)=yp;      
        set(KIKS_LIGHT_HDL(lights),'xdata',KIKS_OBJECT_LIGHT(1,:)+kx-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),'ydata',KIKS_OBJECT_LIGHT(2,:)+ky-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));
    elseif(type==2) 
        balls=balls+1;
        if balls>KIKS_REMOTE_OBJECTS_BALLS
            KIKS_REMOTE_OBJECTS_BALL(balls,1)=0;
            KIKS_REMOTE_OBJECTS_BALL(balls,2)=0;
            KIKS_BALL_HDL(balls)=kiks_patch_ball(balls);
            KIKS_REMOTE_OBJECTS_BALLS=balls;
        end;
        oldxp=KIKS_REMOTE_OBJECTS_BALL(balls,1);
        oldyp=KIKS_REMOTE_OBJECTS_BALL(balls,2);
        kx = xp/KIKS_MMPERPIXEL;
        ky = yp/KIKS_MMPERPIXEL;      
        if(xp~=oldxp | yp~=oldyp)
            set(KIKS_BALL_HDL(balls),'xdata',KIKS_OBJECT_BALL(1,:)+kx-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),'ydata',KIKS_OBJECT_BALL(2,:)+ky-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));   
            if(oldxp~=0 & oldyp~=0)
                minx = floor(oldxp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
                miny = floor(oldyp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
                maxx = floor(oldxp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
                maxy = floor(oldyp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
                KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)-KIKS_OBJECT_BALL_MASK_COL;      
            end;
            
            minx = floor(xp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
            miny = floor(yp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
            maxx = floor(xp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
            maxy = floor(yp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL);
            KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)+KIKS_OBJECT_BALL_MASK_COL;
        end;
        
        KIKS_REMOTE_OBJECTS_BALL(balls,1)=xp;
        KIKS_REMOTE_OBJECTS_BALL(balls,2)=yp;         
    elseif(type==3) 
        cylinders=cylinders+1;
        if cylinders>KIKS_REMOTE_OBJECTS_CYLINDERS
            KIKS_REMOTE_OBJECTS_CYLINDER(cylinders,1)=0;
            KIKS_REMOTE_OBJECTS_CYLINDER(cylinders,2)=0;
            KIKS_CYLINDER_HDL(cylinders)=kiks_patch_ball(cylinders);
            KIKS_REMOTE_OBJECTS_CYLINDERS=cylinders;
        end;
        oldxp=KIKS_REMOTE_OBJECTS_CYLINDER(cylinders,1);
        oldyp=KIKS_REMOTE_OBJECTS_CYLINDER(cylinders,2);
        kx = xp/KIKS_MMPERPIXEL;
        ky = yp/KIKS_MMPERPIXEL; 
        if(xp~=oldxp | yp~=oldyp) 
            set(KIKS_CYLINDER_HDL(cylinders),'xdata',KIKS_OBJECT_SMALLBALL(1,:)+kx-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),'ydata',KIKS_OBJECT_SMALLBALL(2,:)+ky-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL)); 
            if(oldxp~=0 & oldyp~=0)
                minx = floor(oldxp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
                miny = floor(oldyp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
                maxx = floor(oldxp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
                maxy = floor(oldyp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
                KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)-KIKS_OBJECT_SMALLBALL_MASK_COL;      
            end;        
            
            minx = floor(xp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
            miny = floor(yp/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
            maxx = floor(xp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
            maxy = floor(yp/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL);
            KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)+KIKS_OBJECT_SMALLBALL_MASK_COL;
        end;
        KIKS_REMOTE_OBJECTS_CYLINDER(cylinders,1)=xp;
        KIKS_REMOTE_OBJECTS_CYLINDER(cylinders,2)=yp;
    end;
end;




