% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function init_result = kiks_init(arena,colormask)
global KIKS_GUI_COLOR KIKS_PORT KIKS_COLOR_BACKGROUND KIKS_OBJECT_BALL_SMALLRATIO KIKS_ROBOT_RADIUS KIKS_NET_BUFSIZ KIKS_FID KIKS_MMPERPIXEL KIKS_ARENA_MX KIKS_ARENA_MASK KIKS_TIMESCALE KIKS_ROBOT_DATA KIKS_PROX_POS KIKS_LIGHT_POS KIKS_SPDC KIKS_SESSIONACTIVE KIKS_VERSION;
global KIKS_2D_GRID KIKS_ARENA_HDL KIKS_RBT_HDL KIKS_GUI_HDL KIKS_RBTMASK KIKS_RBTMASK_COL KIKS_2DVISUALIZE KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_RBTLIST KIKS_INT_LIMIT KIKS_INTERPOLATE KIKS_INT_LIST KIKS_INT_CELL KIKS_ACC_LIST KIKS_ACC_CELL KIKS_STAT_LIST KIKS_STAT_CELL KIKS_SENS_LIST KIKS_SENS_CELL KIKS_OBJS_CELL;
global KIKS_PROX_DIR KIKS_PROX_ANG KIKS_RBT_BODY KIKS_RBT_LAMP KIKS_RBT_DIOD KIKS_MONITOR_WIN KIKS_MONITOR_ON;
global KIKS_ROUNDOBJMASK KIKS_ROUNDOBJMASK_COL KIKS_ROUNDOBJECT KIKS_ROUNDOBJECT_RADIUS;
global KIKS_KSEND_CONSTANT KIKS_CALIBRATE_BAUD KIKS_REGCODE KIKS_OBJECT_SMALLBALL_MASK_COL;
global KIKS_MAX_SPEED KIKS_WALL_CLOCK KIKS_LINKTIME;
global KIKS_PROX_NNET1 KIKS_PROX_NNET2 KIKS_PROX_NNET3 KIKS_PROX_NNET4 KIKS_PROX_NNET5 KIKS_PROX_NNET6 KIKS_PROX_NNET7 KIKS_PROX_NNET8 KIKS_PROX_MINRAND KIKS_PROX_MAXRAND;
global KIKS_PROX_NETBUF1 KIKS_PROX_NETBUF2 KIKS_PROX_NETBUF3 KIKS_PROX_NETBUF4 KIKS_PROX_NETBUF5 KIKS_PROX_NETBUF6 KIKS_PROX_NETBUF7 KIKS_PROX_NETBUF8;
global KIKS_SIMPROX_MAXDIST KIKS_SIMPROX_STEPLENGTH KIKS_HALT_BOOL;
global KIKS_OBJECT_LIGHT_RADIUS KIKS_OBJECT_LIGHT KIKS_OBJECT_LIGHT_MASK KIKS_LIGHT_NNET_ARRAY KIKS_PROX_NNET_ARRAY;
global KIKS_OBJECT_BALL KIKS_OBJECT_BALL_MASK KIKS_OBJECT_BALL_MASK_COL KIKS_OBJECT_BALL_RADIUS
global KIKS_COMP_LIST KIKS_COMP_CELL KIKS_COMPUTER_SPEED KIKS_COMPUTER_SPEED_SIM KIKS_COLOR_BACKGROUND KIKS_COLOR_BALL KIKS_COLOR_CYLINDER KIKS_COLOR_ROBOT KIKS_OBJECT_SMALLBALL KIKS_OBJECT_SMALLBALL_RADIUS KIKS_OBJECT_SMALLBALL_MASK;
global KIKS_AMETHOD_CELL KIKS_REMOTEKHEP_MTRX KIKS_SIM_STEP KIKS_SIM_PAUSE KIKS_SIM_PROX_STEP KIKS_K213_STEP KIKS_502500 KIKS_1250 KIKS_GUI_LASTPOS KIKS_SETTINGS_DIR KIKS_AVAIL_NNET KIKS_TRACE_MAX KIKS_CALLSIGNS;
global KIKS_ROUND_MASK_CELL KIKS_ROUND_MASK KIKS_MOVLOCK KIKS_GRIPPER_ACTIVE;
global KIKS_KIKSNET_PROTOCOL_VERSION KIKS_HISTORY_HDL KIKS_LOG_HISTORY KIKS_STATUS_BUFFER KIKS_STATUS_BUFFER_CNT KIKS_KIKSNET_REPLY KIKS_PROXIMITY_DIRECTIONS KIKS_PROXIMITY_POSITIONS KIKS_SIMPROX_STEPS KIKS_TURRETS KIKS_TOOLBOX_IMAGES KIKS_ROBOT_DIAMETER KIKS_ROBOT_DISTANCE_BETWEEN_WHEELS KIKS_SIM_PROX_SCALE KIKS_SIM_PROX_DIST KIKS_LIC_CDE KIKS_LIC_VFK KIKS_LIC_LIC;

