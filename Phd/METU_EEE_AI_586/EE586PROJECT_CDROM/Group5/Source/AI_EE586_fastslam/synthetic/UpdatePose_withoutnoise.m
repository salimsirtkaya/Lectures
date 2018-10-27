function newPose = UpdatePose_withoutnoise(oldPose,input)

newPose(1) = oldPose(1) + input(1); 
newPose(2) = oldPose(2) + input(2); 
newPose(3) = mod(oldPose(3) + input(3), 2*pi); 