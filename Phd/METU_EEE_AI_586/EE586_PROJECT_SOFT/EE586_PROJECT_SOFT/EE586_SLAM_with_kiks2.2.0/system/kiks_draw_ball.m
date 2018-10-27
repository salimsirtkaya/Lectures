% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_draw_ball(id)
global KIKS_MMPERPIXEL KIKS_OBJECT_BALL KIKS_OBJECT_SMALLBALL KIKS_BALL_HDL KIKS_BALLDATA KIKS_2DVISUALIZE KIKS_WALL_WIDTH KIKS_WALL_RENDER;

if (KIKS_2DVISUALIZE==0) return; end; % no need to draw if the arena isn't being shown

kx = KIKS_BALLDATA(id,1)/KIKS_MMPERPIXEL;
ky = KIKS_BALLDATA(id,2)/KIKS_MMPERPIXEL;
cylinder=KIKS_BALLDATA(id,5);

if cylinder
    set(KIKS_BALL_HDL(id),'xdata',KIKS_OBJECT_SMALLBALL(1,:)+kx-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),'ydata',KIKS_OBJECT_SMALLBALL(2,:)+ky-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));
else
    set(KIKS_BALL_HDL(id),'xdata',KIKS_OBJECT_BALL(1,:)+kx-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),'ydata',KIKS_OBJECT_BALL(2,:)+ky-(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));
end;    