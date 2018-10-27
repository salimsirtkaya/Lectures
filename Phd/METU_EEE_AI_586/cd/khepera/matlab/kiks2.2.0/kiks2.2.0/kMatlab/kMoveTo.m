function r = kMoveTo(ref,left,right)
%KMOVETO   Send target position command to Khepera
%
%kMoveTo(ref,left,right)
%  Specify the target position for the left wheel and right
%  wheel in pulses (1 pulse = 1/12 mm).
%  Use the reference obtained with kopen.

% Written by Yves Piguet, 8/98.

value = kcmd(ref,sprintf('C,%d,%d',round(left),round(right)));
if value == 'c'
   r = 0;
else
   r = -1;
end
