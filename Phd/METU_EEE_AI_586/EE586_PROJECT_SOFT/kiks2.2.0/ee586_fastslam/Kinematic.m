%% Initial pose of khepera
function [initialPose, poseUpdate, INPUT_kiks] = Kinematic(a)
initialPose = [0 0 -3*pi/2];

currPose = initialPose;

index_1=10;
poseUpdate = [];

%% Generate an input sequence for the wheel commands i mm
%% first entry for left wheel im mm, second entry for right wheel

%% Bulunduðun yönde 10 defa 10'ar mm ile hareket et
for i=1:index_1
    INPUT_kiks(i,:) = [10 10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = INPUT_kiks(i,1)*cos(currPose(3));
    poseUpdate(i,2) = INPUT_kiks(i,2)*sin(currPose(3));
    poseUpdate(i,3) = (INPUT_kiks(i,1) - INPUT_kiks(i,2) ) * 3*pi/2/2/41.65;
    currPose = currPose + poseUpdate(i,:);
end

