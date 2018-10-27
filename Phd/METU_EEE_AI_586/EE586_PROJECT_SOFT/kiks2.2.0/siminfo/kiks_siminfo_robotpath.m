% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% kiks_siminfo_robotpath
% Returns a matrix of size [2,x] containing the coordinates
% of the path the simulated robot has moved since kiks_kopen
% was called.
function res = kiks_siminfo_robotpath
global KIKS_trace KIKS_tracestep KIKS_WALL_RENDER

if ~isempty(KIKS_trace)
    res(1,:) = KIKS_trace(1,1:ceil(KIKS_tracestep(1)),1)-KIKS_WALL_RENDER;
    res(2,:) = KIKS_trace(1,1:ceil(KIKS_tracestep(1)),2)-KIKS_WALL_RENDER;
else
    res = [];
end;