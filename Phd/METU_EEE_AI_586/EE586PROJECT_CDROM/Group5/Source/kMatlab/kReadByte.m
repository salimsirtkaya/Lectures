function r = kReadByte(ref,address)
%KREADBYTE   Read a byte from the extension bus
%
%value = kReadByte(ref)
%  Read a byte from an address (0..63) on the extension bus
%  Use the reference obtained with kopen.

reply = kcmd(ref,sprintf('R,%d',round(address)));
[value,count,errmsg] = sscanf(reply,'r,%d');
if isempty(errmsg)
   r = value;
else
   r = -1;
end

