
%%%find x, y positions and the angle

port=-1; % simulated Khepera
baud=9600; % use 9600 baud
ref=kiks_kopen([port,baud,1]); % open the port for communication


    ref=kiks_kopen([port,baud,1]);
    %Read the Battle Turret sensors
    battle_sensors=kBattle_sensors(ref);        
    % X position of robot (in mm, from left edge).
    x_position = battle_sensors(1);             
    % Y position of robot (in mm, from top edge).
    y_position = battle_sensors(2);            
    % Angle robot is facing.
    angle = battle_sensors(3);                  
    % Distance to whatever the turret is aiming at (in mm, from front of robot).
    distance = battle_sensors(4);               
    % Turret energy level in percent. -1 if not connected to a KiKSnet server.
    energy_level_percent = battle_sensors(5);   
    % Turret energy level in units. -1 if not connected to a KiKSnet server.
    energy_level_units = battle_sensors(6);     
    % Number of times we has been shot by other robots. This number is reset each time we read it. -1 if not connected to a KiKSnet server.
    no_of_hits = battle_sensors(7);             
    
    kiks_kclose(ref); % close the port