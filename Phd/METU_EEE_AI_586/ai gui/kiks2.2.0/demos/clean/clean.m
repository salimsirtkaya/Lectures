% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function clean(port,baud,time)
% clean(port,baud,time)
% port = serial port to communicate with (port<0 ==> simulated robot, port>=0 ==> real robot
% baud = baud rate
% time = time to run behaviour

if(nargin<3) time=60; end;
if(nargin<2) baud=9600; end;
if(nargin<1) port=-1; end;

if port<0
    kiks_arena(zeros(500,500));
    for i=1:12, kiks_spawn(3); end;
end;

ref=kiks_kopen([port,baud,1]);
loops=0;
t0=clock;
while(kiks_ktime(port)<time)
%   res=kLinVis(ref);
   loops=loops+1;
   prox_stim = kProximity(ref);
   respons = seekobject(prox_stim,'');
   respons = pushobject(prox_stim,respons);
   mov_err = kGetStatus(ref);
   avoidobst(ref,[mov_err(3) mov_err(6)],respons);
   if ~isempty(respons) kSetSpeed(ref,respons(1),respons(2)); end;
   kiks_pause(0.05);
end;
kSetSpeed(ref,0,0);
fprintf('%1.0f seconds simulated in %1.0f seconds (%3.0f%% of real time)\n',kiks_ktime(port),etime(clock,t0),(kiks_ktime(port)/etime(clock,t0))*100)
fprintf('%1.1f loops / second\n',loops/kiks_ktime(port))
kiks_kclose(ref);

