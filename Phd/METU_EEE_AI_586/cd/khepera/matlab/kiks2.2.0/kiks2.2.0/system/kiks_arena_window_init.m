% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_arena_window_init(pos)
global KIKS_REGCODE KIKS_RBTARRAY KIKS_PORT KIKS_trace KIKS_tracestep KIKS_BALL_HDL KIKS_BALLARRAY KIKS_ARENA_COLORMASK KIKS_ARENA_MX KIKS_TIMESCALE KIKS_ROBOT_DATA KIKS_PROX_POS KIKS_LIGHT_POS KIKS_SPDC KIKS_SESSIONACTIVE;
global KIKS_ARENA_HDL KIKS_RBT_HDL KIKS_RBTSENS_HDL KIKS_RBTWHL_HDL KIKS_RBTLMP_HDL;
global KIKS_RBTMASK KIKS_2DVISUALIZE KIKS_LIGHTARRAY KIKS_LIGHT_HDL KIKS_2D_GRID;
global KIKS_COLOR_BACKGROUND KIKS_ARENA_UPDATE_FREQ KIKS_ARENA_UPDATE_COUNTER KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_GUI_HDL KIKS_RBTARRAY KIKS_ROUNDOBJARRAY;
global KIKS_ARENA_IMG_XS KIKS_ARENA_IMG_YS KIKS_MMPERPIXEL KIKS_REMOTE_ARRAY KIKS_REMOTEKHEPDIOD_HDL KIKS_REMOTEKHEPWHL_HDL KIKS_REMOTEKHEP_HDL;


KIKS_REMOTEKHEP_HDL=[];

bodyx=KIKS_ROBOT_DATA(2,2)*(cos([KIKS_ROBOT_DATA(1,3):pi/16:2*pi+KIKS_ROBOT_DATA(1,3)]));
bodyy=-KIKS_ROBOT_DATA(2,2)*(sin([KIKS_ROBOT_DATA(1,3):pi/16:KIKS_ROBOT_DATA(1,3)+2*pi]));
sensx=[20*cos(KIKS_ROBOT_DATA(1,3)) -6*sin(KIKS_ROBOT_DATA(1,3)) 6*sin(KIKS_ROBOT_DATA(1,3)) 15*cos(KIKS_ROBOT_DATA(1,3))];
sensy=[-20*sin(KIKS_ROBOT_DATA(1,3)) -6*cos(KIKS_ROBOT_DATA(1,3)) 6*cos(KIKS_ROBOT_DATA(1,3)) -15*sin(KIKS_ROBOT_DATA(1,3))];

kx = KIKS_ROBOT_DATA(1,1);
ky = KIKS_ROBOT_DATA(1,2);

khepx=[bodyx sensx];
khepy=[bodyy sensy];

[xs,ys]=size(KIKS_ARENA_MX);
h=findobj('Name','KiKS');
mainpos=get(h,'Position');

KIKS_ARENA_HDL=findobj(KIKS_GUI_HDL,'tag','arena_axes');
[cl,tmp]=size(colormap); % cl = number of colors to use

arena_without_walls = KIKS_ARENA_MX(1+floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)-floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL):xs-floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),1+floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)-floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL):ys-floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));
color_without_walls = KIKS_ARENA_COLORMASK(1+floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)-floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL):xs-floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL),1+floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)-floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL):ys-floor(KIKS_WALL_WIDTH/KIKS_MMPERPIXEL)+floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL));

I=find(arena_without_walls==1);
arena_without_walls(I)=ceil(color_without_walls(I)/(255/cl))+1;

[xs,ys]=size(arena_without_walls);


