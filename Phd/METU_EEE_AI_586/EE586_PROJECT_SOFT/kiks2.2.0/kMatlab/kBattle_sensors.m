function value=kBattle_sensors(ref);
reply=kTurret(ref,99,'S');
value=sscanf(reply(3:end),'%d,%d,%d,%d,%d,%d,%d');