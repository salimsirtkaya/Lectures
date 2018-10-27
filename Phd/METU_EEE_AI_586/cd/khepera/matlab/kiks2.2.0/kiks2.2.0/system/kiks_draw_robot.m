% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_draw_robot(id)
global KIKS_FIRE_HDL KIKS_GRIPPER_L_HDL KIKS_GRIPPER_R_HDL KIKS_GRIPPER_HDL KIKS_MMPERPIXEL KIKS_NR_HDL KIKS_LINVIS_GR_HDL KIKS_LINVIS_HDL KIKS_ROBOT_MATRIX KIKS_RBT_BODY KIKS_RBT_LAMP KIKS_RBT_DIOD KIKS_RBT_HDL KIKS_RBTSENS_HDL KIKS_RBTWHL_HDL KIKS_RBTLMP_HDL KIKS_RBTDIOD_HDL KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_PROX_DIR KIKS_PROX_ANG;
global KIKS_ROBOT_DATA KIKS_GRIPPER_ACTIVE KIKS_GRIPPER_XCOORD KIKS_GRIPPER_YCOORD KIKS_GRIPPER_GRP_XCOORD KIKS_GRIPPER_GRP_YCOORD;

KIKS_WALL_WIDTH_SCALED=KIKS_WALL_WIDTH/KIKS_MMPERPIXEL;
KIKS_WALL_RENDER_SCALED=KIKS_WALL_RENDER/KIKS_MMPERPIXEL;

set(KIKS_FIRE_HDL(1),'Visible','off');

kx = (KIKS_ROBOT_MATRIX(id,1,1)/KIKS_MMPERPIXEL);
ky = (KIKS_ROBOT_MATRIX(id,1,2)/KIKS_MMPERPIXEL);

