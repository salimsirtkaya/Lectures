function kStatus(ref)
%KSTATUS   Display the status of the motion controller
%
%value = kStatus(ref)
%  Displays the 6 values corresponding to the motion controller
%  status.
%  Use the reference obtained with kopen.

values = kGetStatus(ref);

string = 'Left:   ';
for i=1:2,
   string = [string '(status = '];
   if values((i-1)*3+1) == 1,
      string = [string 'AT TARGET) '];
   else
      string = [string 'MOVING)    '];
   end
   string = [string '(control = '];
   if values((i-1)*3+2) == 1,
      string = [string 'SPEED)    '];
   else
      string = [string 'POSITION) '];
   end
   string = [string sprintf('(Error = %d)', values((i-1)*3+3))];
   disp(string);
   string = 'Right:  ';
end
