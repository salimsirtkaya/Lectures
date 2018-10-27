%% Initial pose of khepera
function [initialPose, poseUpdate, INPUT_kiks] = Kinematic(a)

rot=41.65;

initialPose = [0 0 3*pi/2];

currPose = initialPose;

index_1 = 10;
index_2 = index_1 + 10;
index_3 = index_2 + 10;
index_4 = index_3 + 10;
index_5 = index_4 + 10;
index_6 = index_5 + 10;
index_7 = index_6 + 19;
index_8 = index_7 + 10;
index_9 = index_8 + 20;
index_10 = index_9 + 10;
index_11 = index_10 + 50;


poseUpdate = [];

%% Generate an input sequence for the wheel commands i mm
%% first entry for left wheel im mm, second entry for right wheel

%% Bulunduðun yönde 10 defa 10'ar mm ile hareket et
for i=1:index_1
    INPUT_kiks(i,:) = [10 10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,1) - INPUT_kiks(i,2) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% 9 derecelik 10 dönüþ yap
for i=index_1+1:index_2
    INPUT_kiks(i,:) = [rot/10 -rot/10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% bulunduðun yönde 10 defa 10'ar mm ile hareket et
for i=index_2+1:index_3
    INPUT_kiks(i,:) = [10 10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% 9 derecelik 10 dönüþ yap
for i=index_3+1:index_4
    INPUT_kiks(i,:) = [rot/10 -rot/10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% bulunduðun yönde 10 defa 10'ar mm ile hareket et
for i=index_4+1:index_5
    INPUT_kiks(i,:) = [10 10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% 9 derecelik 10 dönüþ yap
for i=index_5+1:index_6
    INPUT_kiks(i,:) = [rot/10 -rot/10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% bulunduðun yönde 10 defa 10'ar mm ile hareket et
for i=index_6+1:index_7
    INPUT_kiks(i,:) = [10 10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% 9 derecelik 10 dönüþ yap
for i=index_7+1:index_8
    INPUT_kiks(i,:) = [rot/10 -rot/10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% bulunduðun yönde 10 defa 10'ar mm ile hareket et
for i=index_8+1:index_9
    INPUT_kiks(i,:) = [10 10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% 9 derecelik 10 dönüþ yap
for i=index_9+1:index_10
    INPUT_kiks(i,:) = [rot/10 -rot/10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

%% bulunduðun yönde 10 defa 10'ar mm ile hareket et
for i=index_10+1:index_11
    INPUT_kiks(i,:) = [10 10];
    % calculate the pose update (input to kinematic model)
    poseUpdate(i,1) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*cos(currPose(3))/2;
    poseUpdate(i,2) = (INPUT_kiks(i,1)+INPUT_kiks(i,2))*sin(currPose(3))/2;
    poseUpdate(i,3) = (INPUT_kiks(i,2) - INPUT_kiks(i,1) ) * pi/2/2/rot;
    currPose = currPose + poseUpdate(i,:);
end

