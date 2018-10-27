% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function follow(port,baud,time)
% follow(port,baud,time)
% port = serial port to communicate with (port<0 ==> simulated robot, port>=0 ==> real robot
% baud = baud rate
% time = time to run behaviour

if(nargin<3) time=30; end;
if(nargin<2) baud=9600; end;
if(nargin<1) port=-1; end;

ref=kiks_kopen([port,baud,1]); % KiKS starts up automatically when kiks_kopen is called
reflex = 0;
speed = [1 1];
loops=0; % for calculating loops/second, not needed for the simulation
t0=clock; % for calculating loops/second, not needed for the simulation
kSetEncoders(ref,0,0);
while (kiks_ktime(port)<time)
%   kiks_pause(0.2); % just to show how much a simulation can be accelerated.
   loops=loops+1; % for calculating loops/second, not needed for the simulation
   reflex = kProximity(ref);
   weightsL = [5 0 2 3 3 0 0 0 0];
   weightsR = [7 0 0 -3 -3 0 0 0 0];
   speed = calcspd(weightsL,weightsR,reflex);
   kSetSpeed(ref,speed(1),speed(2));   
end;
kSetSpeed(ref,0,0);
% calculate stats
fprintf('%1.0f seconds simulated in %1.0f seconds (%3.0f%% of real time)\n',kiks_ktime(port),etime(clock,t0),(kiks_ktime(port)/etime(clock,t0))*100)
fprintf('%1.1f loops / second\n',loops/kiks_ktime(port))
% close port
kiks_kclose(ref);


function out = calcspd(weightsL, weightsR, reflex)
mL = weightsL(1);
mR = weightsR(1);
  for i=2:9
    mL = weightsL(i)*(1/1023)*reflex(i-1)+mL;
    mR = weightsR(i)*(1/1023)*reflex(i-1)+mR;
 end
out = [round(mL) round(mR)];