rand('state',sum(100*clock));

init_result = 0;
KIKS_GUI_HDL=[];

KIKS_VERSION='2.2.0';
KIKS_KIKSNET_PROTOCOL_VERSION=1;

KIKS_GUI_COLOR=[200/255 200/255 200/255];

KIKS_LIC_CDE=[];
KIKS_LIC_VFK=[];
KIKS_LIC_LIC=[];

KIKS_GRIPPER_ACTIVE=[];
rand('state',sum(100*clock));

kiks_preferences; % Load preferences
if KIKS_MMPERPIXEL<1
    error('KIKS_MMPERPIXEL cannot be less than 1!\nEdit kiks_preferences.m to change the value of KIKS_MMPERPIXEL.');
end;

% Check path
try
    path(kiks_getpath,path);
    path(kiks_getsystempath,path);
    path([kiks_getpath 'kMatlab'],path);
catch
    error('Could not find KiKS path in Matlab path settings. Run kiks_setup from the kiks root directory.');
end;
if ~isempty(KIKS_SETTINGS_DIR) path(KIKS_SETTINGS_DIR,path); end; % don't need to save this

path(path); % Let Matlab validate path settings   

h=findobj('Name','KiKS');
delete(h);
if(~isempty(h))
    fprintf('<KiKS> warning:  A KiKS zombie session has been detected and terminated.\n');
    fprintf('<KiKS> warning:  This usually happens when you have used the ''clear all'' command.\n');
end;

% define graphics and gui
KIKS_GUI_HDL=kiks_gui;
set(KIKS_GUI_HDL,'CloseRequestFcn','kiks_quit');
scrn=get(findobj('type','root'),'screensize');
pos=get(KIKS_GUI_HDL,'position');
pos(2)=scrn(4)-pos(4)-22;
pos(1)=4;
set(KIKS_GUI_HDL,'position',pos);
KIKS_GUI_LASTPOS=pos;
kiks_gui_loghistory;
drawnow;

robotlist = {};
robots = dir([kiks_getpath 'robots/*.m']);
[nr,tmp]=size(robots);
for i=1:nr
    robotlist{i} = strrep(strrep(char(robots(i).name),'.m',''),'_',' ');
end;

KIKS_TURRETS = {};
turretlist = {};
turrets = dir([kiks_getpath 'turrets/*.m']);
[nr,tmp]=size(turrets);
for i=1:nr
    turretname = strrep(char(turrets(i).name),'.m','');
    id = feval(turretname);
    KIKS_TURRETS{id}=turretname;
    kiks_status(sprintf('Turret #%d located (%s)',id,turretname));
end;
KIKS_KIKSNET_REPLY = '';
eval(char(robotlist(1)));

KIKS_MOVLOCK=0;
KIKS_SIM_PROX_DIST=KIKS_PROXIMITY_SENSORS_RANGE;
KIKS_1250=[KIKS_MMPERPIXEL:ceil(KIKS_SIM_PROX_STEP/KIKS_MMPERPIXEL):floor(KIKS_SIM_PROX_DIST/KIKS_MMPERPIXEL)];
[tmp,sz]=size(KIKS_1250);
KIKS_1250=KIKS_1250(2:sz); % don't include (0,0)
KIKS_502500=[floor(50/KIKS_MMPERPIXEL):ceil(KIKS_K213_STEP/KIKS_MMPERPIXEL):floor(500/KIKS_MMPERPIXEL)];
KIKS_HALT_BOOL=0;
KIKS_MAX_SPEED=2;
KIKS_WALL_CLOCK=1;
KIKS_COMPUTER_SPEED=0;
KIKS_FID=-1;
KIKS_NET_BUFSIZ=65535;
retstr=kiks_load_settings;

KIKS_TOOLBOX_IMAGES=ver('images');

