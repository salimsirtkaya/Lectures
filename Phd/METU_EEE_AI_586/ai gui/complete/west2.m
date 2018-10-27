%%this program is to turn khepera to the WEST
%%the error here is too small, 1%

port=-1; % simulated Khepera
baud=9600; % use 9600 baud
ref=kiks_kopen([port,baud,1]); % open the port for communication
kiks_ksend(['B' 10],ref) % read version

%Read the Battle Turret sensors
    battle_sensors=kBattle_sensors(ref);        
    % X position of robot (in mm, from left edge).
    x_position = battle_sensors(1);             
    % Y position of robot (in mm, from top edge).
    y_position = battle_sensors(2);             
    % Angle robot is facing.
    angle = battle_sensors(3);                
    
    
while (angle<175||angle>185)  
            kiks_ksend(['D,0,10' 10],ref)
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
        end
        
     kiks_ksend(['D,0,0' 10],ref)        
kiks_kclose(ref); % close the port

