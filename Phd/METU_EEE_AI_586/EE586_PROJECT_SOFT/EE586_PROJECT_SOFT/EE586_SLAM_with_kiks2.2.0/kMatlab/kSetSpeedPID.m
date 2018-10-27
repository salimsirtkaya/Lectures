function r = kSetSpeedPID(ref,Kp,Ki,Kd)
%KSETSPEEDPID   Set PID speed controller
%
%kSetSpeedPID(ref,Kp,Ki,Kd)
%  Set the proportional, integral, and derivative gain
%  of the speed controller of Khepera.
%  Use the reference obtained with kopen.

% Written by Yves Piguet, 8/98.

if nargin < 4
   Kp = 3800;
   Ki = 800;
   Kd = 100;
   disp('Set default PID controller: Kp=3800, Ki=800, Kd=100')
end

value = kcmd(ref,sprintf('A,%d,%d,%d',round(Kp),round(Ki),round(Kd)));
if value == 'a'
   r = 0;
else
   r = -1;
end

