function r = kTurretBios(ref,turretID)
%KTURRETBIOS   return bios version of turret
%
%kTurretBios(ref,turretID)
%  
%  Use the communication parameters specified with kcmd.

% Written by Skye Legon, 02/99

reply = kTurret(ref,turretID,'B');
[value,count,errmsg] = sscanf(reply,'b,%d,%d');
if isempty(errmsg)
   disp(sprintf('Turret BIOS version %d.%d',value(1),value(2)));
   r = value;
else
   r = -1;
end
