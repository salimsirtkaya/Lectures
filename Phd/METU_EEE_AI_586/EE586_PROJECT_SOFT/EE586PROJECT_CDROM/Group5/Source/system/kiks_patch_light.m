% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function ptch=kiks_patch_light(id)
ptch=patch('Selected','off','Facecolor',[1 .6 .1],'Edgecolor',[0 0 0],'Erase','xor','tag',sprintf('@lightobj %d',id));