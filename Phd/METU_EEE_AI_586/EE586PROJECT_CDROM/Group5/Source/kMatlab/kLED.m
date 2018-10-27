function r = kLED(ref,n,action)
%KLED   Send led command to Khepera
%
%kLED(ref,n,action)
%  Set the led number n to OFF (action=0), ON (action=1),
%  or change its state (action=2). n and/or action can
%  be vector(s) to change more than one led.
%  Use the reference obtained with kopen.

% Written by Yves Piguet, 8/98, Skye Legon 2/99

if length(n) == 1
	n = n * ones(1,length(action(:)));
elseif length(action) == 1
	action = action * ones(1,length(n(:)));
elseif length(n(:)) ~= length(n(:))
	error('both arguments must have the same size.');
end

r = ones(size(n));
for i = 1:length(n(:))
   value = kcmd(ref,sprintf('L,%d,%d',round(n(i)),round(action(i))));
   if value == 'l'
      r(i) = round(action(i));
   else
      r(i) = -1;
   end
end
