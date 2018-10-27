function r = kGetEncoders(ref)
%KGETENCODERS   Get the encoder values of Khepera
%
%value = kGetEncoders(ref)
%  Return a vector of 2 values corresponding to the position of
%  the wheels of Khepera.
%  Use the reference obtained with kopen.

retries = 3;
retry = 1;
errmsg = 'none yet';
while errmsg & (retry <= retries)
   reply = kcmd(ref,'H');
   [r,count,errmsg] = sscanf(reply,'h,%d,%d');
   if errmsg
      disp('Error reading encoders.  Retrying...')
      retry = retry + 1;
   end
end
if errmsg
	disp('Encoders failed.')
	r = -1;
end

