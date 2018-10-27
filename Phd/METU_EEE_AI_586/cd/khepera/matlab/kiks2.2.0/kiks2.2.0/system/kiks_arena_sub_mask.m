% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% TODO: cache downsampled matrixes
function kiks_arena_sub_mask(xpos,ypos,color,theRadius)
global KIKS_ROUND_COLORMASK_CELL KIKS_ROUND_MASK_CELL KIKS_ROUND_MASK KIKS_MMPERPIXEL KIKS_ARENA_MASK KIKS_ARENA_COLORMASK;
r=floor(theRadius/KIKS_MMPERPIXEL)*2+1;
if r>100
    error('Object too large');
end;
binary_mask = KIKS_ROUND_MASK_CELL{r};
color_mask = KIKS_ROUND_COLORMASK_CELL{r};

minx = floor(xpos/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % xpos - object radius
miny = floor(ypos/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % ypos - object radius
maxx = floor(xpos/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
maxy = floor(ypos/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);

KIKS_ARENA_MASK(miny:maxy,minx:maxx) = KIKS_ARENA_MASK(miny:maxy,minx:maxx)-binary_mask;
KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx) = KIKS_ARENA_COLORMASK(miny:maxy,minx:maxx)-color_mask;