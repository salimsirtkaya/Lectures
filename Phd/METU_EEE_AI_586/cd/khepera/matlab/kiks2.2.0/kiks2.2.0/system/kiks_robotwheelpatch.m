% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function ptch = kiks_robotwheelpatch(id)
ptch=patch('Facecolor',[.5 .65 .6],'EdgeColor','none','Erase','xor','tag',sprintf('%dwheels',id));