% [x,y,angle] = kiks_siminfo_robotpos(port);
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function res=kiks_siminfo_robotpos;
global KIKS_ROBOT_MATRIX KIKS_WALL_WIDTH;
if ~isempty(KIKS_ROBOT_MATRIX)
    res(1)=KIKS_ROBOT_MATRIX(1,1,1)-KIKS_WALL_WIDTH;
    res(2)=KIKS_ROBOT_MATRIX(1,1,2)-KIKS_WALL_WIDTH;
    res(3)=KIKS_ROBOT_MATRIX(1,1,3);
else
    res=[];
end;