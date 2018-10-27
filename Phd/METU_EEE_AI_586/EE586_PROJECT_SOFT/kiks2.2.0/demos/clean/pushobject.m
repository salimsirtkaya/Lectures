% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function R = pushobject(prox_stim, respons)
if (prox_stim(3)+prox_stim(4)>1300)
	weightsL = [10 -2 -1 1 1 1 2 0 0];
   weightsR = [10 2 1 1 1 -1 -2 0 0];
   R = calcSpd_prox(weightsL,weightsR,prox_stim);
else
   R = respons;
end;

