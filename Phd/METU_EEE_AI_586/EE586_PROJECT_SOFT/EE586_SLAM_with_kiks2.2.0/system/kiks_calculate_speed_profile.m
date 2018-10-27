% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function six=kiks_calculate_speed_profile(max_speed,acc,start_pos,end_pos)
global KIKS_SPDC;
six=[0,0,0,0,0,0];
if(end_pos-start_pos==0) return; end;

totaldist=(end_pos-start_pos)*(KIKS_SPDC/100); % total distance to travel (in mm)
spdsgn=sign(totaldist);

totaldist=abs(totaldist);
max_speed=sign(totaldist)*max_speed;
acc=sign(totaldist)*acc;
t0=0.0; % time when speed = 0
t1=(max_speed*KIKS_SPDC)/(acc*3.125); % time to reach max_speed
accdist=((max_speed*KIKS_SPDC)/2)*t1*2; % distance travelled during acceleration phases 
maxdist=totaldist-accdist; % distance to travel with max speed in mm
if(maxdist<0)
    tmax=0;
    t1=sqrt(totaldist/(acc*3.125));
    max_speed=(acc*3.125*t1)/KIKS_SPDC;
else   
    tmax=maxdist/(max_speed*KIKS_SPDC); % time to travel with max speed
end;
t2=t1+tmax; % time when speed = max_speed_right
t3=t2+t1;   % time when speed is back to 0 - total time for movement
six=[t0,t1,t2,t3,spdsgn*max_speed,spdsgn*acc];

% Need to check what happens if maxdist<0