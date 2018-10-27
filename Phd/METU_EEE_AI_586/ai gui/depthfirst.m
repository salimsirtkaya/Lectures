
%Using ambiant light

%Qeue: W-N-E-S
%first go west,if you can't go north,if u can't go east, if u can't go
%south
% 

%-------------------------------------------------------------------

port=-1; % simulated Khepera
baud=9600; % use 9600 baud
ref=kiks_kopen([port,baud,1]); % open the port for communication



    
    
    
value = kProximity(ref) %get the values of the proximity sensors
                        %put them in a matrix value(i) where i=1,...,8
                        
battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot
    
%starting point
%at reset x=250 and y=325

x=x_position;
y=y_position;
  
  
 
 while (x>200 && y>200)
     
     
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %      first reset the robot angle     %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 value = kProximity(ref);
   while (angle<80||angle>100)  
            kiks_ksend(['D,0,10' 10],ref)
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
        end
        
     kiks_ksend(['D,0,0' 10],ref)
    
     
     
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %      then go to the west if possible     %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 

value = kProximity(ref);
if (value(1)<100)
    %here call the function go west
value = kProximity(ref);

while (angle<175||angle>185)  
            kiks_ksend(['D,0,10' 10],ref)
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
        end
        
     kiks_ksend(['D,0,0' 10],ref)       
        
while ((value(3)+value(4))<200)  %after turning left go straight until an obstacle is seen
            value = kProximity(ref);
            kiks_ksend(['D,10,10' 10],ref)
            
        end
        
%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  %      after stop, reset the robot angle     %
%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
   while (angle<80||angle>100)  
       
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
            kiks_ksend(['D,10,0' 10],ref)
            
        end
        
     kiks_ksend(['D,0,0' 10],ref)
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %              if possible go straight    %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  
value = kProximity(ref);

if (value(1)>100 && ((value(3)+value(4))/2)<100)

    while (value(1)>100 && (value(3)+value(4))<200)  %straight until an obstacle is seen
            value = kProximity(ref);
            kiks_ksend(['D,10,10' 10],ref)
            
        end
        
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %      then go to the east if possible     %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
 
 if (value(1)>100 && ((value(3)+value(4))/2)>100 && value(6)<100)
            %here call the function go east
 
            %Read the Battle Turret sensors
    battle_sensors=kBattle_sensors(ref);        
    % Angle robot is facing.
    angle = battle_sensors(3);                
    
    
while (angle>10)  
            kiks_ksend(['D,10,0' 10],ref)
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
        end
        
     kiks_ksend(['D,0,0' 10],ref)   
     
     
     

 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %              if possible go straight    %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  
value = kProximity(ref);

if (value(1)>100 &&((value(3)+value(4))/2)<200)

    while (value(1)>50 && (value(3)+value(4))<30)  %straight until an obstacle is seen
            value = kProximity(ref);
            kiks_ksend(['D,10,10' 10],ref)
            
        end
        
end

%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  %      after stop, reset the robot angle     %
%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
   while (angle<80||angle>100)  
       
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
            kiks_ksend(['D,0,10' 10],ref)
            
        end
        
     kiks_ksend(['D,0,0' 10],ref)
    
end

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %      turn back if nothing is possible     %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
 value = kProximity(ref);
 if (value(1)>100 && ((value(3)+value(4))/2)>100 && value(6)>100 && ((value(7)+value(8))/2)<100)
            %here call the function go east
 
            
 %Read the Battle Turret sensors
    battle_sensors=kBattle_sensors(ref);        
    % Angle robot is facing.
    angle = battle_sensors(3);                
    value = kProximity(ref);
    
while (angle<265||angle>275)  
            kiks_ksend(['D,0,10' 10],ref)
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
        end
        
     kiks_ksend(['D,0,0' 10],ref)        
     
     
       
     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     %      now try to go straight      %
     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      while ((value(1)>100 && ((value(3)+value(4))/2)>100 && value(6)>100 && ((value(7)+value(8))/2)<100))  %straight until an obstacle is seen
            value = kProximity(ref);
            kiks_ksend(['D,10,10' 10],ref)
            
        end
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
        end
        
        

 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 
 battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot
 
x=x_position;
y=y_position;


end%%%of the first while
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 kiks_kclose(ref); % close the port