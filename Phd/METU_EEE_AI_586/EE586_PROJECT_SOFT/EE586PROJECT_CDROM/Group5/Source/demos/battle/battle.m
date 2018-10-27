% battle(port,baud,time)
% Demonstrates how to use the K-Team Radio Turret and the KiKS Battle Turret.
%
% port = serial port to communicate with (port<0 ==> simulated robot, port>=0 ==> real robot
% baud = baud rate
% time = time to run behaviour
% -------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -------------------------------------------------
function battle(port,baud,time)

if nargin<3 time=Inf; end;
if nargin<2 baud=9600; end;
if nargin<1 port=-1; end;

ref=kiks_kopen([port,baud,1]);
if isempty(ref)
    error('Could not open communication with robot!');
    return;
end;
kSetEncoders(ref,0,0);
reflex = 0;
speed = [0 0];
while (kiks_ktime(port)<time)   
    % If you are running the KiKSnet server on the same machine as KiKS,
    % you might want to keep Matlab from eating all CPU power by pausing a
    % short time in the beginning of each loop.
    pause(0.01); 
    % Just your normal avoid behavior
    reflex = kProximity(ref);
    weightsL = [5  2  3  4  4  3  2 0 0];
    weightsR = [5 -2 -3 -4 -4 -3 -2 0 0];
    speed = calcSpd(weightsL,weightsR,reflex)/2;
    kSetSpeed(ref,speed(1),speed(2));
    % End of avoid stuff
    
    % Check status of the radio turret
    ready_to_send=0; message_recieved=0; send_failed=0;
    radio_status=kRadio_status(ref);
    if ~isempty(radio_status)
        ready_to_send = radio_status(1);
        message_recieved = radio_status(2);
        send_failed = radio_status(3);
    end;
    % If we have a new message in the reception buffer, read and display
    % it.
    if (message_recieved)
        msg = kRadio_read(ref);
        sender = msg(1);
        msglength = msg(2);
        message = char(msg(3:3+msglength));
        kiks_print(sprintf('Message recieved from %d: %s',sender,message));
    end;
    
    % Read the Battle Turret sensors
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
    if no_of_hits>0
        kiks_print('I''m hit! I''m hit!');
    end;
    
    kiks_print(sprintf('X:%d | Y:%d | Angle:%d | Distance:%d | Energy:%d%%',x_position,y_position,angle,distance,energy_level_percent));
    
    % Each shot with the cannon costs us 5 energy points.
    % If we hit a robot, our victim will lose 10 energy points.
    % Energy re-charges at a rate of 1 point per second.
    % If we do not currently have at least 5 energy points, we
    % won't be able to fire.
    % Max energy level is equal to the radius of the robot, so 
    % large robots have better firepower than small robots but 
    % are on the other hand easier to hit.
    % There is no reload time.
    
    % Use the K213 linear vision camera to determine if there is
    % anything in front of us worth shooting at.
    target_in_sight = 0;
    picture = kLinVis(ref);
    min_pixel_value = min(picture(8:56)); % simplistic examination of picture
    if min_pixel_value<150 
        % There's something in front of us.
        % Lets shoot first and ask questions later.
        target_in_sight = 1;
        kiks_print('Target aquired!');
    end;
    
    % The fire command only works if we are connected to a KiKSnet server.
    % If energy is reported to be -1, we are offline, and there's no need
    % to even bother shooting. The cannon is entirely handled by the
    % server for fairness.
    if target_in_sight & energy_level_units>-1 
        % Try to fire the cannon
        target=kBattle_fire(ref);
        % Radio turret ID of robot we hit, or -1 if we just made another burn mark in the wall.
        target_id = target(1);                      
        % Distance to whatever we hit, or -1 if we couldn't fire (in which case the energy level is below 5 units).
        target_distance = target(2);                
        if target_distance==-1
            kiks_print(sprintf('Energy level too low to fire (%d units, %d%% of maximum capacity)',energy_level_units,energy_level_percent));
        else
            kiks_print('Cannon fired...');        
            if target_id~=-1
                kiks_print(sprintf(' Ha! I shot robot #%d.\n',target_id));
                % Lets use the radio to apologize.
                if (ready_to_send)
                    msg = 'Terribly sorry!';
                    kRadio_send(ref,target_id,msg,length(msg));
                end;
            else
                kiks_print(' Doh! Another burn mark in the wall.\n');
            end;    
        end;
    end;
end;

kSetSpeed(ref,0,0);
kiks_kclose(ref);


function out = calcSpd(weightsL, weightsR, reflex)
mL = weightsL(1);
mR = weightsR(1);
for i=2:9
   mL = weightsL(i)*(1/400)*reflex(i-1)+mL;
   mR = weightsR(i)*(1/400)*reflex(i-1)+mR;
end
if sum(reflex(1:4)) > sum(reflex(5:8)) 
   out = [round(mL) round(mR)];
else
   out = [round(mR) round(mL)];
end;