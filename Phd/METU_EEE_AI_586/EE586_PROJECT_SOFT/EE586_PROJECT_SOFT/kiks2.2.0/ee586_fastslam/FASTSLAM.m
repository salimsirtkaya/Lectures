function FASTSLAM(port,baud,time)
close all;
if nargin<3 time=10; end;
if nargin<2 baud=9600; end;
if nargin<1 port=-1; end;


SensorData=[];
EstimateMap = [];
global no_of_particles;
no_of_particles = 100;
curr_particle_no = 1;
total_no_of_landmarks = 0;
curr_no_of_landmarks = 0;



ARENA=zeros(500,500);
ARENA(130,250)=-270; %start position
% ARENA(50,180)=4;
% ARENA(185,150)=4;
ARENA(275:285,245:255)=1;
ARENA(160:170,280:290)=1;
% ARENA(360:410,50:60)=1;

kiks(ARENA);
ref=kiks_kopen([port,baud,1]);
kSetEncoders(ref,0,0);

reflex = 0;

t0=clock;
loops=0;
i=1;
t=1;
tMax = 10;

%%%%LOAD the KINEMATIC inputs
[initialPose, poseUpdate, INPUT_kiks] = Kinematic(0);
% Initialize the particle set

for i=1:no_of_particles
    PARTICLE_SET(1).particles(i).pose(1,:) = initialPose; % x position
    PARTICLE_SET(1).particles(i).no_of_landmarks = 0;
end

% Measurement Covariance (precalculated)
R= [0.1 0;0 pi/180];

% [Measurement,Input,tMax] = LoadTestData2(0);

load INPUT.mat;
load DISTBEAR_imp.mat;
load DISTBEAR_mean.mat;

Measurement(1,:)=[0 0];
% Measurement(2:53,:) = DISTBEAR_mean;

% Input(1,:)=[0 0 0];
% Input(2:tMax,:)= INPUT;

figure;
AXIS([-150 50 -150 50]) 
hold on;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%while (kiks_ktime(port)<time)
while(t<tMax)
    %    loops=loops+1;
    %    reflex = kProximity(ref);
    %    lights = kAmbient(ref);
    %    weightsL = [10 2 4 6 6 4 2 4 4];
    %    weightsR = [10 -2 -4 -6 -6 -4 -2 4 4];
    %    speed = calcSpd(weightsL,weightsR,reflex)/4;
    
    % set counters to 0 again
    kSetEncoders(ref,0,0);    % Set the speed profile
    kSetProfile(ref,40,96,40,96);
    % Order the Khepera to move each wheel 10mm
    kMoveTo(ref,kiks_mm2p(INPUT_kiks(t,1)),kiks_mm2p(INPUT_kiks(t,2)));
    % wait for the Khepera to finish movement
    status=kGetStatus(ref);
    
%     SensorData(:,i)=kProximity(ref);
%     i=i+1;
%%% Get the sensor data
    sensor_data=[];
    while(status(1)+status(2)<2)
        status=kGetStatus(ref);
        sensor_data(:,i)=kProximity(ref);
        i=i+1;
    end;

    mean_sensor_data(:,j)=mean(sensor_data,2);
    
