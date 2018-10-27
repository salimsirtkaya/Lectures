function r = kProximity(ref)
%KPROXIMITY   Get the value of the proximity sensors of Khepera
%
%value = kProximity(ref)
%  Return a vector of 8 values corresponding to the 8
%  proximity sensors of Khepera.
%  Use the reference obtained with kopen.

% Written by Skye Legon, 2/99

retries = 3;
retry = 1;
errmsg = 'none yet';
while errmsg & (retry <= retries)
   reply = kcmd(ref,'N');
   [r,count,errmsg] = sscanf(reply,'n,%d,%d,%d,%d,%d,%d,%d,%d');
   if errmsg
      disp('Error reading sensors.  Retrying...')
      retry = retry + 1;
   end
end
if errmsg
	disp('Sensors failed.')
	r = -1;
end
