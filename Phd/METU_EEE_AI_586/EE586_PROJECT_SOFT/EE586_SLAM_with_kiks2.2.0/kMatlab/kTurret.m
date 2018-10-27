function r = kTurret(ref,turretID,textString)
%KTURRET   Send command (in form of text string) to turret
%
%kTurret(ref,turretID,textString)
%  
%  The response of the turret is returned as a string.
%  A higher-level routine could thus call kTurret, and then
%  parse the returned string.
%  e.g. see the included kTurretBios command
%  Use the communication parameters specified with kcmd.

% Written by Skye Legon, 02/99

reply = kcmd(ref,[sprintf('T,%d,',turretID) textString]);
[value,count,errmsg] = sscanf(reply,'t,%d,%s');
turret_response = char(value(2:length(value)))';
if isempty(errmsg)
   r = turret_response;
else
   r = -1;
end
