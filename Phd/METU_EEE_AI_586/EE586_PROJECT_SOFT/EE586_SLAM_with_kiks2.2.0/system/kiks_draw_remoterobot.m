% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_draw_remoterobot(id,kx,ky,ang,n,r)
global KIKS_MMPERPIXEL KIKS_ARENA_HDL KIKS_REMOTEKHEPDIOD_HDL KIKS_REMOTEKHEPWHL_HDL KIKS_REMOTEKHEP_HDL KIKS_MMPERPIXEL KIKS_NR_HDL KIKS_LINVIS_GR_HDL KIKS_LINVIS_HDL KIKS_ROBOT_MATRIX KIKS_RBT_BODY KIKS_RBT_LAMP KIKS_RBT_DIOD KIKS_RBT_HDL KIKS_RBTSENS_HDL KIKS_RBTWHL_HDL KIKS_RBTLMP_HDL KIKS_RBTDIOD_HDL KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_PROX_DIR KIKS_PROX_ANG;

scale = r/29;

KIKS_WALL_WIDTH_SCALED=KIKS_WALL_WIDTH/KIKS_MMPERPIXEL;
KIKS_WALL_RENDER_SCALED=KIKS_WALL_RENDER/KIKS_MMPERPIXEL;

if ~isempty(n)
    KIKS_REMOTEKHEP_HDL(id)=kiks_remotekheppatch(id);
    KIKS_REMOTEKHEPWHL_HDL(id)=patch('Facecolor',[.5 .5 .6],'EdgeColor','none','Erase','xor','tag',sprintf('remoteKhep %d',id));
    KIKS_REMOTEKHEPDIOD_HDL(id,1)=patch('Facecolor',[.5 .5 .6],'EdgeColor','none','Erase','xor','tag',sprintf('remoteKhep %d',id));
    KIKS_REMOTEKHEPDIOD_HDL(id,2)=patch('Facecolor',[.5 .5 .6],'EdgeColor','none','Erase','xor','tag',sprintf('remoteKhep %d',id));
end;

set(KIKS_REMOTEKHEP_HDL(id),'xdata',KIKS_RBT_BODY(1,1:3:end)*(r/KIKS_MMPERPIXEL)+floor(kx/KIKS_MMPERPIXEL)-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',KIKS_RBT_BODY(2,1:3:end)*(r/KIKS_MMPERPIXEL)+floor(ky/KIKS_MMPERPIXEL)-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));

whl_xcoord = [ -15 -15  20 ]/KIKS_MMPERPIXEL*scale;
whl_ycoord = [ -10  10   0 ]/KIKS_MMPERPIXEL*scale;
set(KIKS_REMOTEKHEPWHL_HDL(id),'xdata',(whl_xcoord*cos(-ang)-whl_ycoord*sin(-ang))+floor(kx/KIKS_MMPERPIXEL)-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',(whl_xcoord*sin(-ang)+whl_ycoord*cos(-ang))+floor(ky/KIKS_MMPERPIXEL)-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
