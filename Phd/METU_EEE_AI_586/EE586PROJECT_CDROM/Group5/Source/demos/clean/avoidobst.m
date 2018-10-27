% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function R = avoidobst(ref,mov_err,spd)
if mov_err>spd*0.8
   % back up
   kSetEncoders(ref,0,0);
   kMoveTo(ref,-200,-200);

   status=kGetStatus(ref);
   while(status(1)+status(2)<2)
       kiks_pause(0.1);
      status=kGetStatus(ref);
   end;
   
   % rotate
   kSetEncoders(ref,0,0);
   dir=round(rand);
   dist=(900+120*rand);
   kMoveTo(ref,((-1)^dir)*dist,-((-1)^dir)*dist);

   status=kGetStatus(ref);
   while(status(1)+status(2)<2)
       kiks_pause(0.1);
      status=kGetStatus(ref);
   end;   
end;
