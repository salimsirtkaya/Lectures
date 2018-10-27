% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_subremoterobot(xpos,ypos)
global KIKS_MMPERPIXEL KIKS_ROBOT_RADIUS KIKS_COLOR_ROBOT KIKS_RBTMASK KIKS_RBTMASK_COL KIKS_ARENA_COLORMASK;

[rows,cols]=size(KIKS_RBTMASK);
minx = floor(xpos/KIKS_MMPERPIXEL)-floor(KIKS_ROBOT_RADIUS/KIKS_MMPERPIXEL); % xpos - robot radius
miny = floor(ypos/KIKS_MMPERPIXEL)-floor(KIKS_ROBOT_RADIUS/KIKS_MMPERPIXEL); % ypos - robot radius
maxx = floor(xpos/KIKS_MMPERPIXEL)+floor(KIKS_ROBOT_RADIUS/KIKS_MMPERPIXEL);
maxy = floor(ypos/KIKS_MMPERPIXEL)+floor(KIKS_ROBOT_RADIUS/KIKS_MMPERPIXEL);

KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)=KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)-KIKS_RBTMASK_COL;