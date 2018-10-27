% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function spd=kiks_calculate_speed_from_profile(t0,t1,t2,t3,max_speed,acc,time)
global KIKS_SPDC

if(time<t0) spd=0; return; end;
if(time<t1) spd=(acc*3.125*time)/KIKS_SPDC; return; end;
if(time<t2) spd=max_speed; return; end;
if(time<t3) spd=((max_speed*KIKS_SPDC)-(acc*3.125*(time-t2)))/KIKS_SPDC; return; end;
spd=0; return;