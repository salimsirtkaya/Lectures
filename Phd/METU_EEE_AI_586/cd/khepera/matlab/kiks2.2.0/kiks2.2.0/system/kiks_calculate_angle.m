function [rad,deg,dist]=kiks_calculate_angle(start,stop);

xdiff=stop(1)-start(1);
ydiff=stop(2)-start(2);
dist=sqrt(xdiff^2+ydiff^2);
if (dist~=0)
    ang=asin(ydiff/dist);
else
    ang=0;
end;

if (xdiff>=0 & ydiff>=0)
    rad=ang;
    deg=rad/(pi/180);
end;
if (xdiff<0)
    rad=pi-ang;
    deg=rad/(pi/180);
    return;
end;   
if (ydiff<0)
    rad=2*pi+ang;
    deg=rad/(pi/180);
    return;
end;