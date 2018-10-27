function r = kWriteByte(ref,data,address)
%KWRITEBYTE   Write a byte to the extension bus
%
%kWriteByte(ref,data,address)
%  Write a data byte to an address (0..63) on the extension bus
%  Use the communication parameters specified with kcmd.

% Written by Skye Legon 2/99

value = kcmd(ref,sprintf('W,%d,%d',round(data),round(address)));
if value == 'w'
   r = 0;
else
   r = -1;
end

