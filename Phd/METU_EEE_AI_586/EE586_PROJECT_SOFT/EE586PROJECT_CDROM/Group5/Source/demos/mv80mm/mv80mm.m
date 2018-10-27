% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% Two different ways to make the Khepera move a specific distance.
function mv80mm
time=2;
baud=9600;
port=-1;

ref=kiks_kopen([port,baud,1]);

% ------------------------------------------------------------------------------------------
% First, let's try moving 80mm by setting left and right speed and waiting for 2 seconds.
% set the position counters to 0
kSetEncoders(ref,0,0);
% set speed to 40 mm/sec
kSetSpeed(ref,kiks_mm2p(40)/100,kiks_mm2p(40)/100);
% kiks_ktime returns no. of seconds since kiks_kopen was called
while(kiks_ktime(ref)<time)
    % just waiting for 2 seconds to pass...
end;
kSetSpeed(ref,0,0);
% how far have we moved?
pulses=kGetEncoders(ref);
leftmm_speed_mode=kiks_p2mm(pulses(1))
rightmm_speed_mode=kiks_p2mm(pulses(2))
% -----------------------------------------------------------------------------------------

% -----------------------------------------------------------------------------------------
% This time, we will simply tell the Khepera to move each wheel 80mm.
% set counters to 0 again
kSetEncoders(ref,0,0);
% Set the speed profile
kSetProfile(ref,40,96,40,96);
% Order the Khepera to move each wheel 80mm
kMoveTo(ref,kiks_mm2p(80),kiks_mm2p(80));
% wait for the Khepera to finish movement
status=kGetStatus(ref);
while(status(1)+status(2)<2)
   status=kGetStatus(ref);
end;
% how far have we moved?
pulses=kGetEncoders(ref);
leftmm_position_mode=kiks_p2mm(pulses(1))
rightmm_position_mode=kiks_p2mm(pulses(2))
% -----------------------------------------------------------------------------------------

kiks_kclose(ref);