% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function res = kiks_siminfo_speed
% returns simulator speed (relative to real time):
% [avg mom]
% where mom is the current speed (average since last call to kiks_siminfo_speed)
% and avg is the average speed since kiks_kopen was called.
global KIKS_RBT_RTIME KIKS_RBT_TIME KIKS_RBT_RTIME_MOM KIKS_RBT_TIME_MOM

id=1;

if KIKS_RBT_TIME_MOM(id)>0
    delta=KIKS_RBT_TIME(id)-KIKS_RBT_TIME_MOM(id);
    rdelta=etime(clock,KIKS_RBT_RTIME_MOM(id,:));
    avg = KIKS_RBT_TIME(id)/etime(clock,KIKS_RBT_RTIME(id,:))*100;    
    mom = delta/rdelta*100;
else
    avg=100;
    mom=avg;
end;
res=[avg mom];

KIKS_RBT_TIME_MOM(id)=KIKS_RBT_TIME(id);
KIKS_RBT_RTIME_MOM(id,:)=clock;