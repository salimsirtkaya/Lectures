function [bios,prot] = kversion(ref)
%KVERSION   Read software version from Khepera
%
%kversion(ref)
%  Display the versions of the BIOS and of the protocol.
%  Use the reference obtained with kopen.
%[vers_bios,vers_protocol] = kversion(ref)
%  Return the versions as strings.

% Written by Yves Piguet, 9/98.

reply = kcmd(ref,'B');
i = findstr(reply, ',');
bios_string = reply(i(1)+1:i(2)-1);
prot_string = reply(i(2)+1:end);
values = sscanf(reply,'b,%f,%f');
bios = values(1);
prot = values(2);

if nargout <= 1		% display nicely the versions
	fprintf('Khepera BIOS version: %s\n', bios_string);
	fprintf('Khepera protocol version: %s\n', prot_string);
end
