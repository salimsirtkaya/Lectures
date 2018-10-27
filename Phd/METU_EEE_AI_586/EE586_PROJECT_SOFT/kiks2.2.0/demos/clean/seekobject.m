% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function R = seekobjects(prox_stim, nada)
weightsL = [5 -5 -4 -2 2 4 5 4 4];
weightsR = [5 5 4 2 -2 -4 -5 4 4];
R = calcSpd_prox(weightsL,weightsR,prox_stim);
