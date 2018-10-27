
%Greedy search
%using an old maze, a normal one
% the goal is at x=63 and y=60
%-------------------------------------------------------------------
%  kiks_kclose(ref); % close the port
port=-1; % simulated Khepera
baud=9600; % use 9600 baud
ref=kiks_kopen([port,baud,1]); % open the port for communication

value = kProximity(ref) %get the values of the proximity sensors
                        %put them in a matrix value(i) where i=1,...,8                        
battle_sensors=kBattle_sensors(ref); %read the battle sensors
angle = battle_sensors(3); %angle of the robot
 
%%%here are the coordinates of the goal

xg=50;
yg=50;


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
 
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
 %%read all the sensors
 
 value = kProximity(ref) %get the values of the proximity sensors
                        %put them in a matrix value(i) where i=1,...,8                        
battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot
    
%starting coordinates of the robot
x=x_position;
y=y_position;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%     now we'll find the line joining the start and the goal
%%%     then we'll find the angle between the vertical and this 
%%%     line, then the robot will turn this angle and navigate
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p=y-yg;
q=x-xg;
u=p/q;
v=atan(u);
alpha=rad2deg(v);   %this is the angle




while (sqrt((x_position-xg).^2+(y_position-yg).^2)>160)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%     now let the robot turn this angle
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 value = kProximity(ref);
 beta=180-alpha;
   while (angle<(beta-5)||angle>(beta+5))  
            kiks_ksend(['D,0,10' 10],ref)
            battle_sensors=kBattle_sensors(ref); 
            angle = battle_sensors(3); 

        
     kiks_ksend(['D,0,0' 10],ref)
     
 end
 
 
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%     now go straight until u see an obstacle
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



while ((value(3)+value(4))<25)  %straight until an obstacle is seen
            value = kProximity(ref);
            kiks_ksend(['D,10,10' 10],ref)
            
        end
        
     kiks_ksend(['D,0,0' 10],ref)
        
        
        
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        
 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%     when u see an obstacle, turn in order to make this obstacle
%%%     seen by sensor#6, then go straight... when the obstacle is 
%%%     farther,turn to the right and go a small distance in order 
%%%     for the senxor#6 to still seeing the obstacle 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



while ((value(6))<90)  %an obstacle is seen, turn so sensor#6 sees it
            value = kProximity(ref);
            kiks_ksend(['D,-10,10' 10],ref)
            
        end
        
%%%read position sensors
battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot

p1=y_position-yg;
q1=x_position-xg;
u1=p1/q1;
v1=atan(u1);
alpha1=rad2deg(v1);   %this is the angle, if=alpha stop





while (alpha1>alpha)   %alpha1: yeni noktada goal'a olan aci, alpha: starttan bla bla bla...
 %repeat the following
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 


        
   while ((value(6))<60)  %an obstacle is seen, turn so sensor#6 sees it
            value = kProximity(ref);
            kiks_ksend(['D,10,-10' 10],ref)
            
        end
 
        
        
%%%now if the right is closed, go straight if there is no obstacle ahead

while ((value(6))>60 && (value(3)+value(4))<100)  %an obstacle is seen, turn so sensor#6 sees it
            value = kProximity(ref);
            kiks_ksend(['D,10,10' 10],ref)
            
        end
  
        
 %%%now if the right and the front are closed, go to the left

while ((value(6))>60 && (value(3)+value(4))>100 && (value(1))<60)  %an obstacle is seen, turn so sensor#6 sees it
            value = kProximity(ref);
            kiks_ksend(['D,-10,10' 10],ref)
            
        end
  
     
   %%%now if all the directions are closed, goback

while ((value(6))>60 && (value(3)+value(4))>100 && (value(1))>60)  %an obstacle is seen, turn so sensor#6 sees it
            value = kProximity(ref);
            kiks_ksend(['D,-10,-10' 10],ref)
            
        end
        
 
        
        %%%read position sensors
battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot

p1=y_position-yg;
q1=x_position-xg;
u1=p1/q1;
v1=atan(u1);
alpha1=rad2deg(v1);   %this is the angle, if=alpha stop
value = kProximity(ref);



        
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
    end%of the while to avoide obstacle
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
    
value = kProximity(ref);
battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot
    

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


     kiks_ksend(['D,0,0' 10],ref)
     
            
 %%%        till here we turn after seeing the obstacle
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
        
    
 


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%     after finishing the obstacle, reset the angle then 
%%%     turn the angle toward the goal and go straight
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



end%%%of the big while

 kiks_kclose(ref); % close the port