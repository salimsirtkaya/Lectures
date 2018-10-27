% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_draw_light(id)
global KIKS_MMPERPIXEL KIKS_2DVISUALIZE KIKS_OBJECT_LIGHT KIKS_LIGHTDATA KIKS_LIGHT_HDL KIKS_WALL_WIDTH KIKS_WALL_RENDER;

if (KIKS_2DVISUALIZE>0)
    kx = KIKS_LIGHTDATA(id,1)/KIKS_MMPERPIXEL;
    ky = KIKS_LIGHTDATA(id,2)/KIKS_MMPERPIXEL;
    set(KIKS_LIGHT_HDL(id),'xdata',KIKS_OBJECT_LIGHT(1,:)+kx-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),'ydata',KIKS_OBJECT_LIGHT(2,:)+ky-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));
end;

