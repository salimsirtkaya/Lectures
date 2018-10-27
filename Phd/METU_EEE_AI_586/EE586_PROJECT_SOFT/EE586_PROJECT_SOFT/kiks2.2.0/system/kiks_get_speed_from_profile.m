% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function spd=kiks_get_speed_from_profile(tnow,six)
global KIKS_SPDC
% spd = mm/sec
if tnow<six(1) spd=0.0; return; end;
if tnow<six(2) spd=six(6)*tnow*3.125; return; end;
if tnow<=six(3) spd=six(5)*KIKS_SPDC; return; end;
if tnow<six(4) spd=six(5)*KIKS_SPDC-(tnow-six(3))*six(6)*3.125; return; end;
spd=0; 
return;
