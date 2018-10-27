% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_subroundobj(id,xpos,ypos)
global KIKS_MMPERPIXEL KIKS_COLOR_CYLINDER KIKS_ROUNDOBJMASK KIKS_ROUNDOBJMASK_COL KIKS_ARENA_MASK KIKS_ARENA_COLORMASK KIKS_ROUNDOBJECT_RADIUS;

[rows,cols]=size(KIKS_ROUNDOBJMASK);

minx = floor(xpos/KIKS_MMPERPIXEL)-floor(KIKS_ROUNDOBJECT_RADIUS/KIKS_MMPERPIXEL); % xpos - object radius
miny = floor(ypos/KIKS_MMPERPIXEL)-floor(KIKS_ROUNDOBJECT_RADIUS/KIKS_MMPERPIXEL); % ypos - object radius
maxx = floor(xpos/KIKS_MMPERPIXEL)+floor(KIKS_ROUNDOBJECT_RADIUS/KIKS_MMPERPIXEL);
maxy = floor(ypos/KIKS_MMPERPIXEL)+floor(KIKS_ROUNDOBJECT_RADIUS/KIKS_MMPERPIXEL);

KIKS_ARENA_MASK(miny:maxy,minx:maxx) = KIKS_ARENA_MASK(miny:maxy,minx:maxx)-KIKS_ROUNDOBJMASK;
KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)-KIKS_ROUNDOBJMASK_COL;
