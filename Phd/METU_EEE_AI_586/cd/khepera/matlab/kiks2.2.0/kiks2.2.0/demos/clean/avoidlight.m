% -------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -------------------------------------------------
function R = avoidlight(amb_stim, respons)
if(amb_stim(1)+amb_stim(2)+amb_stim(3)+amb_stim(4)+amb_stim(5)+amb_stim(6)<500)
	weightsL = [5 1 2 4 4 2 1 1 1];
   weightsR = [5 -1 -2 -4 -4 -2 -1 1 1];
   R = calcSpd_prox(weightsL,weightsR,amb_stim);
else
   R = respons;
end;
