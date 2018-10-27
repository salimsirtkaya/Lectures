function r = kSetPWM(ref,left,right)
%KSETPWM   Set motor PWM directly
%
%kSetPWM(ref,left,right)
%  Set PWM between -255 and 255
%  Use the communication parameters specified with kcmd.

% Written by Skye Legon 2/99.

value = kcmd(ref,sprintf('P,%d,%d',round(left),round(right)));
if value == 'p'
   r = 0;
else
   r = -1;
end

