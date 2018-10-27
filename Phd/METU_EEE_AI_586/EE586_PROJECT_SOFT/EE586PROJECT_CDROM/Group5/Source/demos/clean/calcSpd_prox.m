% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function out = calcSpd_prox(weightsL, weightsR, reflex)
mL = weightsL(1);
mR = weightsR(1);
  for i=2:9
    mL = weightsL(i)*(1/400)*reflex(i-1)+mL;
    mR = weightsR(i)*(1/400)*reflex(i-1)+mR;
 end
out = [round(mL) round(mR)];