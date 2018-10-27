function r = kSetSpeed(ref,left,right)
%KSETSPEED   send a speed command to Khepera
%
%kSetSpeed(ref,left,right)
%  
%  Use the communication parameters specified with kcmd.

% Written by Yves Piguet, 08/98

value = kcmd(ref,sprintf('D,%d,%d',round(left),round(right)));
if value == 'd'
   r = 0;
else
   r = -1;
end

