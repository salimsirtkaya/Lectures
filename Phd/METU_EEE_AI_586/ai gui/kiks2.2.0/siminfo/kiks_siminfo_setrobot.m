% function res = kiks_siminfo_setrobot(x,y,radians)
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function res=kiks_siminfo_setrobot(x,y,radians)
global KIKS_RBTARRAY KIKS_WALL_WIDTH KIKS_MMPERPIXEL;

res=1;

if(nargin<3) 
    rot=[]; 
else
    %rot=degrees*(pi/180);
    rot=radians;
end;

if(nargin<2) 
    res=0;
    pos=[]; 
else
    pos=[(x)+KIKS_WALL_WIDTH (y)+KIKS_WALL_WIDTH];
end;

if(res)
    while size(KIKS_RBTARRAY>0)
        kiks_delete_robot(KIKS_RBTARRAY(1));
    end;
    res=kiks_spawn_robot(pos,rot);
end;