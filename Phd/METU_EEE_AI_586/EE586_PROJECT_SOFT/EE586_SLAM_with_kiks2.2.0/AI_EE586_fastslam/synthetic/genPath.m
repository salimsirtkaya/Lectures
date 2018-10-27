
function genPath()

pose(1,:) = [0 0 pi/2];

[Measurement,poseUpdate,tMax] = LoadTestData2(0);

for t=2:30
    pose(t,:) = UpdatePose_withoutnoise(pose(t-1,:),poseUpdate(t-1,:));
end

save realpose.mat pose;
figure;

plot(pose(:,1),pose(:,2),'b');
AXIS([-10 40 -10 80]);
grid;
hold;
plot(pose(:,1),pose(:,2),'kX','lineWidth',2);
plot(5,15,'rO','lineWidth',2);
plot(-8,58,'rO','lineWidth',2);
plot(23,58,'rO','lineWidth',2);

