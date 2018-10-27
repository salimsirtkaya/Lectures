% camera(port,baud,time)
% 'Avoid' behaviour slightly modified to also read the K213 camera.
% Place some objects in the arena and observe the camera output using the simulation monitor.
% image data is however not used in the behavior itself.
% port = serial port to communicate with (port<0 ==> simulated robot, port>=0 ==> real robot
% baud = baud rate
% time = time to run behaviour
% -------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -------------------------------------------------
function camera(port,baud,time)

if nargin<3 time=60; end;
if nargin<2 baud=19200; end;
if nargin<1 port=-1; end;

ref=kiks_kopen([port,baud,1]);
kSetEncoders(ref,0,0);
reflex = 0;
speed = [0 0];
t0=clock;
loops=0;
while (kiks_ktime(port)<time)
   loops=loops+1;
   reflex = kProximity(ref);
   cam=kLinVis(ref); % cam is an array of 64 bytes (camera pixels from left to right), where 0 is black and 255 is white.
   weightsL = [3 2 4 6 6 4 2 4 4];
   weightsR = [3 -2 -4 -6 -6 -4 -2 4 4];
   speed = calcSpd(weightsL,weightsR,reflex)/2;
   kSetSpeed(ref,speed(1),speed(2));   
end;
t=etime(clock,t0);
fprintf('%.1f loops in %.1f seconds = %.1f loops/second (%.0f%%)\n',loops,t,loops/t,(time/t)*100);

kSetSpeed(ref,0,0);
kiks_kclose(ref);

function out = calcSpd(weightsL, weightsR, reflex)

mL = weightsL(1);
mR = weightsR(1);
for i=2:9
   mL = weightsL(i)*(1/400)*reflex(i-1)+mL;
   mR = weightsR(i)*(1/400)*reflex(i-1)+mR;
end
if sum(reflex(1:4)) > sum(reflex(5:8)) 
   out = [round(mL) round(mR)];
else
   out = [round(mR) round(mL)];
end;