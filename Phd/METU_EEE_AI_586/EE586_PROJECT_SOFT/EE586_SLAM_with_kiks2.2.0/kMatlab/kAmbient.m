function r = kAmbient(ref)
%KAMBIENT   Get the value of the ambient light sensors of Khepera
%
%value = kAmbient(ref)
%  Return a vector of 8 values corresponding to the 8
%  ambient light sensors of Khepera.
%  Use the reference obtained with kopen.

% Written by Yves Piguet, 8/98.

reply = kcmd(ref,'O');
[value,count,errmsg] = sscanf(reply,'o,%d,%d,%d,%d,%d,%d,%d,%d');
if isempty(errmsg)
   r = value;
else
   r = -1;
end
