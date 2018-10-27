% function res = kiks_siminfo_objects
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% returns a 5*N matrix of N objects where each row contains the following:
% [object_type x_pos y_pos mm_per_seconds_speed angle_radians]
% object_type 1: light
% object_type 2: ball
% object_type 3: cylinder
function res = kiks_siminfo_objects
global KIKS_WALL_RENDER KIKS_WALL_WIDTH KIKS_LIGHTARRAY KIKS_LIGHTDATA KIKS_BALLARRAY KIKS_BALLDATA

[lrows,lcols]=size(KIKS_LIGHTDATA);
[brows,bcols]=size(KIKS_BALLDATA);
res = zeros(lrows+brows,5);

for i=1:lrows
    res(i,2)=KIKS_LIGHTDATA(i,1)-KIKS_WALL_WIDTH;
    res(i,3)=KIKS_LIGHTDATA(i,2)-KIKS_WALL_WIDTH;
end;

for i=1:brows
    res(lrows+i,1)=2+KIKS_BALLDATA(i,5);    
    res(lrows+i,2)=KIKS_BALLDATA(i,1)-KIKS_WALL_WIDTH;
    res(lrows+i,3)=KIKS_BALLDATA(i,2)-KIKS_WALL_WIDTH;
    res(lrows+i,4)=KIKS_BALLDATA(i,3); % speed (in mm/seconds)
    res(lrows+i,5)=KIKS_BALLDATA(i,4); % angle (in radians)
end;