if isempty(KIKS_GRIPPER_ACTIVE)
    set(KIKS_RBT_HDL(id),'xdata',(KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL)*KIKS_RBT_BODY(1,:)+kx-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',(KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL)*KIKS_RBT_BODY(2,:)+ky-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
else
    set(KIKS_RBT_HDL(id),'xdata',kx+(KIKS_RBT_BODY(1,:)*cos(-KIKS_ROBOT_MATRIX(id,1,3))-KIKS_RBT_BODY(2,:)*sin(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',ky+(KIKS_RBT_BODY(1,:)*sin(-KIKS_ROBOT_MATRIX(id,1,3))+KIKS_RBT_BODY(2,:)*cos(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
end;

r = KIKS_ROBOT_DATA(2,2)-2;
q = min(1,KIKS_ROBOT_DATA(2,2)/29);

prox_xvals = (r/KIKS_MMPERPIXEL)*cos(KIKS_PROX_ANG-KIKS_ROBOT_MATRIX(id,1,3))+(KIKS_ROBOT_MATRIX(id,1,1)/KIKS_MMPERPIXEL);
prox_yvals = (r/KIKS_MMPERPIXEL)*sin(KIKS_PROX_ANG-KIKS_ROBOT_MATRIX(id,1,3))+(KIKS_ROBOT_MATRIX(id,1,2)/KIKS_MMPERPIXEL);
prox_dirs  = KIKS_PROX_DIR+KIKS_ROBOT_MATRIX(id,1,3);

prox_xcord = [1  1 -2 -2]/KIKS_MMPERPIXEL;
prox_ycord = [3 -3 -3  3]/KIKS_MMPERPIXEL;

[tmp,sensors]=size(prox_xvals);

for sens=1:sensors,
    num=0;
    pos_x = prox_xvals(sens);
    pos_y = prox_yvals(sens);
    coss = cos(-prox_dirs(sens));
    sins = sin(-prox_dirs(sens));
    set(KIKS_RBTSENS_HDL(id,sens),'xdata',(prox_xcord*coss-prox_ycord*sins)+pos_x-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',(prox_xcord*sins+prox_ycord*coss)+pos_y-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
end
if (~isempty(KIKS_GRIPPER_ACTIVE))
    set(KIKS_GRIPPER_HDL(id),'xdata',kx+(KIKS_GRIPPER_XCOORD*cos(-KIKS_ROBOT_MATRIX(id,1,3))-KIKS_GRIPPER_YCOORD*sin(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',ky+(KIKS_GRIPPER_XCOORD*sin(-KIKS_ROBOT_MATRIX(id,1,3))+KIKS_GRIPPER_YCOORD*cos(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
    set(KIKS_GRIPPER_L_HDL(id),'xdata',kx+(KIKS_GRIPPER_GRP_XCOORD*cos(-KIKS_ROBOT_MATRIX(id,1,3))-KIKS_GRIPPER_GRP_YCOORD*sin(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',ky+(KIKS_GRIPPER_GRP_XCOORD*sin(-KIKS_ROBOT_MATRIX(id,1,3))+KIKS_GRIPPER_GRP_YCOORD*cos(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
    set(KIKS_GRIPPER_R_HDL(id),'xdata',kx+(KIKS_GRIPPER_GRP_XCOORD*cos(-KIKS_ROBOT_MATRIX(id,1,3))-(-KIKS_GRIPPER_GRP_YCOORD)*sin(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',ky+(KIKS_GRIPPER_GRP_XCOORD*sin(-KIKS_ROBOT_MATRIX(id,1,3))+(-KIKS_GRIPPER_GRP_YCOORD)*cos(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
end;

cam_xcoord = [-10*q  10*q  10*q -10*q]/KIKS_MMPERPIXEL;
cam_ycoord = [-10*q -10*q  10*q  10*q]/KIKS_MMPERPIXEL;
set(KIKS_LINVIS_HDL(id),'xdata',kx+(cam_xcoord*cos(-KIKS_ROBOT_MATRIX(id,1,3))-cam_ycoord*sin(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',ky+(cam_xcoord*sin(-KIKS_ROBOT_MATRIX(id,1,3))+cam_ycoord*cos(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));

gr_xcoord = [-20*q -10*q -10*q -20*q]/KIKS_MMPERPIXEL;
gr_ycoord = [ -8*q  -8*q   8*q   8*q]/KIKS_MMPERPIXEL;
set(KIKS_LINVIS_GR_HDL(id),'xdata',kx+(gr_xcoord*cos(-KIKS_ROBOT_MATRIX(id,1,3))-gr_ycoord*sin(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',ky+(gr_xcoord*sin(-KIKS_ROBOT_MATRIX(id,1,3))+gr_ycoord*cos(-KIKS_ROBOT_MATRIX(id,1,3)))-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));

inner = floor(KIKS_ROBOT_DATA(2,1)/2)-2;
outer = ceil(KIKS_ROBOT_DATA(2,1)/2);
whl_xcoord = [  0  -7  -7    7   7     0   0   7    7  -7  -7     0]/KIKS_MMPERPIXEL;
whl_ycoord = [-inner -inner -outer  -outer  -inner  -inner  inner  inner   outer  outer   inner   inner]/KIKS_MMPERPIXEL;
set(KIKS_RBTWHL_HDL(id),'xdata',(whl_xcoord*cos(-KIKS_ROBOT_MATRIX(id,1,3))-whl_ycoord*sin(-KIKS_ROBOT_MATRIX(id,1,3)))+kx-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',(whl_xcoord*sin(-KIKS_ROBOT_MATRIX(id,1,3))+whl_ycoord*cos(-KIKS_ROBOT_MATRIX(id,1,3)))+ky-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));

set(KIKS_RBTDIOD_HDL(id,1),'xdata',((22*q)/KIKS_MMPERPIXEL)*cos(-KIKS_ROBOT_MATRIX(id,1,3)+pi/6)+KIKS_RBT_DIOD(1,:)+kx-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',((22*q)/KIKS_MMPERPIXEL)*sin(-KIKS_ROBOT_MATRIX(id,1,3)+pi/6)+KIKS_RBT_DIOD(2,:)+ky-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
set(KIKS_RBTDIOD_HDL(id,2),'xdata',((22*q)/KIKS_MMPERPIXEL)*cos(-KIKS_ROBOT_MATRIX(id,1,3)+pi/6+pi/12)+KIKS_RBT_DIOD(1,:)+kx-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED),'ydata',((22*q)/KIKS_MMPERPIXEL)*sin(-KIKS_ROBOT_MATRIX(id,1,3)+pi/6+pi/12)+KIKS_RBT_DIOD(2,:)+ky-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED));
