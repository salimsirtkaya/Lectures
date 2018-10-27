% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function res=kiks_spawn_robot(pos,rotation,alignment,newkhepid)
global KIKS_COLOR_ROBOT KIKS_FID KIKS_MMPERPIXEL KIKS_SIM_LINVIS_2DMODE KIKS_SIM_LINVIS_IMG KIKS_SIM_LINVIS_LU KIKS_SIM_LINVIS_RP KIKS_RBTARRAY KIKS_ROBOT_MATRIX KIKS_ROBOT_DATA KIKS_RBT_HDL KIKS_2DVISUALIZE KIKS_dynstp KIKS_PORT KIKS_lastwascoll KIKS_RBTLIST KIKS_GUI_HDL KIKS_WALL_WIDTH KIKS_ARENA_MX KIKS_ARENA_MASK KIKS_RBTMASK KIKS_MONITOR_ON KIKS_TIMESCALE;

res=1;
if (nargin<4) newkhepid=1; end;
[rows,cols]=size(KIKS_RBTARRAY);
if ~isempty(KIKS_RBTARRAY)
    return;
end;

ok=1;
while(ok==1)
    ok=0;
    for i=1:cols,
        if(KIKS_RBTARRAY(i)==newkhepid)
            ok=1;
        end
    end
    if (ok==1) newkhepid=newkhepid+1; end;
end;

h=findobj(KIKS_GUI_HDL,'tag','t_kiksnet_place_robot');
set(h,'Visible','off');
if(KIKS_FID>=0)
    h=findobj(KIKS_GUI_HDL,'tag','simulate_popup');
    set(h,'Enable','off'); 
end;

KIKS_RBTARRAY(cols+1) = newkhepid;
KIKS_ROBOT_MATRIX(newkhepid,:,:) = KIKS_ROBOT_DATA;

if(nargin<2 | isempty(rotation)) % random rotation
    KIKS_ROBOT_MATRIX(newkhepid,1,3)=pi*2*rand;
else
    KIKS_ROBOT_MATRIX(newkhepid,1,3)=rotation;
end


[ys,xs]=size(KIKS_ARENA_MASK);
ys=ys*KIKS_MMPERPIXEL;
xs=xs*KIKS_MMPERPIXEL;
if(nargin<1 | isempty(pos)) % place robot at random position
    KIKS_ROBOT_MATRIX(newkhepid,1,1)=(xs/2);
    KIKS_ROBOT_MATRIX(newkhepid,1,2)=(ys/2);
    kiks_calculate_gripper(newkhepid);
else
    KIKS_ROBOT_MATRIX(newkhepid,1,1)=pos(1);
    KIKS_ROBOT_MATRIX(newkhepid,1,2)=pos(2);
    kiks_calculate_gripper(newkhepid);
end;

tries=0;
while(kiks_detect_collision(newkhepid)>1 & tries<100)
    tries=tries+1;
    xp = rand*(xs-KIKS_WALL_WIDTH*2);
    yp = rand*(ys-KIKS_WALL_WIDTH*2);
    KIKS_ROBOT_MATRIX(newkhepid,1,1)=xp;
    KIKS_ROBOT_MATRIX(newkhepid,1,2)=yp;
    
    kiks_calculate_gripper(newkhepid);
    res=0;
end
if tries>=100
    kiks_status('Warning: Robot spawned in wall.');
    KIKS_ROBOT_MATRIX(newkhepid,1,1)=(xs/2);
    KIKS_ROBOT_MATRIX(newkhepid,1,2)=(ys/2);
end;


KIKS_dynstp(newkhepid)=1;
KIKS_lastwascoll(newkhepid)=0;
KIKS_PORT(newkhepid)=0;
KIKS_SIM_LINVIS_RP(newkhepid)=0.2;
KIKS_SIM_LINVIS_LU(newkhepid)=-10;
if KIKS_SIM_LINVIS_2DMODE
    KIKS_SIM_LINVIS_IMG(newkhepid,KIKS_SIM_LINVIS_2DMODE,KIKS_SIM_LINVIS_2DMODE)=0;
else
    KIKS_SIM_LINVIS_IMG(newkhepid,:)=zeros(1,64);
end;

%KIKS_MONITOR_ON(newkhepid)=0;
try
   test=KIKS_MONITOR_ON(newkhepid);
catch
    KIKS_MONITOR_ON(newkhepid)=0;
end;

if (KIKS_2DVISUALIZE>0)
    %   h=findobj('Name','KiKS arena');
    %   figure(h);
    figure(KIKS_GUI_HDL);
    kiks_gui_robotvis(newkhepid);
    kiks_draw_robot(newkhepid);
end;

try
    h=findobj(KIKS_GUI_HDL,'Tag','kheppopup');
    emp=get(h,'Enable');
catch
    emp='off';
end;

if isempty(emp) emp='off'; end;

if(emp(2) ~= 'f') % oFf...
    [rows,cols]=size(KIKS_RBTLIST);
    KIKS_RBTLIST(cols+1)={sprintf('Port %d',-newkhepid)};
else
    KIKS_RBTLIST={};
    KIKS_RBTLIST(1)={sprintf('Port %d',-newkhepid)};
end;

newxp = floor(KIKS_ROBOT_MATRIX(newkhepid,1,1));
newyp = floor(KIKS_ROBOT_MATRIX(newkhepid,1,2));
%kiks_arena_addrobot(newkhepid,newxp,newyp);
kiks_arena_add_mask(newxp,newyp,KIKS_COLOR_ROBOT,KIKS_ROBOT_MATRIX(newkhepid,2,2));

try
    h=findobj(KIKS_GUI_HDL,'Tag','kheppopup');
    set(h,'String',KIKS_RBTLIST);
    set(h,'Value',cols+1);
    if (emp(2) == 'f') % oFf...
        set(h,'Enable','on');
        h=findobj(KIKS_GUI_HDL,'Tag','deletekhep');
        set(h,'Enable','on');
        h=findobj(KIKS_GUI_HDL,'Tag','monkhep');
        set(h,'Enable','on');      
    end;
end;   
kiks_checkpoint;