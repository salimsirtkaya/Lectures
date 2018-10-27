% -------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -------------------------------------------------
function avoid(port,baud,time)
% avoid(port,baud,time)
% port = serial port to communicate with (port<0 ==> simulated robot, port>=0 ==> real robot
% baud = baud rate
% time = time to run behaviour

if nargin<3 time=60; end;
if nargin<2 baud=9600; end;
if nargin<1 port=-1; end;

ref=kiks_kopen([port,baud,1]);
kSetEncoders(ref,0,0);
reflex = 0;
speed = [10 10];
t0=clock;
loops=0;
while (kiks_ktime(port)<time)
   loops=loops+1;
   reflex = kProximity(ref);
   lights = kAmbient(ref);
   weightsL = [10 2 4 6 6 4 2 4 4];
   weightsR = [10 -2 -4 -6 -6 -4 -2 4 4];
   speed = calcSpd(weightsL,weightsR,reflex)/2;
   kSetSpeed(ref,speed(1),speed(2));   
end;
%kGetEncoders(ref)
t=etime(clock,t0);
disp(sprintf('%.1f loops in %.1f seconds = %.1f loops/second (%.0f%%)\n',loops,t,loops/t,(time/t)*100));

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
