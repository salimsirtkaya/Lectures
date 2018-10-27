% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_addlight(id,xpos,ypos)
global KIKS_MMPERPIXEL KIKS_OBJECT_LIGHT_MASK KIKS_ARENA_MASK KIKS_OBJECT_LIGHT_RADIUS;

[rows,cols]=size(KIKS_OBJECT_LIGHT_MASK);

minx = floor(xpos/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL); % xpos - object radius
miny = floor(ypos/KIKS_MMPERPIXEL)-floor(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL); % ypos - object radius
maxx = floor(xpos/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL);
maxy = floor(ypos/KIKS_MMPERPIXEL)+floor(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL);

KIKS_ARENA_MASK(miny:maxy,minx:maxx) = KIKS_ARENA_MASK(miny:maxy,minx:maxx)+KIKS_OBJECT_LIGHT_MASK;
