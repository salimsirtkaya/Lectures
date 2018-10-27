% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_pushobj_test(id,runtime)
global KIKS_OBJECT_SMALLBALL_RADIUS KIKS_WALL_WIDTH KIKS_SPDC KIKS_BALLDATA KIKS_BALLARRAY KIKS_OBJECT_BALL_RADIUS KIKS_ROBOT_MATRIX;

[rows,cols]=size(KIKS_BALLARRAY);

for i=1:cols,
    cylinder=KIKS_BALLDATA(KIKS_BALLARRAY(i),5);
    theRadius=KIKS_OBJECT_BALL_RADIUS;
    if cylinder theRadius=KIKS_OBJECT_SMALLBALL_RADIUS; end;
    x = [KIKS_BALLDATA(KIKS_BALLARRAY(i),1)-KIKS_ROBOT_MATRIX(id,1,1) KIKS_BALLDATA(KIKS_BALLARRAY(i),2)-KIKS_ROBOT_MATRIX(id,1,2)];
    if norm(x)<=KIKS_ROBOT_MATRIX(id,2,2)+theRadius+1
        kspd=mean([KIKS_ROBOT_MATRIX(id,1,5) KIKS_ROBOT_MATRIX(id,1,6)])*KIKS_SPDC;
        kvec=[cos(KIKS_ROBOT_MATRIX(id,1,3))*mean([KIKS_ROBOT_MATRIX(id,1,5) KIKS_ROBOT_MATRIX(id,1,6)])*KIKS_SPDC -sin(KIKS_ROBOT_MATRIX(id,1,3))*mean([KIKS_ROBOT_MATRIX(id,1,5) KIKS_ROBOT_MATRIX(id,1,6)])*KIKS_SPDC];
        kiks_calculate_ballspd(KIKS_BALLARRAY(i),kvec,kspd,x/norm(x));
    end;
end;