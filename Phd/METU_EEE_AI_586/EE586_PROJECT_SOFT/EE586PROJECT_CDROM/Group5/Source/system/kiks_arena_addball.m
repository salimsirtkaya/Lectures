% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_addball(id,xpos,ypos)
global KIKS_OBJECT_SMALLBALL_RADIUS KIKS_OBJECT_BALL_SMALLRATIO KIKS_OBJECT_SMALLBALL_MASK KIKS_OBJECT_SMALLBALL_MASK_COL KIKS_BALLDATA KIKS_MMPERPIXEL KIKS_COLOR_BALL KIKS_OBJECT_BALL_MASK_COL KIKS_OBJECT_BALL_MASK KIKS_ARENA_MASK KIKS_ARENA_COLORMASK KIKS_OBJECT_BALL_RADIUS;

[rows,cols]=size(KIKS_OBJECT_BALL_MASK);
cylinder=KIKS_BALLDATA(id,5);
theRadius=KIKS_OBJECT_BALL_RADIUS;
if cylinder theRadius=KIKS_OBJECT_SMALLBALL_RADIUS; end;

minx = floor(xpos/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % xpos - object radius
miny = floor(ypos/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % ypos - object radius
maxx = floor(xpos/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
maxy = floor(ypos/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);

if cylinder
    KIKS_ARENA_MASK(miny:maxy,minx:maxx) = KIKS_ARENA_MASK(miny:maxy,minx:maxx)+KIKS_OBJECT_SMALLBALL_MASK;
    KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)+KIKS_OBJECT_SMALLBALL_MASK_COL;
else
    KIKS_ARENA_MASK(miny:maxy,minx:maxx) = KIKS_ARENA_MASK(miny:maxy,minx:maxx)+KIKS_OBJECT_BALL_MASK;
    KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)+KIKS_OBJECT_BALL_MASK_COL;
end;    