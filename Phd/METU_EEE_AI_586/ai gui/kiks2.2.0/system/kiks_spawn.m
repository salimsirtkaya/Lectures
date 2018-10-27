% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
%
% kiks_spawn(type,pos)
% 
% places an object of type t at position pos.
% Pos is a 2-dimensional vector [xpos ypos].
% If pos is [] or omitted, the object will be placed at a random position.
% types: 1 = light, 2 = ball, 3 = cylinder
% examples: 
%    kiks_spawn(2,[100,100]);
%     places a ball at coordinates (100,100).
%    kiks_spawn(1);
%     places a light source at a random position.
function kiks_spawn(type,pos)
global KIKS_ARENA_MASK KIKS_MMPERPIXEL KIKS_WALL_WIDTH;

if nargin<1 | type<1 | type>3
    help kiks_spawn;
    error('<KiKS error> unknown object type. Supported types are 1 (light), 2 (ball) and 3 (cylinder).');
end;
if nargin==2
    [rows,cols]=size(pos);
    if rows~=1 | cols~=2
        help kiks_spawn;
        error('<KiKS error> Malformed position vector.');
    end;
    [ys,xs]=size(KIKS_ARENA_MASK);
    ys=ys*KIKS_MMPERPIXEL;
    xs=xs*KIKS_MMPERPIXEL;
    
    if pos(1)<0 | pos(1)>xs-KIKS_WALL_WIDTH*2 | pos(2)<0 | pos(2)>ys-KIKS_WALL_WIDTH*2
        help kiks_spawn;
        error('<KiKS error> Illegal position. Position is outside arena.');
    end;
else
    pos=[];
end;

kiks_spawn_object(pos,type);