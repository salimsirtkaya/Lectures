function r = kGetAnalog(ref,channel)
% KGETANALOG   Read the analog inputs

if nargin ~= 2
   disp('Usage:')
   disp('value = kGetAnalog(ref,channel)')
   disp('Returns a vector of values corresponding to a vector of channels.')
   disp('Returns -1 if the channel is not found.')
   disp('Use the reference obtained with kopen.')
   disp('Skye Legon, K-Team SA, 02/99')
   return
end

r = ones(size(channel));
for i = 1:length(channel)
   reply = kcmd(ref,sprintf('I,%d',round(channel(i))));
   [value,count,errmsg] = sscanf(reply,'i,%d');
   if isempty(errmsg)
      r(i) = value;
   else
      r(i) = -1;
   end
end