%%% Convert the sensor data to distance and bearing
    
    %%%%fastSlam algorithm 
    
    if (Measurement(t+1,1) > 0.2)  % if there is valuable measurement
        for m=1:no_of_particles
            %update the pose according to the motion model
            PARTICLE_SET(t+1).particles(m).pose = UpdatePose(PARTICLE_SET(t).particles(m).pose,poseUpdate(t,:));
            
            %weight=[];
            %% calculate measurement likelihood of the observed landmarks
            for n=0:PARTICLE_SET(t).particles(m).no_of_landmarks-1
                %%calculate the measurement prediction
                deltaX = (PARTICLE_SET(t).particles(m).landmark(n+1).mean(1) - PARTICLE_SET(t+1).particles(m).pose(1));
                deltaY = (PARTICLE_SET(t).particles(m).landmark(n+1).mean(2) - PARTICLE_SET(t+1).particles(m).pose(2));
                mCap(1) = sqrt(deltaX^2 + deltaY^2);
                mCap(2) = atan2(deltaY,deltaX);
                if mCap(2)<0
                    mCap(2) = mCap(2)+2*pi;
                end
                %%Calculate Jacobian
                G = [deltaX/mCap(1) deltaY/mCap(1) ; -deltaY/(mCap(1)^2) deltaX/(mCap(1)^2)];
                %%Calculate the measurement covariance 
                Q=G'*PARTICLE_SET(t).particles(m).landmark(n+1).cov*G + R;
                
                %Calculate the likelihood of correspondence
                A=Measurement(t+1,:)-mCap;
                if abs(A(2)) > pi,
                    if A(2) < 0,
                        A(2) = A(2) + 2*pi;                  
                    elseif A(2) > 0,
                        A(2) = -A(2) + 2*pi;
                    end;
                end;
                
                PARTICLE_SET(t+1).particles(m).weight(n+1)=exp(-0.5*A*inv(Q)*A')/ sqrt(det(Q));
            end;
            %set importance factor for new landmark ss 0.5 may not be true
            PARTICLE_SET(t+1).particles(m).weight(PARTICLE_SET(t).particles(m).no_of_landmarks+1) = 0.0001;
            % calculate the new number of features
            [ttemp,nCap] = max(PARTICLE_SET(t+1).particles(m).weight);
            %prev_no_of_particles = PARTICLE_SET.particles(m).no_of_landmarks;
            PARTICLE_SET(t+1).particles(m).no_of_landmarks = max(nCap,PARTICLE_SET(t).particles(m).no_of_landmarks);
            
            %%We know the new number of particles.Thus, we're ready for Kalman
            %%Filter Update 
            for n=1:PARTICLE_SET(t+1).particles(m).no_of_landmarks            
                if n==PARTICLE_SET(t).particles(m).no_of_landmarks+1  %is new feature
                    %initialize the mean of new landmark %% ss will be
                    %rearranged
                    PARTICLE_SET(t+1).particles(m).landmark(n).mean(1) = PARTICLE_SET(t+1).particles(m).pose(1) + Measurement(t+1,1) * cos(Measurement(t+1,2)+PARTICLE_SET(t+1).particles(m).pose(3));
                    PARTICLE_SET(t+1).particles(m).landmark(n).mean(2) = PARTICLE_SET(t+1).particles(m).pose(2) + Measurement(t+1,1) * sin(Measurement(t+1,2)+PARTICLE_SET(t+1).particles(m).pose(3));
                    
                    deltaX = (PARTICLE_SET(t+1).particles(m).landmark(n).mean(1) - PARTICLE_SET(t+1).particles(m).pose(1));
                    deltaY = (PARTICLE_SET(t+1).particles(m).landmark(n).mean(2) - PARTICLE_SET(t+1).particles(m).pose(2));
                    mCap(1) = sqrt(deltaX^2 + deltaY^2);
                    mCap(2) = atan2(deltaY,deltaX);
                    if mCap(2)<0
                        mCap(2) = mCap(2)+2*pi;
                    end
                    %%Calculate Jacobian
                    G = [deltaX/mCap(1) deltaY/mCap(1) ; -deltaY/(mCap(1)^2) deltaX/(mCap(1)^2)];
                    
                    PARTICLE_SET(t+1).particles(m).landmark(n).cov = inv(G)*R*inv(G)';
                    
                    %%initialize counter
                    PARTICLE_SET(t+1).particles(m).landmark(n).existence=1;
                    
                elseif n==nCap  %is observed feature
                    deltaX = (PARTICLE_SET(t).particles(m).landmark(n).mean(1) - PARTICLE_SET(t+1).particles(m).pose(1));
                    deltaY = (PARTICLE_SET(t).particles(m).landmark(n).mean(2) - PARTICLE_SET(t+1).particles(m).pose(2));
                    mCap(1) =  sqrt(deltaX^2 + deltaY^2);
                    mCap(2) = atan2(deltaY,deltaX);
                    if mCap(2)<0
                        mCap(2) = mCap(2)+2*pi;
                    end
                    %%Calculate Jacobian
                    G = [deltaX/mCap(1) deltaY/mCap(1) ; -deltaY/(mCap(1)^2) deltaX/(mCap(1)^2)];
                    
                    Q = G'*PARTICLE_SET(t).particles(m).landmark(n).cov*G + R;
                    
                    %Calculate Kalman Gain %% ss will be rearranged
                    K = PARTICLE_SET(t).particles(m).landmark(n).cov*G*inv(Q);
                    A=Measurement(t+1,:)-mCap;
                    if abs(A(2)) > pi,
                        if A(2) < 0,
                            A(2) = A(2) + 2*pi;                  
                        elseif A(2) > 0,
                            A(2) = -A(2) + 2*pi;
                        end;
                    end;
                    %Update mean
                    PARTICLE_SET(t+1).particles(m).landmark(n).mean = PARTICLE_SET(t).particles(m).landmark(n).mean +...
                        (K*A')';
                    
                    %Update Covariance
                    PARTICLE_SET(t+1).particles(m).landmark(n).cov = (eye(2) - K*G')*PARTICLE_SET(t).particles(m).landmark(n).cov;   
                    
                    PARTICLE_SET(t+1).particles(m).landmark(n).existence = PARTICLE_SET(t).particles(m).landmark(n).existence+1;
                    %%End of Kalman Filter Update
                else % all other features copy old mean and variance
                    PARTICLE_SET(t+1).particles(m).landmark(n).mean = PARTICLE_SET(t).particles(m).landmark(n).mean;
                    PARTICLE_SET(t+1).particles(m).landmark(n).cov = PARTICLE_SET(t).particles(m).landmark(n).cov;
                    PARTICLE_SET(t+1).particles(m).landmark(n).existence = PARTICLE_SET(t).particles(m).landmark(n).existence;
                    
                    %%negative filtering implementation ss
                end; % end of  if n==PARTICLE_SET(t).particles(m).no_of_landmarks+1
            end; % end of for n=1:PARTICLE_SET(t+1).particles(m).no_of_landmarks
            
            %             sum = 0;
            %             for a=1:PARTICLE_SET(t+1).particles(m).no_of_landmarks
            %                 sum = sum + PARTICLE_SET(t+1).particles(m).landmark(a).weight;
            %             end;
            %importance factor of the particle is calculated by averaging the weight
            %for each landmark.
            PARTICLE_SET(t+1).particles(m).impFact = mean(PARTICLE_SET(t+1).particles(m).weight); 
        end %end of for m=1:no_of_particles      
        %Resampling
%         auxPARTICLE_SET = PARTICLE_SET(t+1);
%         PARTICLE_SET(t+1) = ResampleParticles(auxPARTICLE_SET);      
    elseif (Measurement(t+1,1)<=0.2)
        %update the pose according to the motion model
        for m=1:no_of_particles
            PARTICLE_SET(t+1).particles(m).pose = UpdatePose(PARTICLE_SET(t).particles(m).pose,poseUpdate(t,:));
            PARTICLE_SET(t+1).particles(m).no_of_landmarks  = PARTICLE_SET(t).particles(m).no_of_landmarks ;
            for k=1:PARTICLE_SET(t).particles(m).no_of_landmarks
                PARTICLE_SET(t+1).particles(m).landmark(k) = PARTICLE_SET(t).particles(m).landmark(k);
            end
            %%negative filtering
            
        end; % end of for m=1:...
    end;% end of if (Measurement(t,1) > 0.2)  
    
    t=t+1;
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%% PLOT %%%%%%%%%%%%%%%
    
    for jj=1:no_of_particles,
        
        pp=PARTICLE_SET(t).particles(jj).pose;
        
        plot(pp(1),pp(2),'r')
    end
    
    for jj=1:no_of_particles,
        for q=1:PARTICLE_SET(t).particles(jj).no_of_landmarks,
            xm = PARTICLE_SET(t).particles(jj).landmark(q).mean;
            plot(xm(1),xm(2),'*')
        end;
    end;
    grid on
    
end

%%%%%%%%%%%%%%%%%end of while (kiks_ktime(port)<time

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