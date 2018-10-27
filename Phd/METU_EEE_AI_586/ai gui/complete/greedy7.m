
%Greedy search
%using an old maze, a normal one
% the goal is at x=63 and y=60
%-------------------------------------------------------------------

port=-1; % simulated Khepera
baud=9600; % use 9600 baud
ref=kiks_kopen([port,baud,1]); % open the port for communication

%the heuristic is the distance between the new position (3 different
%positions) to the goal.. the Euclidean distance
    
xg=100;
yg=100;

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
   
    
 
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %      first reset the robot angle     %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 value = kProximity(ref);
   while (angle<80||angle>100)  
            kiks_ksend(['D,-10,10' 10],ref)
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 
        end
        
     kiks_ksend(['D,0,0' 10],ref)
    
     
e=x;
f=y-10;
 
d1=sqrt((e-xg).^2+(f-yg).^2);  %the distance from a square ahead to the goal
        
    
    
     
     
e=x-10;
f=y-10;
 
d2=sqrt((e-xg).^2+(f-yg).^2);   % the distance from a square at the left of the robot to the goal
    
   
    
 
    
    
e=x+10;
f=y-10;

d3=sqrt((e-xg).^2+(f-yg).^2);   % the distance from a square at the left of the robot to the goal
  
     
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

n=10;
while(d1>100&&d2>100&&d3>100) 
    
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %      then check the sensors of three directions     
 %      if no obstacle ahead find d1, if no obstacle 
 %      at the right find d2, if no obstacle st the left
 %      find d3, compare the three distances and make a move
 %      toward the minimum distance... what are d1,d2 and d3???
 %      they are the distances from the new position (if the move is made)
 %      to the goal... a heuristic.  move +10 at each move
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
 
 
 
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
   





 %%%start point is at x=1625 and y=611
 %%%goal point is at x=31 and y=30
 value = kProximity(ref);
 d1=10000;
 d2=10000;
 d3=10000;
 
 if (((value(3)+value(4))/2)<100) %if thtere is no obstacle aheasd 

 e=x;
 f=y-10;
 
    d1=sqrt((e-xg).^2+(f-yg).^2);  %the distance from a square ahead to the goal
        
end
 


value = kProximity(ref);

if (value(1)<100)

e=x-10;
f=y-10;
 
    d2=sqrt((e-xg).^2+(f-yg).^2);   % the distance from a square at the left of the robot to the goal
    
        end
        
        
     
value = kProximity(ref);

if (value(6)<100)

e=x+10;
f=y-10;

    d3=sqrt((e-xg).^2+(f-yg).^2);   % the distance from a square at the left of the robot to the goal
    
        end
        
  
        
        
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%      for avoiding obstacles
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



 value = kProximity(ref);

if (value(5)>200 && ((value(3)+value(4))/2)>200 && (value(2)>200))

%if there is no place to go, go backward
for i=1:1:20
            kiks_ksend(['D,-10,-10' 10],ref)
        end
        
        end
     
        
        
        
        
  value = kProximity(ref);

if (value(5)>200)

%if there is an obstacle atthe right, avoid it by going left back
for i=1:1:10
            kiks_ksend(['D,-10,0' 10],ref)
        end
        
        end
        
        
    
        
        value = kProximity(ref);

if (value(2)>200)

%if there is an obstacle at the left, avoid it by going right back
for i=1:1:10
            kiks_ksend(['D,0,-10' 10],ref)
        end
        
        end
        
        
        
 
        
        value = kProximity(ref);

if (((value(7)+value(8))/2)>200)

%if there is an obstacle behind u, go ahead
for i=1:1:20
            kiks_ksend(['D,10,10' 10],ref)
        end
        
        end
        
        
        
        
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %            Now compare the three distances and choose the
 %            direction that make u closer to the goal
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       
        
        
      
 if (d1<d2 && d1<d3)
                         %here go straight
      for i=1:1:10
            kiks_ksend(['D,10,10' 10],ref)
        end        
     
    end    
        
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
    
    
if (d2<d3)  
    
  for i=1:1:30
kiks_ksend(['D,0,10' 10],ref) % set left motor speed to 10 pulses and right
            %motor speed to 0 pulses
        end
           
    
        
 for i=1:1:10
            kiks_ksend(['D,10,10' 10],ref)
        end   
        
 
        %reset angle
        for i=1:1:10
kiks_ksend(['D,10,0' 10],ref) 
        end
        
        end
        
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        

if (d3<d2)      
      
    for i=1:1:30
kiks_ksend(['D,10,0' 10],ref) % set left motor speed to 10 pulses and right
            %motor speed to 0 pulses
        end
 
 
        
 for i=1:1:10
            kiks_ksend(['D,10,10' 10],ref)
        end   
        
        
        %reset angle
        for i=1:1:10
kiks_ksend(['D,0,10' 10],ref) 
        end
        
        
 end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

n=n+1;
end


     kiks_ksend(['D,0,0' 10],ref)

 kiks_kclose(ref); % close the port
