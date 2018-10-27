% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function spd=kiks_calculate_speed(t0,t1,t2,t3,max_speed,acc,start_time,end_time)
global KIKS_SPDC;

if(start_time<t0) 
    start_spd=0;
elseif(start_time<t1) 
    start_spd=(acc*3.125*start_time)/KIKS_SPDC;
elseif(start_time<t2) 
    start_spd=max_speed;
elseif(start_time<t3) 
    start_spd=((max_speed*KIKS_SPDC)-(acc*3.125*(start_time-t2)))/KIKS_SPDC;
else
    start_spd=0;
end;

if(end_time<t0) 
    end_spd=0;
elseif(end_time<t1) 
    end_spd=(acc*3.125*end_time)/KIKS_SPDC;
elseif(end_time<t2) 
    end_spd=max_speed;
elseif(end_time<t3) 
    end_spd=((max_speed*KIKS_SPDC)-(acc*3.125*(end_time-t2)))/KIKS_SPDC; 
else
    end_spd=0;
end;

spd=(start_spd+end_spd)/2;