clear;
time=1/8;
baud=9600;
port=-1;
rot=41.65;

ARENA=zeros(300,300);
ARENA(150,150)=-270; %start position
% ARENA(120:140,50:70)=1;
% ARENA(120:140,50:60)=1;
% ARENA(190:220,50:60)=1;
% ARENA(270:310,50:60)=1;
% ARENA(360:410,50:60)=1;

kiks(ARENA);

%kiks('alan.kad');

ref=kiks_kopen([port,baud,1]);

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

for j=1:10

    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(10),kiks_mm2p(10));
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
    % wait for the Khepera to finish movement
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

    mean_sensor_data(:,11)=mean(sensor_data,2);
% 
%     % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(11)=kiks_p2mm(pulses(1));
    rightmm_position_mode(11)=kiks_p2mm(pulses(2));
%     % -----------------------------------------------------------------------------------------

    


    
  for j=12:21

    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(10),kiks_mm2p(10));
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
    % wait for the Khepera to finish movement
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

       mean_sensor_data(:,22)=mean(sensor_data,2);

    % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(22)=kiks_p2mm(pulses(1));
    rightmm_position_mode(22)=kiks_p2mm(pulses(2));
    % -----------------------------------------------------------------------------------------

    



    
  for j=23:32

    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(10),kiks_mm2p(10));
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
    % wait for the Khepera to finish movement
    status=kGetStatus(ref);

    i=1;
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

       mean_sensor_data(:,33)=mean(sensor_data,2);

    % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(33)=kiks_p2mm(pulses(1));
    rightmm_position_mode(33)=kiks_p2mm(pulses(2));
    % -----------------------------------------------------------------------------------------

    



    
  for j=34:43

    % -----------------------------------------------------------------------------------------
    % This time, we will simply tell the Khepera to move each wheel 80mm.
    % set counters to 0 again
    kSetEncoders(ref,0,0);
    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(10),kiks_mm2p(10));
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

    % how far have we moved?
    pulses=kGetEncoders(ref);
    leftmm_position_mode(j)=kiks_p2mm(pulses(1));
    rightmm_position_mode(j)=kiks_p2mm(pulses(2));
    % -----------------------------------------------------------------------------------------

end  
    
     
    
    
    


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

% [m,n]=size(mean_sensor_data);
% 
% for j=n:
%     
%    r4=(50-mean_sensor_data(4,j)*50/1023)
%    r5=(50-mean_sensor_data(5,j)*50/1023)
%    r6=(50-mean_sensor_data(6,j)*50/1023)
%    
% 
% 
%     if mean_sensor_data(5,j)>20
% 
%         if mean_sensor_data(6,j)<20
% 
%         else
% 
%         end
% 
%     else
%         
%          if mean_sensor_data(6,j)<20
% 
%         else
% 
%         end
        
        
%         
%    
%  location=scxsc()
%             
% 
%         end
% 
% 
%     end



    %    scxsc(0,0,1,1,0,1)
    %
    % ans =
    %
    %     0.4999    0.4999   -0.8661    0.8661



