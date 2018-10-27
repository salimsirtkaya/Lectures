% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function ptch = kiks_robotpatch(id)
global KIKS_COLOR_BACKGROUND
col=[.05 .20 0];
ptch=patch('Facecolor',col,'Edgecolor',[0 0 0],'Erase','xor','tag',sprintf('@handle %d',id));