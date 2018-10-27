% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_simulaterobot
global KIKS_PROXIMITY_DIRECTIONS KIKS_PROXIMITY_POSITIONS KIKS_ROBOT_DISTANCE_BETWEEN_WHEELS KIKS_ROBOT_DIAMETER KIKS_PROXIMITY_SENSORS_RANGE KIKS_RBTARRAY KIKS_SIM_PROX_DIST KIKS_1250 KIKS_MMPERPIXEL KIKS_SIM_PROX_STEP KIKS_GUI_HDL;

dontspawn=0;
if isempty(KIKS_RBTARRAY)
    dontspawn=1;
end;

while size(KIKS_RBTARRAY>0)
    kiks_delete_robot(KIKS_RBTARRAY(1));
end;

h=findobj(KIKS_GUI_HDL,'Tag','simulate_popup');
nr=get(h,'Value');
robots = get(h,'String');
robot = char(strrep(robots(nr),' ','_'));

eval(robot);

KIKS_SIM_PROX_DIST = KIKS_PROXIMITY_SENSORS_RANGE;

KIKS_1250=[KIKS_MMPERPIXEL:ceil(KIKS_SIM_PROX_STEP/KIKS_MMPERPIXEL):floor(KIKS_SIM_PROX_DIST/KIKS_MMPERPIXEL)];
[tmp,sz]=size(KIKS_1250);
KIKS_1250=KIKS_1250(2:sz); % don't include (0,0)

kiks_set_robot_data;

if dontspawn==0
    kiks_spawn_robot;
end;