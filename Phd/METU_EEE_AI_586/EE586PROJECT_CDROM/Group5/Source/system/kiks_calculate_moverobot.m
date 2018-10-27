% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_calculate_moverobot(id, v_time)
global KIKS_BALLARRAY KIKS_DIST_STR_COORD KIKS_DIST_FWD KIKS_DIST_BWD KIKS_DIST_STR KIKS_COLL_CNT KIKS_COLL_L KIKS_COLL_R KIKS_OLDSPD KIKS_TRACE_MAX KIKS_ROBOT_MATRIX KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_SPDC KIKS_RBT_TIME KIKS_INT_LIMIT KIKS_trace KIKS_tracestep;

% TODO: indicate movement error when colliding server side
if isempty(KIKS_DIST_STR_COORD)
    KIKS_DIST_STR_COORD=[KIKS_ROBOT_MATRIX(id,1,1) KIKS_ROBOT_MATRIX(id,1,2)];
end;

% spin the wheels
oEnc=[KIKS_ROBOT_MATRIX(id,1,7); KIKS_ROBOT_MATRIX(id,1,8)]; % old counter
KIKS_ROBOT_MATRIX(id,1,7)=KIKS_ROBOT_MATRIX(id,1,7)+(v_time*KIKS_ROBOT_MATRIX(id,1,5)*100);
KIKS_ROBOT_MATRIX(id,1,8)=KIKS_ROBOT_MATRIX(id,1,8)+(v_time*KIKS_ROBOT_MATRIX(id,1,6)*100);
exp_Enc=[KIKS_ROBOT_MATRIX(id,1,7); KIKS_ROBOT_MATRIX(id,1,8)]; % expected new counter

rEnc=exp_Enc;

% calculate new position
oldPosition=oEnc*(KIKS_SPDC/100);
newPosition = exp_Enc*(KIKS_SPDC/100);
posdiff=newPosition-oldPosition;
dTheta = (posdiff(2)-posdiff(1))/KIKS_ROBOT_MATRIX(id,2,1); % degrees to rotate in radians
dist = sum(posdiff)/2; % distance to move in Theta/2 direction (curved distance - not direct)
if dist>0
    KIKS_DIST_FWD=KIKS_DIST_FWD+dist;
else
    KIKS_DIST_BWD=KIKS_DIST_BWD+abs(dist);
end;

