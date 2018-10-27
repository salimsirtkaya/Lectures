% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_draw_roundobj(id)
global KIKS_MMPERPIXEL KIKS_2DVISUALIZE KIKS_ROUNDOBJECT KIKS_ROUNDOBJDATA KIKS_ROUNDOBJ_HDL KIKS_WALL_WIDTH KIKS_WALL_RENDER;

if (KIKS_2DVISUALIZE>0)
    kx = KIKS_ROUNDOBJDATA(id,1)/KIKS_MMPERPIXEL;
    ky = KIKS_ROUNDOBJDATA(id,2)/KIKS_MMPERPIXEL;
    set(KIKS_ROUNDOBJ_HDL(id),'xdata',KIKS_ROUNDOBJECT(1,:)+kx-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),'ydata',KIKS_ROUNDOBJECT(2,:)+ky-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));
end;