nv=ver('nnet');
if ~isempty(nv)
    netpath1=which('nnet_prox1.mat');
    netpath2=which('nnet_prox2.mat');
    netpath3=which('nnet_prox3.mat');
    netpath4=which('nnet_prox4.mat');
    netpath5=which('nnet_prox5.mat');
    netpath6=which('nnet_prox6.mat');
    netpath7=which('nnet_prox7.mat');
    netpath8=which('nnet_prox8.mat');
    if ~isempty(netpath1) & ~isempty(netpath2) & ~isempty(netpath3) & ~isempty(netpath4) & ~isempty(netpath5) & ~isempty(netpath6) & ~isempty(netpath7) & ~isempty(netpath8)
        KIKS_AVAIL_NNET=1;
        load(netpath1); KIKS_PROX_NNET1=net;   
        load(netpath2); KIKS_PROX_NNET2=net;
        load(netpath3); KIKS_PROX_NNET3=net;
        load(netpath4); KIKS_PROX_NNET4=net;
        load(netpath5); KIKS_PROX_NNET5=net;
        load(netpath6); KIKS_PROX_NNET6=net;
        load(netpath7); KIKS_PROX_NNET7=net;
        load(netpath8); KIKS_PROX_NNET8=net;
    else
        KIKS_AVAIL_NNET=0;
    end;
else
    KIKS_AVAIL_NNET=0;
end;

load([kiks_getsystempath 'nnet_array.mat']);
KIKS_SIMPROX_MAXDIST=KIKS_SIM_PROX_DIST; % mm to track
nnetarrsz = size(KIKS_PROX_NNET_ARRAY);
KIKS_SIMPROX_STEPS = nnetarrsz(end);
nnetsteps = nnetarrsz(end)-1;
nnetsteplen = 50/nnetsteps;
KIKS_SIM_PROX_SCALE=nnetsteplen*(KIKS_SIM_PROX_DIST/50);

KIKS_PROX_MINRAND=0.90;
KIKS_PROX_MAXRAND=1.0;

if isempty(KIKS_KSEND_CONSTANT)
    % Could not find computer-specific settings
    KIKS_KSEND_CONSTANT=0;
    KIKS_CALIBRATE_BAUD=0;
end;

cde=0;
lic=0;
vfk=0;
name='';
org='';
email='';
reginfo='';
KIKS_REGCODE=[];
datapath = which('kiks_reginfo.mat');
cde='UNREGISTERED';
kiks_status(sprintf(' \nKiKS v%s (c) 2000-2004 Theodor Storm <theodor@tstorm.se>\nhttp://www.tstorm.se\nMany thanks to Peter Rydesäter (Peter.Rydesater@mh.se)\nfor the Matlab tcp/ip toolbox. Download the latest version at\nhttp://petrydpc.ite.mh.se/tools/.\n',KIKS_VERSION));

if ~isempty(datapath)
    load(datapath);
    KIKS_LIC_CDE=cde;
    KIKS_LIC_VFK=vfk;
    KIKS_LIC_LIC=lic;
    KIKS_REGCODE=cde; 
end;

KIKS_REGCODE=cde;

KIKS_SESSIONACTIVE=1;
kiks_status(retstr);

KIKS_MONITOR_WIN=[];
KIKS_MONITOR_ON=[];
KIKS_REMOTEKHEP_MTRX=[];

prox_dir = [90 45 10 -10 -45 -90 180 -180];
prox_ang = [-68 -43 -13 13 43 68 158 -158];
KIKS_PROX_DIR = (pi/180)*prox_dir;
KIKS_PROX_ANG = (pi/180)*prox_ang;
num=0;

KIKS_COLOR_BACKGROUND=[0.25 0.3 0.35];

KIKS_SIM_STEP=0;
KIKS_SIM_PAUSE=0;
KIKS_COMPUTER_SPEED_SIM=1;
KIKS_LINKTIME=0;
KIKS_2D_GRID=0;
KIKS_WALL_WIDTH=128; % mm
KIKS_WALL_RENDER=0; % mm
KIKS_RBTLIST={};
KIKS_INT_LIMIT=25;
KIKS_INTERPOLATE=1;
KIKS_INT_CELL={'1 mm' '2 mm' '5 mm' '10 mm' '15 mm' '20 mm' '25 mm' 'no limit'};

KIKS_INT_LIST=[1 2 5 10 15 20 25 0];
KIKS_ACC_CELL={'Wall clock (simplistic)' 'High precision (realistic)'};
KIKS_ACC_LIST=[1 -1];
KIKS_STAT_LIST=[10 15 20 25 30 40 0];
KIKS_STAT_CELL={'10 updates/sec' '15 updates/sec' '20 updates/sec' '25 updates/sec' '30 updates/sec' '40 updates/sec' 'no limit'};
KIKS_SENS_LIST=[1 2 5 10];
KIKS_SENS_CELL={'1 mm' '2 mm' '5 mm' '10 mm'};
KIKS_OBJS_CELL={'light','ball','cylinder'};
KIKS_COMP_LIST=[20.33 15.11 10.25 10.01 5.87 5.70 5.47 4.39 3.27 3.18];
KIKS_COMP_CELL={'143Mhz UltraSPARC' '300Mhz Celeron-A' '300Mhz UltraSPARC-II' '450Mhz Celeron-A' '733Mhz Pentium III' '900Mhz Celeron II' '800Mhz Pentium III EB' '1Ghz Pentium III' '1.2Ghz AMD Athlon' '1.4Ghz AMD Athlon'};
KIKS_AMETHOD_CELL={'emulate CPU speed' 'target speed: 100%'};

