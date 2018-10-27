function [Measurement,Input,tMax]=LoadTestData1(arg)

tMax=12;
%%%%% TEST CASE %%%%%%%%%%%%%
for i=1:6
    Input(i,:) = [0 5 0];
end
Input(1,:)=[0 0 0];

for i=7:11
    Input(i,:)=[0 8 0];
end

Measurement(1,:) = [0 0];
Measurement(2,:) = [0 0];
Measurement(3,:) = [0 0];
Measurement(4,:) = [5*sqrt(2)+0.2*randn pi/4+randn*pi/180];
Measurement(5,:) = [5+0.2*randn abs(randn)*pi/180];
Measurement(6,:) = [5*sqrt(2)+0.2*randn 7*pi/4+randn*pi/180];
Measurement(7,:) = [0 0];
Measurement(8,:) = [0 0];
Measurement(9,:) = [0 0];
Measurement(10,:) = [8*sqrt(2)+0.2*randn 3*pi/4+randn*pi/180];
Measurement(11,:) = [8+0.2*randn pi+randn*pi/180];
Measurement(12,:) = [8*sqrt(2)+0.2*randn 5*pi/4+randn*pi/180];

%%
