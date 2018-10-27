function r = kSetPositionPID(ref,Kp,Ki,Kd)
%KSETPOSITIONPID   Configuration position PID controller
%
%kSetPositionPID(ref,Kp,Ki,Kd)
%  Set the proportional, integral, and derivative gain
%  of the position controller of Khepera.
%  Use the reference obtained with kopen.

if nargin < 4
   Kp = 3000;
   Ki = 20;
   Kd = 4000;
   disp('Set default PID controller: Kp=3000, Ki=20, Kd=4000')
end

value = kcmd(ref,sprintf('F,%d,%d,%d',round(Kp),round(Ki),round(Kd)));
if value == 'f'
   r = 0;
else
   r = -1;
end