res=0;

KIKS_TIMESCALE = -1;
KIKS_2DVISUALIZE = 0; % set to higher than 0 to draw arena

kiks_set_robot_data;

% general mask for round objects
max_radius=100;
MX=floor(max_radius/KIKS_MMPERPIXEL)*2+1;
MY=floor(max_radius/KIKS_MMPERPIXEL)*2+1;
KIKS_ROUND_MASK_CELL=cell(1,100);
KIKS_ROUND_MASK=zeros(MX,MY);
for x=1:MX,
    for y=1:MY,
        if sqrt((x-(MX+1)/2)*(x-(MX+1)/2)+(y-(MY+1)/2)*(y-(MY+1)/2))<=max_radius/KIKS_MMPERPIXEL KIKS_ROUND_MASK(x,y)=1; end;
    end;   
end;

KIKS_PORT = [0];

KIKS_ROUNDOBJECT_RADIUS=16;
KIKS_ROUNDOBJECT(1,:)=(KIKS_ROUNDOBJECT_RADIUS/KIKS_MMPERPIXEL)*(cos(pi/4:pi/4:2*pi));
KIKS_ROUNDOBJECT(2,:)=-(KIKS_ROUNDOBJECT_RADIUS/KIKS_MMPERPIXEL)*(sin(pi/4:pi/4:2*pi));

KIKS_OBJECT_LIGHT_RADIUS=16;

KIKS_OBJECT_LIGHT(1,:)=cos(pi/10:pi/10:2*pi);
KIKS_OBJECT_LIGHT(2,:)=sin(pi/10:pi/10:2*pi);
[tmp,sz]=size(KIKS_OBJECT_LIGHT(1,:));
KIKS_OBJECT_LIGHT(1,2:2:sz)=KIKS_OBJECT_LIGHT(1,2:2:sz)*(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL);
KIKS_OBJECT_LIGHT(2,2:2:sz)=KIKS_OBJECT_LIGHT(2,2:2:sz)*(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL);
KIKS_OBJECT_LIGHT(1,1:2:sz)=KIKS_OBJECT_LIGHT(1,1:2:sz)*(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL-(KIKS_OBJECT_LIGHT_RADIUS*0.66)/KIKS_MMPERPIXEL);
KIKS_OBJECT_LIGHT(2,1:2:sz)=KIKS_OBJECT_LIGHT(2,1:2:sz)*(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL-(KIKS_OBJECT_LIGHT_RADIUS*0.66)/KIKS_MMPERPIXEL);

MX=floor(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL)*2+1;
MY=floor(KIKS_OBJECT_LIGHT_RADIUS/KIKS_MMPERPIXEL)*2+1;
KIKS_OBJECT_LIGHT_MASK=kiks_scale(KIKS_ROUND_MASK,MX,MY);

KIKS_OBJECT_BALL_RADIUS=32;
KIKS_OBJECT_BALL_SMALLRATIO=1/2;
KIKS_OBJECT_BALL(1,:)=(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL)*(cos(pi/8:pi/8:2*pi));
KIKS_OBJECT_BALL(2,:)=-(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL)*(sin(pi/8:pi/8:2*pi));
MX=floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL)*2+1;
MY=floor(KIKS_OBJECT_BALL_RADIUS/KIKS_MMPERPIXEL)*2+1;
KIKS_OBJECT_BALL_MASK=kiks_scale(KIKS_ROUND_MASK,MX,MY);
KIKS_OBJECT_BALL_MASK_COL=KIKS_OBJECT_BALL_MASK*KIKS_COLOR_BALL;

