clear;
close all;
time=1/8;
baud=9600;
port=-1;
rot=41.65;

ARENA=zeros(700,500);
ARENA(130,250)=-270; %start position
% ARENA(50,180)=4;
% ARENA(170,85)=4;
% ARENA(295:305,245:255)=1;
% ARENA(235:245,185:195)=1;
ARENA(255:265,200:210)=1;

kiks(ARENA);

%kiks('alan.kad');

ref=kiks_kopen([port,baud,1]);

INPUT=[];
MEASUREMENT_mean=[];
MEASUREMENT_imp=[];
% time=1;
% speed = [5 5];
% i=1;
%
% for n=1:100
%
% value(:,i)=kProximity(ref);
% while (kiks_ktime(port)<time)
%    kSetSpeed(ref,speed(1),speed(2));
%    end;
% i=i+1;
%
% end

for j=1:30

    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(10),kiks_mm2p(10));
    INPUT(j,:)=[0 -10 0];
    % wait for the Khepera to finish movement
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

    mean_sensor_data(:,j)=mean(sensor_data,2);
    sense=kProximity(ref);
    MEASUREMENT_imp(j,:)=sense';
    % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(j)=kiks_p2mm(pulses(1));
    rightmm_position_mode(j)=kiks_p2mm(pulses(2));
    % -----------------------------------------------------------------------------------------

end


for kk=1:10
    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(rot/10),kiks_mm2p(-rot/10));
    INPUT(kk+30,:)=[0 0 351*pi/180];
    % wait for the Khepera to finish movement
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

    mean_sensor_data(:,kk+30)=mean(sensor_data,2);
    sense=kProximity(ref);
    MEASUREMENT_imp(kk+30,:)=sense';
% 
%     % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(kk+30)=kiks_p2mm(pulses(1));
    rightmm_position_mode(kk+30)=kiks_p2mm(pulses(2));
%     % -----------------------------------------------------------------------------------------

end;



    
  for j=41:52

    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(10),kiks_mm2p(10));
    % wait for the Khepera to finish movement
     INPUT(j,:)=[-10 0 0];
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

    mean_sensor_data(:,j)=mean(sensor_data,2);
    sense=kProximity(ref);
    MEASUREMENT_imp(j,:)=sense';

    % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(j)=kiks_p2mm(pulses(1));
    rightmm_position_mode(j)=kiks_p2mm(pulses(2));
    % -----------------------------------------------------------------------------------------

  end  
    
  
  
   % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(rot),kiks_mm2p(-rot));
    INPUT(53,:)=[0 0 270*pi/180];
    % wait for the Khepera to finish movement
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

    mean_sensor_data(:,53)=mean(sensor_data,2);
    sense=kProximity(ref);
    MEASUREMENT_imp(53,:)=sense';
% 
%     % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(53)=kiks_p2mm(pulses(1));
    rightmm_position_mode(53)=kiks_p2mm(pulses(2));
%     %
%     -----------------------------------------------------------------------------------------
  
  for j=54:84

    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(10),kiks_mm2p(10));
    % wait for the Khepera to finish movement
     INPUT(j,:)=[0 10 0];
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

    mean_sensor_data(:,j)=mean(sensor_data,2);
    sense=kProximity(ref);
    MEASUREMENT_imp(j,:)=sense';

    % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(j)=kiks_p2mm(pulses(1));
    rightmm_position_mode(j)=kiks_p2mm(pulses(2));
    % -----------------------------------------------------------------------------------------

  end  
  
  
  
    
    
save INPUT INPUT;

MEASUREMENT_mean = mean_sensor_data';
save MEASUREMENT_mean MEASUREMENT_mean;

save MEASUREMENT_imp MEASUREMENT_imp;


[m,n]=size(rightmm_position_mode);
position(1:2,1)=0;
position(3,1)=3*pi/2;

for j=2:n
    % position(3,j)=(leftmm_position_mode(1,j-1)-rightmm_position_mode(1,j-1))/55; %teta
    % mid_d=(leftmm_position_mode(1,j-1)-rightmm_position_mode(1,j-1))/2;
    % position(1,j)=position(1,j-1)+(abs(mid_d)*sin(position(3,j)))/(position(3,j)+0.0001);
    % position(2,j)=position(1,j-1)+(abs(mid_d)*(1-cos(position(3,j))))/(position(3,j)+0.0001);
    %

    if leftmm_position_mode(1,j-1)==rightmm_position_mode(1,j-1)

        position(1,j)=position(1,j-1)+cos(position(3,j-1))*leftmm_position_mode(1,j-1);
        position(2,j)=position(2,j-1)+sin(position(3,j-1))*rightmm_position_mode(1,j-1);
        position(3,j)=position(3,j-1);

    elseif leftmm_position_mode(1,j-1)>rightmm_position_mode(1,j-1)

        position(1,j)=position(1,j-1);
        position(2,j)=position(2,j-1);
        position(3,j)=position(3,j-1)-pi/2;

    elseif leftmm_position_mode(1,j-1)<rightmm_position_mode(1,j-1)
        position(1,j)=position(1,j-1);
        position(2,j)=position(2,j-1);
        position(3,j)=position(3,j-1)+pi/2;

    end
end

kiks_kclose(ref);