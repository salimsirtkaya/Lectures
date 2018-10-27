function r = kSetEncoders(ref, left, right)
%KSETENCODERS   Set the encoder values of Khepera
%
%value = kSetEncoders(ref, left, right)
%  Set the encoders to particular values.
%  if no values are specified, they are reset to zero.
%  Use the reference obtained with kopen.

if nargin < 3
   left = 0;
   right = 0;
end

value = kcmd(ref,sprintf('G,%d,%d',round(left),round(right)));
if value == 'g'
   r = 0;
else
   r = -1;
end