map=gray;
map(1,:)=KIKS_COLOR_BACKGROUND;
colormap(map);
X=[1 ys]; Y=[1 xs];
if KIKS_2D_GRID>0
    spacing=floor(KIKS_WALL_RENDER/KIKS_MMPERPIXEL);
    arena_without_walls(round(spacing+10/KIKS_MMPERPIXEL:10/KIKS_MMPERPIXEL:xs-spacing),round(spacing+1:ys-spacing))=100/(255/cl);
    arena_without_walls(round(spacing+1:xs-spacing),round(spacing+10/KIKS_MMPERPIXEL:10/KIKS_MMPERPIXEL:ys-spacing))=100/(255/cl);
    arena_without_walls(round(spacing+100/KIKS_MMPERPIXEL:100/KIKS_MMPERPIXEL:xs-spacing),round(spacing+1:ys-spacing))=200/(255/cl);
    arena_without_walls(round(spacing+1:xs-spacing),round(spacing+100/KIKS_MMPERPIXEL:100/KIKS_MMPERPIXEL:ys-spacing))=200/(255/cl);
    image(X,Y,abs(arena_without_walls));
else
    image(X,Y,abs(arena_without_walls));
end;
set(KIKS_ARENA_HDL,'xlim',[0 ys]);
set(KIKS_ARENA_HDL,'ylim',[0 xs]);
[KIKS_ARENA_IMG_YS,KIKS_ARENA_IMG_XS]=size(arena_without_walls);
H=KIKS_ARENA_HDL;
set(H,'PlotBoxAspectRatioMode','auto');
set(H,'Visible','off');

axes(KIKS_ARENA_HDL);
[rows,cols]=size(KIKS_RBTARRAY);
for i=1:cols,
    kiks_gui_robotvis(KIKS_RBTARRAY(i));
    kiks_draw_robot(KIKS_RBTARRAY(i));
end;
[rows,cols]=size(KIKS_ROUNDOBJARRAY);
for i=1:cols,
    kiks_gui_roundobjvis(KIKS_ROUNDOBJARRAY(i));
    kiks_draw_roundobj(KIKS_ROUNDOBJARRAY(i));
end;
[rows,cols]=size(KIKS_LIGHTARRAY);
for i=1:cols,
    KIKS_LIGHT_HDL(i)=kiks_patch_light(i);
    kiks_draw_light(KIKS_LIGHTARRAY(i));
end;
[rows,cols]=size(KIKS_BALLARRAY);
for i=1:cols,
    KIKS_BALL_HDL(i)=kiks_patch_ball(i);
    kiks_draw_ball(KIKS_BALLARRAY(i));
end;

openports=max(KIKS_PORT);
hold on;
if ~isempty(openports) & openports==0
    % draw trace lines
    [rows,cols]=size(KIKS_RBTARRAY);
    col(1)='w'; col(2)='y'; col(3)='c';
    
    for i=1:cols
        id=KIKS_RBTARRAY(i);
        try
            plot(KIKS_trace(id,1:ceil(KIKS_tracestep(id)),1)/KIKS_MMPERPIXEL,KIKS_trace(id,1:ceil(KIKS_tracestep(id)),2)/KIKS_MMPERPIXEL,sprintf('%s.-',col(mod(id,5)+1)));  
        end;
    end;
end;

if ~isempty(KIKS_REMOTE_ARRAY)
    entries=8; % entries per object
    nr = size(KIKS_REMOTE_ARRAY,1)/entries;
    for i=0:nr-1
        id=KIKS_REMOTE_ARRAY(1+i*entries);
        type=KIKS_REMOTE_ARRAY(2+i*entries);
        x=KIKS_REMOTE_ARRAY(3+i*entries);
        y=KIKS_REMOTE_ARRAY(4+i*entries);
        ang=KIKS_REMOTE_ARRAY(5+i*entries);
        r=KIKS_REMOTE_ARRAY(6+i*entries);
        kiks_draw_remoterobot(id,x,y,ang,1,r);
    end;
end;
%kiks_update_remote;

H=findobj(KIKS_GUI_HDL,'Tag','toggle2dvis');
if (KIKS_2DVISUALIZE==0)
    set(H,'String','enable visualization'); 
else
    set(H,'String','disable visualization'); 
end;

H=findobj(KIKS_GUI_HDL,'Tag','arena_redraw');
set(H,'Enable','on');
H=findobj(KIKS_GUI_HDL,'Tag','arena_grid');
set(H,'Enable','on');
set(KIKS_ARENA_HDL,'tag','arena_axes');
drawnow;
kiks_mouse_moveobj on;