if abs(dist)>0 qTheta=dTheta/dist; end;
mod_l=mod(abs(dist),KIKS_INT_LIMIT)*sign(dist);
int_dist=abs(dist-mod_l); % 0 => no interpolation needed
move=1;
inc_Enc=oEnc;
diff_Enc=exp_Enc-oEnc;
while(move==1) % interpolate if necessary
    if(abs(int_dist)>abs(mod_l))
        l=KIKS_INT_LIMIT*sign(dist);
        int_dist=int_dist-KIKS_INT_LIMIT;
    else
        l=mod_l;
        move=0;
    end;
    
    if abs(dist)>0 iTheta = qTheta*l; else iTheta=dTheta; end; % degrees to rotate in this step
    old_Enc=inc_Enc;
    if dist==0 p_Enc=1; else p_Enc=l/dist; end;
    inc_Enc=inc_Enc+diff_Enc*p_Enc;
    
    xp=KIKS_ROBOT_MATRIX(id,1,1);
    oxp=xp;
    yp=KIKS_ROBOT_MATRIX(id,1,2);
    oyp=yp;
    Theta=KIKS_ROBOT_MATRIX(id,1,3);
    oTheta=Theta;
    
    mv_l=l; % this only holds for small angles of rotation!
    
    % Simplistic, but fast, calculation of
    % new position.
    % Move the Khepera mv_l pixels on a straight line in the direction given by
    % Theta+iTheta/2 radians (average of Theta and Theta+iTheta -
    % old and new angle respectively)
    % If iTheta is small, the straight line
    % between the old and the new positions is estimated to be the 
    % length of the curved line. The error will become bigger the 
    % larger the angle is, which is why small interpolation intervals should
    % be used.
    xpadd=cos(Theta + iTheta/2)*mv_l;
    ypadd=-sin(Theta + iTheta/2)*mv_l;
    oxpadd=xpadd;
    oypadd=ypadd;
    nxpadd=xpadd;
    nypadd=ypadd;
    xp = xp+xpadd;
    yp = yp+ypadd;
    nxp=xp;
    nyp=yp;
    Theta = Theta + iTheta;
    KIKS_ROBOT_MATRIX(id,1,1)=xp;
    KIKS_ROBOT_MATRIX(id,1,2)=yp;
    KIKS_ROBOT_MATRIX(id,1,3)=Theta;
    
    % are there any objects to push? If not, don't make this call.
    if ~isempty(KIKS_BALLARRAY) kiks_pushobj_test(id,v_time); end; % push objects
    collided=kiks_detect_collision(id);
    if collided(1)==1 & size(collided,1)>1 % TODO: fix counters
        % server provided the coordinates, we may have collided server-side
        planned_dist=abs(sqrt(xp^2+yp^2)-sqrt(oxp^2+oyp^2));
        actual_dist=abs(sqrt(collided(2)^2+collided(3)^2)-sqrt(oxp^2+oyp^2));
        inc_Enc=old_Enc;
        KIKS_ROBOT_MATRIX(id,1,1)=collided(2);
        KIKS_ROBOT_MATRIX(id,1,2)=collided(3);
        ol=planned_dist;
        nl=actual_dist;
        if(abs(ol)>0)
            mov=0.1+rand*0.1+nl/ol;
            if(mov>1) mov=1; end;
        else
            mov=0.1+rand*0.1;
        end;
        inc_Enc=inc_Enc+diff_Enc*p_Enc*mov; % final counter      
    elseif collided(1)>1
        inc_Enc=old_Enc;
        move=0;
        % Set xp, yp to suggested collided(2), collided(3) if provided
        nTheta=Theta;
        nxp=xp; nyp=yp;
        if size(collided,1)==1
            % local collision
            xp=oxp;
            yp=oyp;
        else
            % server collision
            xp=collided(2);
            yp=collided(3);      
        end;
        Theta=oTheta;
        KIKS_ROBOT_MATRIX(id,1,1)=xp;
        KIKS_ROBOT_MATRIX(id,1,2)=yp;
        KIKS_ROBOT_MATRIX(id,1,3)=Theta;
        xpadd=(cos(Theta + iTheta/2)/2)*sign(mv_l);
        nxpadd=0;
        ypadd=(-sin(Theta + iTheta/2)/2)*sign(mv_l);
        nypadd=0;
        
        kiks_pushobj_test(id,v_time); % push objects     
        collided=kiks_detect_collision(id);
        test_xp=xp;
        test_yp=yp;
        while(collided(1)<=1 & abs(xp-nxp)>abs(xpadd))
            xp=test_xp;
            yp=test_yp;
            test_xp=test_xp+xpadd;
            nxpadd=nxpadd+xpadd;
            test_yp=test_yp+ypadd;
            nypadd=nypadd+ypadd;
            KIKS_ROBOT_MATRIX(id,1,1)=test_xp;
            KIKS_ROBOT_MATRIX(id,1,2)=test_yp;      
            collided=kiks_detect_collision(id);
            if (collided(1)>1)
                test_xp=xp+xpadd;
                test_yp=yp;
                KIKS_ROBOT_MATRIX(id,1,1)=test_xp;
                KIKS_ROBOT_MATRIX(id,1,2)=test_yp;      
                collided=kiks_detect_collision(id);
                if(collided(1)>1)
                    test_xp=xp;
                    test_yp=yp+ypadd;
                    KIKS_ROBOT_MATRIX(id,1,1)=test_xp;
                    KIKS_ROBOT_MATRIX(id,1,2)=test_yp;      
                    collided=kiks_detect_collision(id);
                    if(collided(1)<=1)
                        yp=test_yp;
                    end;
                else
                    xp=test_xp;
                end;
                collided(1)=2;
            end;
        end;
        nxpadd=nxpadd-xpadd;
        nypadd=nypadd-ypadd;
        KIKS_ROBOT_MATRIX(id,1,1)=xp;
        KIKS_ROBOT_MATRIX(id,1,2)=yp;
        
        if(abs(nxp-oxp)>0)
            Theta=Theta+iTheta*0.5; % rotate a bit...
        end;
        KIKS_ROBOT_MATRIX(id,1,3)=Theta;
        ol=sqrt(oxpadd^2+oypadd^2);
        nl=sqrt(nxpadd^2+nypadd^2);
        if(abs(ol)>0)
            mov=0.1+rand*0.1+nl/ol;
            if(mov>1) mov=1; end;
        else
            mov=0.1+rand*0.1;
        end;
        inc_Enc=inc_Enc+diff_Enc*p_Enc*mov; % final counter
    end;
