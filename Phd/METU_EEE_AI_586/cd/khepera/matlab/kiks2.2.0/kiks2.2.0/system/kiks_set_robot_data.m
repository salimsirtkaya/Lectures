% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_set_robot_data
global KIKS_PROXIMITY_DIRECTIONS KIKS_PROXIMITY_POSITIONS KIKS_PROX_DIR KIKS_PROX_ANG KIKS_GRIPPER_ACTIVE KIKS_LIGHT_POS KIKS_PROX_POS KIKS_SPDC KIKS_ROBOT_DATA KIKS_RBTMASK_COL KIKS_COLOR_ROBOT KIKS_RBT_DIOD KIKS_RBT_LAMP KIKS_RBT_BODY KIKS_RBTMASK KIKS_WALL_WIDTH KIKS_MMPERPIXEL KIKS_RBT_BODY KIKS_GRIPPER_ACTIVE KIKS_ROBOT_DATA KIKS_ROBOT_DISTANCE_BETWEEN_WHEELS KIKS_ROBOT_DIAMETER KIKS_SPDC KIKS_PROX_POS KIKS_LIGHT_POS;

KIKS_ROBOT_RADIUS=floor(KIKS_ROBOT_DIAMETER/2);
% internal representation of the simulated robot
kx=1+KIKS_ROBOT_RADIUS+KIKS_WALL_WIDTH; % coordinate=1+radius+wall
ky=1+KIKS_ROBOT_RADIUS+KIKS_WALL_WIDTH;
ang=0;

KIKS_PROX_DIR = (pi/180)*KIKS_PROXIMITY_DIRECTIONS;
KIKS_PROX_ANG = -(pi/180)*KIKS_PROXIMITY_POSITIONS;

KIKS_ROBOT_DATA = [ kx   ky   ang  0    0    0    0    0    ; % xpos ypos rotation_angle move_mode(0=speed,1=position) left_wheel_speed right_wheel_speed left_wheel_counter right_wheel_counter
    KIKS_ROBOT_DISTANCE_BETWEEN_WHEELS   KIKS_ROBOT_RADIUS   0    0    0    0    0    0    ; % diameter_between_wheels robot_radius lT lM lE rT rM rE
    0    0    0    0    0    0    0    0    ; % registers for internal use (general speed variables)
    0    0    0    0    0    0    0    0    ; % baud rate variables
    20   64   20   64   0    0    0   -1    ; % max_speed_left, acc_left, max_speed_right, acc_right, left_wheel_target, right_wheel_target, movement_accumulated_time
    0    0    0    0    0    0    0    0    ; % position mode profiles: lt0 lt1 lt2 lt3 left_maxspeed left_acc server_left_speed server_right_speed
    0    0    0    0    0    0    -1  -1    ; % position mode profiles: rt0 rt1 rt2 rt3 right_maxspeed right_acc                     
    0    0    0    0    0    0    0    0    ; % registers for internal use (general speed variables)
    0    0    0    0    0    0    0    0    ; % proximity sensor data
    0    0    0    0    0    0    0    0    ; % light sensor data
    127  200  0    0    0    0    0    0    ; % gripper data: arm_position gripper_position resistivity object_present arm_target gripper_target
    0    0    0    0    0    0    0    0   ]; % radio data: buffer_empty==1 message_in_reception_buffer==1 message_send_failed==1

KIKS_SPDC=8.2;                  
KIKS_PROX_POS = 9; KIKS_LIGHT_POS = 10; % in case more registers are added, just change these to correct row number.

stp=pi/32;
if isempty(KIKS_GRIPPER_ACTIVE)
%    KIKS_RBT_BODY(1,:)=(((KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL)+1)*(cos([KIKS_ROBOT_DATA(1,3):stp:2*pi+KIKS_ROBOT_DATA(1,3)-stp])));
%    KIKS_RBT_BODY(2,:)=-(((KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL)+1)*(sin([KIKS_ROBOT_DATA(1,3):stp:KIKS_ROBOT_DATA(1,3)+2*pi-stp])));
    KIKS_RBT_BODY(1,:)=(cos([KIKS_ROBOT_DATA(1,3):stp:2*pi+KIKS_ROBOT_DATA(1,3)-stp]));
    KIKS_RBT_BODY(2,:)=-(sin([KIKS_ROBOT_DATA(1,3):stp:KIKS_ROBOT_DATA(1,3)+2*pi-stp]));
else
    KIKS_RBT_BODY(1,:)=(((KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL))*(cos([pi+pi/2+KIKS_ROBOT_DATA(1,3):stp:2*pi+pi/2+KIKS_ROBOT_DATA(1,3)])));
    KIKS_RBT_BODY(2,:)=-(((KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL))*(sin([pi+pi/2+KIKS_ROBOT_DATA(1,3):stp:2*pi+pi/2+KIKS_ROBOT_DATA(1,3)])));
    [tmp,pts]=size(KIKS_RBT_BODY);
    KIKS_RBT_BODY(1,pts+1)=-KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL;
    KIKS_RBT_BODY(2,pts+1)=-KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL;
    KIKS_RBT_BODY(1,pts+2)=-KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL;
    KIKS_RBT_BODY(2,pts+2)=KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL;
end;

KIKS_RBT_LAMP(1,:)=(5/KIKS_MMPERPIXEL)*(cos(pi/4:pi/4:2*pi));
KIKS_RBT_LAMP(2,:)=(5/KIKS_MMPERPIXEL)*(sin(pi/4:pi/4:2*pi));

KIKS_RBT_DIOD(1,:)=(2/KIKS_MMPERPIXEL)*(cos(pi/4:pi/4:2*pi));
KIKS_RBT_DIOD(2,:)=(2/KIKS_MMPERPIXEL)*(sin(pi/4:pi/4:2*pi));


MX = floor(KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL)*2+1;
MY = floor(KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL)*2+1;
KIKS_RBTMASK = zeros(MY, MX);
KIKS_RBTMASK_COL = zeros(MY, MX);
for x=1:MX,
    for y=1:MY,
        if sqrt((x-(MX+1)/2)*(x-(MX+1)/2)+(y-(MY+1)/2)*(y-(MY+1)/2))<=KIKS_ROBOT_DATA(2,2)/KIKS_MMPERPIXEL 
            KIKS_RBTMASK(x,y)=1; 
            if KIKS_COLOR_ROBOT>0
                KIKS_RBTMASK_COL(x,y)=KIKS_COLOR_ROBOT;
            else
                % black/white stripes
                qs=abs(KIKS_COLOR_ROBOT)/4; % stripes in each quadrant
                ang=pi/(8*qs);
                col=1;
                xp=abs(x-(MX+1)/2);
                yp=abs(y-(MY+1)/2);
                hyp=sqrt((xp*xp)+(yp*yp));
                for i=1:qs % test each stripe
                    xp_hi=cos(ang)*hyp;
                    xp_low=cos(ang+pi/(4*qs))*hyp;
                    if (xp>=xp_low & xp<=xp_hi) | hyp<=2
                        col=255;
                    end;
                    ang=ang+(pi/(2*qs));
                end;
                KIKS_RBTMASK_COL(x,y)=col;             
            end;         
        end;
    end;   
end;