KIKS_OBJECT_SMALLBALL_RADIUS=floor(KIKS_OBJECT_BALL_RADIUS*KIKS_OBJECT_BALL_SMALLRATIO);
KIKS_OBJECT_SMALLBALL(1,:)=(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL)*(cos(pi/8:pi/8:2*pi));
KIKS_OBJECT_SMALLBALL(2,:)=-(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL)*(sin(pi/8:pi/8:2*pi));
MX=floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL)*2+1;
MY=floor(KIKS_OBJECT_SMALLBALL_RADIUS/KIKS_MMPERPIXEL)*2+1;
KIKS_OBJECT_SMALLBALL_MASK=kiks_scale(KIKS_ROUND_MASK,MX,MY);
KIKS_OBJECT_SMALLBALL_MASK_COL=KIKS_OBJECT_SMALLBALL_MASK*KIKS_COLOR_CYLINDER;

MX=2*floor(KIKS_ROUNDOBJECT_RADIUS/KIKS_MMPERPIXEL)+1;
MY=MX;
KIKS_ROUNDOBJMASK=kiks_scale(KIKS_ROUND_MASK,MY,MX);
KIKS_ROUNDOBJMASK_COL=KIKS_ROUNDOBJMASK*KIKS_COLOR_CYLINDER;

if nargin<1 arena=[]; end
if nargin<2 colormask=[]; end

KIKS_PROX_NNET_ARRAY=double(KIKS_PROX_NNET_ARRAY);



h=findobj(KIKS_GUI_HDL,'Tag','kheppopup');
set(h,'String',KIKS_RBTLIST);
h=findobj(KIKS_GUI_HDL,'Tag','timescale_popup');
set(h,'string',KIKS_ACC_CELL);
H=findobj(KIKS_GUI_HDL,'Tag','toggle2dvis');
set(H,'String','enable visualization'); 
h=findobj(KIKS_GUI_HDL,'Tag','acceleration_method');
set(h,'string',KIKS_AMETHOD_CELL);
kiks_setinterpolate;
kiks_gui_setlimitlistbox;
kiks_gui_getlimitlistbox;
kiks_gui_setstatlistbox;
kiks_gui_getstatlistbox;
kiks_gui_setobjlistbox;
kiks_gui_ixprox;
if KIKS_COMPUTER_SPEED>0
    % Insert this computers' speed in the list
    ix=1;
    [tmp,sz]=size(KIKS_COMP_CELL);
    while ix<=sz & KIKS_COMPUTER_SPEED<KIKS_COMP_LIST(ix)
        ix=ix+1;
    end;
    for i=sz:-1:ix
        KIKS_COMP_CELL(i+1)=KIKS_COMP_CELL(i);
        KIKS_COMP_LIST(i+1)=KIKS_COMP_LIST(i);
    end;
    
    KIKS_COMP_CELL(ix)={'This CPU (emulation off)'};
    KIKS_COMP_LIST(ix)=KIKS_COMPUTER_SPEED;
    kiks_gui_setcomplistbox(ix);
else
    [tmp,sz]=size(KIKS_COMP_CELL);
    for i=sz:-1:1
        KIKS_COMP_CELL(i+1)=KIKS_COMP_CELL(i);
        KIKS_COMP_LIST(i+1)=KIKS_COMP_LIST(i);
    end;
    KIKS_COMP_CELL(1)={'This CPU (off)'};
    KIKS_COMP_LIST(1)=0;
    kiks_gui_setcomplistbox(1);
end;
kiks_gui_getcomplistbox;
kiks_gui_settimescale;
kiks_gui_gettimescale;

h=findobj(KIKS_GUI_HDL,'Tag','compspeed_popup');
if KIKS_COMPUTER_SPEED==0
    set(h,'Enable','off');
else
    set(h,'Enable','on');
end;
kiks_gui_getaccmethod;
h=findobj(KIKS_GUI_HDL,'Tag','simulate_popup');
set(h,'String',robotlist);
set(h,'Val',1);

h=findobj(KIKS_GUI_HDL,'Tag','version');
set(h,'string',sprintf('v%s',KIKS_VERSION));

h=findobj(KIKS_GUI_HDL,'Tag','version');

kiks_arena(arena,colormask);
H=findobj(KIKS_GUI_HDL,'type','patch');
delete(H);
kiks_arena_window_open;

[res,onlineversion]=kiks_checkversion;

if res==1 & strcmp(KIKS_VERSION,onlineversion)==0
    msg=msgbox(sprintf('KiKS %s is available for download at http://www.tstorm.se',onlineversion),'New KiKS version available');
end;

if res==-1
    init_result=-1;
end;

if strcmp(KIKS_REGCODE,'UNREGISTERED')~=1     
    h=findobj(KIKS_GUI_HDL,'Tag','reginfo');
    set(h,'string',KIKS_REGCODE);
else
    addinfo=kiks_tou([]);
end;
%kiks_status([sprintf(addinfo) 10]);
