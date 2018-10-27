% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_calculate_ballspd(ballnum,ovec,ospd,cvec)
global KIKS_BALLDATA KIKS_BALLARRAY

e=0.95;

bvec=[cos(KIKS_BALLDATA(ballnum,4))*KIKS_BALLDATA(ballnum,3) -sin(KIKS_BALLDATA(ballnum,4))*KIKS_BALLDATA(ballnum,3)];
% find angle alpha between bvec and cvec, beta between ovec and cvec
if norm(ovec)>0 & norm(bvec)>0 % both in movement
    alpha=acos((bvec(1)*cvec(1)+bvec(2)*cvec(2))/(norm(bvec)*norm(cvec)));
    beta=acos((ovec(1)*cvec(1)+ovec(2)*cvec(2))/(norm(ovec)*norm(cvec)));
    % new direction coeff. for ball
    v=KIKS_BALLDATA(ballnum,3)*sin(alpha); % speed component perpendicular to cvec
    u=((1-e)*KIKS_BALLDATA(ballnum,3)*cos(alpha)+ospd*cos(beta)*(1+e))/2; % speed component parallell to cvec
    pvec=cvec*[cos(pi/2) -sin(pi/2); sin(pi/2) cos(pi/2)]; % vector perpendicular to cvec
    nbvec=v*pvec+u*cvec;
    nbvec(2)=-nbvec(2);
    % update ball
    KIKS_BALLDATA(ballnum,3)=norm(nbvec);
    nang=atan(nbvec(2)/nbvec(1));
    
    if(cvec(1)<0)
        nang=nang+pi;  % hack...
    end;
    
    xv=cos(nang)*50;
    yv=-sin(nang)*50;
    if nang==NaN nang=0; end;
    
    KIKS_BALLDATA(ballnum,4)=nang;
elseif norm(ovec)>0 % ball is at rest
    beta=acos((ovec(1)*cvec(1)+ovec(2)*cvec(2))/(norm(ovec)*norm(cvec)));
    u=(ospd*cos(beta)*(1+e))/2;
    nbvec=u*cvec;
    nbvec(2)=-nbvec(2);
    
    KIKS_BALLDATA(ballnum,3)=norm(nbvec);
    nang=atan(nbvec(2)/nbvec(1));
    
    if(cvec(1)<0)
        nang=nang+pi;  % hack...
    end;
    KIKS_BALLDATA(ballnum,4)=nang;
end;