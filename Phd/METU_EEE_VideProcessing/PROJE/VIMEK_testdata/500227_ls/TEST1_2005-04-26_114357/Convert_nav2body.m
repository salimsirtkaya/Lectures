%%Salim SIRTKAYA EE706 Project
%% Convert the navigation frame velocities to
%% body frame velocities


//clear all;
close all;
load Me2.500227.Uut1.2005-04-26_114357;

endtime = length (LsSysTimeE2);
rad = pi/180;

V_body=zeros(3,endtime);

for n = 1:endtime
    R1 = [1 0 0 ; 0 cos(LsRoll(n)*rad) sin(LsRoll(n)*rad) ; 0 -sin(LsRoll(n)*rad) cos(LsRoll(n)*rad)];
    R2 = [cos(LsPitch(n)*rad) 0 -sin(LsPitch(n)*rad) ; 0 1 0 ; sin(LsPitch(n)*rad) 0 cos(LsPitch(n)*rad)];
    R3 = [cos(LsTrueHdg(n)*rad) sin(LsTrueHdg(n)*rad) 0 ; -sin(LsTrueHdg(n)*rad) cos(LsTrueHdg(n)*rad) 0 ; 0 0 1];
    
    V_body(:,n) = (R1 * (R2 * (R3 * [LsNVelocity(n); LsEVelocity(n); LsUpVelocity(n)])));
end

figure;
plot(-V_body(1,50:275));
TITLE('Vy INS - body  (m/sec)');

figure;
plot(-V_body(2,50:275));
TITLE('Vx INS - body  (m/sec)');

figure;
plot(-V_body(3,50:275));
TITLE('Vz INS - body  (m/sec)');