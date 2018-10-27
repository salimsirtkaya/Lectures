function r = kGetSpeed(ref)
%KGETSPEED   Get the instantaneous speed of Khepera
%
%value = kGetSpeed(ref)
%  Return a vector of 2 values corresponding to the speed of
%  the wheels of Khepera.
%  Use the reference obtained with kopen.

reply = kcmd(ref,'E');
[value,count,errmsg] = sscanf(reply,'e,%d,%d');
if isempty(errmsg)
   r = value;
else
   r = -1;
end

