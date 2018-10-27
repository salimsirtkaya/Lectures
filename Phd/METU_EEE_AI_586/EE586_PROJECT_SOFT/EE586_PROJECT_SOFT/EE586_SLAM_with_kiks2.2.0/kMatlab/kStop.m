function r = kStop(ref)
%KSTOP   Send stop command to Khepera
%
%kStop(ref)
%  Specify a zero speed for the left and right wheels.
%  Use the reference obtained with kopen.

% Written by Yves Piguet, 8/98.

kSetSpeed(ref,0,0);