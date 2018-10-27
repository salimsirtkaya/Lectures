% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res=kiks_net_request(id)
global KIKS_SPDC KIKS_NET_BUFSIZ KIKS_FID KIKS_ROBOT_MATRIX KIKS_MMPERPIXEL;

res='';
if KIKS_FID>-1 
    req=sprintf('R 1 %.3f %.3f %.3f %.3f %.3f %.3f %.3f',KIKS_ROBOT_MATRIX(id,1,1),KIKS_ROBOT_MATRIX(id,1,2),KIKS_ROBOT_MATRIX(id,1,3),KIKS_ROBOT_MATRIX(id,6,7)*KIKS_SPDC,KIKS_ROBOT_MATRIX(id,6,8)*KIKS_SPDC,KIKS_ROBOT_MATRIX(id,2,2),KIKS_ROBOT_MATRIX(id,2,1));
    kiks_transmit_string(KIKS_FID,req); 
    res=kiks_recieve_string(KIKS_FID);
end;
