% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function val=kiks_mod(xval,modval);
val=xval;
while val>=modval
    val=val-modval;
end;
while val<0
    val=val+modval;
end;
