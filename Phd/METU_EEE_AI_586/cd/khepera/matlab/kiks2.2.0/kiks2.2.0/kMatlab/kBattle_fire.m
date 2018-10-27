function value=kBattle_fire(ref);
reply=kTurret(ref,99,'F');
value=sscanf(reply(3:end),'%d,%d');