end;

KIKS_ROBOT_MATRIX(id,1,7:8)=inc_Enc;
% approximate error
if isempty(KIKS_COLL_CNT)
    KIKS_COLL_CNT=1;
else
    KIKS_COLL_CNT=KIKS_COLL_CNT+1;
    if KIKS_COLL_CNT>3 KIKS_COLL_CNT=1; end;
end;

if KIKS_ROBOT_MATRIX(id,2,4)==1 % position mode
    errEnc=exp_Enc-inc_Enc; % counter error
    KIKS_COLL_L(KIKS_COLL_CNT)=errEnc(1);
    KIKS_COLL_R(KIKS_COLL_CNT)=errEnc(2);
    if KIKS_COLL_L(KIKS_COLL_CNT)==0 & KIKS_COLL_R(KIKS_COLL_CNT)==0
        KIKS_COLL_L=[0 0 0];
        KIKS_COLL_R=[0 0 0];
    end;
    
    KIKS_ROBOT_MATRIX(id,2,5)=KIKS_ROBOT_MATRIX(id,2,5)+mean(KIKS_COLL_L);
    KIKS_ROBOT_MATRIX(id,2,8)=KIKS_ROBOT_MATRIX(id,2,8)+mean(KIKS_COLL_R);  
else % speed mode
    tSpd=[KIKS_ROBOT_MATRIX(id,1,5) KIKS_ROBOT_MATRIX(id,1,6)];
    if abs(exp_Enc(1)-oEnc(1))>0 errSpd(1)=(inc_Enc(1)-oEnc(1))/(exp_Enc(1)-oEnc(1))*tSpd(1); else errSpd(1)=KIKS_ROBOT_MATRIX(id,1,5); end;
    if abs(exp_Enc(2)-oEnc(2))>0 errSpd(2)=(inc_Enc(2)-oEnc(2))/(exp_Enc(2)-oEnc(2))*tSpd(2); else errSpd(2)=KIKS_ROBOT_MATRIX(id,1,6); end;
    KIKS_COLL_L(KIKS_COLL_CNT)=errSpd(1);
    KIKS_COLL_R(KIKS_COLL_CNT)=errSpd(2);
    if KIKS_COLL_L(KIKS_COLL_CNT)==KIKS_ROBOT_MATRIX(id,1,5) & KIKS_COLL_R(KIKS_COLL_CNT)==KIKS_ROBOT_MATRIX(id,1,6)
        KIKS_COLL_L=[KIKS_ROBOT_MATRIX(id,1,5) KIKS_ROBOT_MATRIX(id,1,5) KIKS_ROBOT_MATRIX(id,1,5)];
        KIKS_COLL_R=[KIKS_ROBOT_MATRIX(id,1,6) KIKS_ROBOT_MATRIX(id,1,6) KIKS_ROBOT_MATRIX(id,1,6)];
    end;   
    
    KIKS_ROBOT_MATRIX(id,2,5)=KIKS_ROBOT_MATRIX(id,1,5)-mean(KIKS_COLL_L);
    KIKS_ROBOT_MATRIX(id,2,8)=KIKS_ROBOT_MATRIX(id,1,6)-mean(KIKS_COLL_R);
end;

KIKS_RBT_TIME(id)=KIKS_RBT_TIME(id)+v_time;
KIKS_tracestep(id)=KIKS_tracestep(id)+1;
if ceil(KIKS_tracestep(id))>KIKS_TRACE_MAX
    kiks_status('Warning:  Khepera trace points reset. Increase KIKS_TRACE_MAX in kiks_preferences.m.');
    KIKS_tracestep(id)=0.5;
end;

tmpvec=KIKS_DIST_STR_COORD-[KIKS_ROBOT_MATRIX(id,1,1) KIKS_ROBOT_MATRIX(id,1,2)];
KIKS_DIST_STR=sqrt(tmpvec(1)^2+tmpvec(2)^2);
KIKS_trace(id,ceil(KIKS_tracestep(id)),:)=[KIKS_ROBOT_MATRIX(id,1,1)-KIKS_WALL_WIDTH+KIKS_WALL_RENDER KIKS_ROBOT_MATRIX(id,1,2)-KIKS_WALL_WIDTH+KIKS_WALL_RENDER];
