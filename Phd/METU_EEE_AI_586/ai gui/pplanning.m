function varargout = pplanning(varargin)
% PPLANNING M-file for pplanning.fig
%      PPLANNING, by itself, creates a new PPLANNING or raises the existing
%      singleton*.
%
%      H = PPLANNING returns the handle to a new PPLANNING or the handle to
%      the existing singleton*.
%
%      PPLANNING('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PPLANNING.M with the given input arguments.
%
%      PPLANNING('Property','Value',...) creates a new PPLANNING or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before pplanning_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to pplanning_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help pplanning

% Last Modified by GUIDE v2.5 08-Jun-2006 11:31:16

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @pplanning_OpeningFcn, ...
                   'gui_OutputFcn',  @pplanning_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin & isstr(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before pplanning is made visible.
function pplanning_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to pplanning (see VARARGIN)

% Choose default command line output for pplanning
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

h=imread('khepera.bmp');
imshow(h)
% UIWAIT makes pplanning wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = pplanning_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in intro.
function intro_Callback(hObject, eventdata, handles)
% hObject    handle to intro (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
!introduction.pps

% --- Executes on button press in khepera.
function khepera_Callback(hObject, eventdata, handles)
% hObject    handle to khepera (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
!Khepera.pps

% --- Executes on button press in depthfirst.
function depthfirst_Callback(hObject, eventdata, handles)
% hObject    handle to depthfirst (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


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

xg=50;
yg=50;
  
dept=sqrt((x-xg).^2+(x-yg).^2)
 
 while (dept >100)
     
     
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
     
dept=sqrt((x-xg).^2+(x-yg).^2)     
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
 battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot
 
x=x_position;
y=y_position;



d=sqrt((x-xg).^2+(x-yg).^2)

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
  
         battle_sensors=kBattle_sensors(ref); %read the battle sensors
x_position = battle_sensors(1);  % X position of robot (in mm, from left edge).           
y_position = battle_sensors(2);  % Y position of robot (in mm, from top edge).    
angle = battle_sensors(3); %angle of the robot
 
x=x_position;
y=y_position;



d=sqrt((x-xg).^2+(x-yg).^2)
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



d=sqrt((x-xg).^2+(x-yg).^2)


end%%%of the first while
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 kiks_kclose(ref); % close the port
 
 

% --- Executes on button press in greedy.
function greedy_Callback(hObject, eventdata, handles)
% hObject    handle to greedy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

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



% --- Executes on button press in obstacle.
function obstacle_Callback(hObject, eventdata, handles)
% hObject    handle to obstacle (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

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

% --- Executes on button press in cspace.
function cspace_Callback(hObject, eventdata, handles)
% hObject    handle to cspace (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
figure,imshow(I),title('the original map, coordinate space')
se = strel('square',15);
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a square robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
se = strel('disk',15);
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a circular robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
se = [0 0 0 1 0 0 0
      0 0 1 1 1 0 0
      0 1 1 1 1 1 0
      1 1 1 1 1 1 1]
  
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a triangular robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze1.bmp');
I=rgb2gray(a);
I=double(I);
se = [0 0 0 1 0 0 0
      0 0 1 1 1 0 0
      0 1 1 1 1 1 0
      1 1 1 1 1 1 1
      1 1 1 1 1 1 1
      0 1 1 1 1 1 0
      0 0 1 1 1 0 0
      0 0 0 1 0 0 0]
  
b = imdilate(I,se);
[x,y]=size(b);
figure,imshow(b),title('C-space of a rhombus robot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --- Executes on button press in voronoy.
function voronoy_Callback(hObject, eventdata, handles)
% hObject    handle to voronoy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


%%%%%%%erode the maze%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a=imread('maze.bmp');
%a=imread('maze2.bmp');
I=rgb2gray(a);
%I=double(I);
figure,imshow(I)
se = strel('square',40);
b = imerode(I,se);
[x,y]=size(b);
figure,imshow(b)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%now find the white%%%%% 
%%%%%%%regions' centers%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%here we took a block of 10 pixels... we test if there is a white squares
%inside this block... if there exist take any pixel to be the center


k=1;

for i=1:x       %here we r testing blocks of 10x10 pixels
    for j=1:y
     
        if (b(i,j)==255)&(b(i,j-1)==0)&(b(i-1,j)==0)
            m(1,k)=i+1;
            m(2,k)=j+2;
            k=k+1;
        end
     
    

    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       after getting the centers
%       we will draw Voronoi diagram
%       using m and n vectors
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
r=1:k-1
xx=m(1,r)
yy=m(2,r)
hold on
voronoi(yy,xx)

% --- Executes on button press in map.
function map_Callback(hObject, eventdata, handles)
% hObject    handle to map (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
kiks

% --- Executes on button press in closes.
function closes_Callback(hObject, eventdata, handles)
% hObject    handle to closes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
kiks_quit

