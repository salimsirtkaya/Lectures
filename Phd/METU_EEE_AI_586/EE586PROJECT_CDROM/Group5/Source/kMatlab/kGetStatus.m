function r = kGetStatus(ref)
%KGETSTATUS   Get the status of the motion controller
%
%value = kGetStatus(ref)
%  Return a vector of 6 values corresponding to the motion controller
%  status.
%  Use the reference obtained with kopen.

reply = kcmd(ref,'K');
r = sscanf(reply,'k,%d,%d,%d,%d,%d,%d');
