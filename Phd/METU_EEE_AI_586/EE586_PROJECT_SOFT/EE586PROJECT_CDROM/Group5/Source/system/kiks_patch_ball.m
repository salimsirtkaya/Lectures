% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function ptch=kiks_patch_ball(id)
global KIKS_COLOR_BACKGROUND KIKS_COLOR_BALL;
%col=([KIKS_COLOR_BALL KIKS_COLOR_BALL KIKS_COLOR_BALL]/255)+KIKS_COLOR_BACKGROUND;
col=[0.1 0.8 0.5];
ptch=patch('Selected','off','Facecolor',col,'Edgecolor',[0 0 0],'Erase','xor','tag',sprintf('@ballobj %d',id));