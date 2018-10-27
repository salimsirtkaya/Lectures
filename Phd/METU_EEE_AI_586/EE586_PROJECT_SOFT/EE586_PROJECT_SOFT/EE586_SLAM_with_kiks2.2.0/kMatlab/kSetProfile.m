function r = kSetProfile(ref,vL,aL,vR,aR)
%KSETPROFILE   Set the speed and acceleration profile for
%              the position controller.
%
%kSetProfile(ref,vL,aL,vR,aR)
%  Set the left and right speed and acceleration
%  of the position controller of Khepera.
%  Use the reference obtained with kopen.

if nargin < 5
   vL = 20;
   vR = 20;
   aL = 64;
   aR = 64;
   disp('Resetting to default speed (20) and acceleration (64).');
end

value = kcmd(ref,sprintf('J,%d,%d,%d,%d',round(vL),round(aL),round(vR),round(aR)));
if value == 'j'
   r = 0;
else
   r = -1;
end

