% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% collision detection

function ret=kiks_detect_collision(id,nonetwork)
global KIKS_REMOTE_ARRAY_NEW KIKS_FID KIKS_ARENA_MASK KIKS_ROBOT_MATRIX KIKS_RBTMASK KIKS_REMOTE_OBJECTS_ARRAY_NEW KIKS_NET_BUFSIZ KIKS_MMPERPIXEL KIKS_WALL_WIDTH KIKS_GRIPPER_ACTIVE % KIKS_GRIPPER_XCOORD KIKS_GRIPPER_YCOORD KIKS_GRIPPER_GRP_XCOORD KIKS_GRIPPER_GRP_YCOORD KIKS_GRIPPER_ARM_X KIKS_GRIPPER_ARM_Y KIKS_GRIPPER_LGRP_X KIKS_GRIPPER_LGRP_Y KIKS_GRIPPER_RGRP_X KIKS_GRIPPER_RGRP_Y;

if ~isempty(KIKS_GRIPPER_ACTIVE)
    kiks_calculate_gripper(id);
end;

if nargin<2
    nonetwork=[];
end;
ret=1;
if KIKS_FID==-1
    [ys,xs]=size(KIKS_ARENA_MASK);
    if (~isempty(KIKS_GRIPPER_ACTIVE))
        grpxp=floor([KIKS_GRIPPER_ARM_X KIKS_GRIPPER_LGRP_X KIKS_GRIPPER_RGRP_X]);
        grpyp=floor([KIKS_GRIPPER_ARM_Y KIKS_GRIPPER_LGRP_Y KIKS_GRIPPER_RGRP_Y]);
        grppos=(grpxp-1)*ys+grpyp;
        grpcoll=find(KIKS_ARENA_MASK(grppos));
        if(~isempty(grpcoll))
            ret=2; % TODO: indicate gripper collision so no rotation is performed
            return;
        end;
    end;
    minx = floor(KIKS_ROBOT_MATRIX(id,1,1)/KIKS_MMPERPIXEL)-floor(KIKS_ROBOT_MATRIX(id,2,2)/KIKS_MMPERPIXEL); % xpos - robot radius
    miny = floor(KIKS_ROBOT_MATRIX(id,1,2)/KIKS_MMPERPIXEL)-floor(KIKS_ROBOT_MATRIX(id,2,2)/KIKS_MMPERPIXEL); % ypos - robot radius
    maxx = floor(KIKS_ROBOT_MATRIX(id,1,1)/KIKS_MMPERPIXEL)+floor(KIKS_ROBOT_MATRIX(id,2,2)/KIKS_MMPERPIXEL);
    maxy = floor(KIKS_ROBOT_MATRIX(id,1,2)/KIKS_MMPERPIXEL)+floor(KIKS_ROBOT_MATRIX(id,2,2)/KIKS_MMPERPIXEL);
    
    KIKS_WALL_WIDTH_SCALED=KIKS_WALL_WIDTH/KIKS_MMPERPIXEL;
    
    if(minx<(KIKS_WALL_WIDTH_SCALED) | maxx>xs-(KIKS_WALL_WIDTH_SCALED) | miny<(KIKS_WALL_WIDTH_SCALED) | maxy>ys-(KIKS_WALL_WIDTH_SCALED)) 
        ret=99;
        return;
    end;
    
    map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_RBTMASK;
    ret = max(max(map));
    
    %ret = any(KIKS_ARENA_COLORMASK(miny:maxy, minx:maxx) & KIKS_RBTMASK_COL)+1;
else % let server handle collision detection
    sret = kiks_server_request(id);
    if ~isempty(sret)
        if sret(1)=='N' % server could not give us a position
            ret=[100];
            return;
        end;
        if sret(1)=='O'
            ret=[1; sscanf(sret,'OK %f %f')];
            KIKS_REMOTE_ARRAY_NEW=sscanf(sret(4:end),'%f'); % we've fetched the updated object array.
            KIKS_REMOTE_ARRAY_NEW=KIKS_REMOTE_ARRAY_NEW(3:end);
            kiks_update_remote;
            res=kiks_recieve_string(KIKS_FID);
            KIKS_REMOTE_OBJECTS_ARRAY_NEW=sscanf(res(6:end),'%f');
            kiks_update_remote_objects;
        end;
    else % no response means that the connection to the server is gone.
        kiks_server_disconnect;
        kiks_halt;
        errordlg('Connection to server lost.','KiKS network error');
    end;
end;
