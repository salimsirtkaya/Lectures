% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function ptch = kiks_robotdiodpatch(id,col)
ptch=patch('Facecolor',col,'EdgeColor','none','Erase','xor','tag',sprintf('%ddiod',id));