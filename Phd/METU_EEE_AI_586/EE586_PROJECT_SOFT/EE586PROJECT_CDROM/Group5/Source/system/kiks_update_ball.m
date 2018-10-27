% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_update_ball(id,runtime,notid)
global KIKS_OBJECT_BALL_SMALLRATIO KIKS_OBJECT_SMALLBALL_MASK KIKS_OBJECT_BALL_SMALLRATIO KIKS_REMOTE_ARRAY KIKS_MMPERPIXEL KIKS_TRACE_MAX KIKS_ROUNDOBJECT_RADIUS KIKS_ROUNDOBJDATA KIKS_ROUNDOBJARRAY KIKS_PUSH_TMPARRAY KIKS_MAXMOVLIMIT KIKS_BALLARRAY KIKS_OBJECT_BALL_UPD KIKS_WALL_WIDTH KIKS_ARENA_MASK KIKS_BALLDATA KIKS_OBJECT_BALL_RADIUS KIKS_OBJECT_BALL_MASK KIKS_WALL_WIDTH KIKS_WALL_RENDER;

if ~runtime
    return;
end;

if isempty(KIKS_OBJECT_BALL_UPD(id)) KIKS_OBJECT_BALL_UPD(id)=0; end;
KIKS_OBJECT_BALL_UPD(id)=KIKS_OBJECT_BALL_UPD(id)+runtime;
e=0.25;
cylinder=KIKS_BALLDATA(id,5);
theRadius=KIKS_OBJECT_BALL_RADIUS;
if cylinder theRadius=theRadius*KIKS_OBJECT_BALL_SMALLRATIO; end;

if KIKS_BALLDATA(id,3)>0
    % this one is moving  
    spd=KIKS_BALLDATA(id,3); % mm/sec
    ang=real(KIKS_BALLDATA(id,4));
    distance=spd*runtime; % mm to move
    coll=0;
    rest=mod(distance,10);
    steps=(distance-rest)/10;
    step=0;
    moving=1;
    while coll==0 & moving==1
        xp=KIKS_BALLDATA(id,1);
        yp=KIKS_BALLDATA(id,2);
        
        step=step+1;
        if step>steps dist=rest; moving=0; else dist=10; end;
        
        nxp=xp+cos(ang)*dist;
        nyp=yp-sin(ang)*dist;
        [ys,xs]=size(KIKS_ARENA_MASK);
        ys=ys*KIKS_MMPERPIXEL;
        xs=xs*KIKS_MMPERPIXEL;
        if (nxp<KIKS_WALL_WIDTH) nxp=KIKS_WALL_WIDTH; end;
        if (nxp>xs-KIKS_WALL_WIDTH) nxp=xs-KIKS_WALL_WIDTH; end;
        if (nyp<KIKS_WALL_WIDTH) nyp=KIKS_WALL_WIDTH; end;
        if (nyp>ys-KIKS_WALL_WIDTH) nyp=ys-KIKS_WALL_WIDTH; end;
        
        if cylinder
            nspd=spd-(20/(KIKS_OBJECT_BALL_SMALLRATIO^3))*runtime;
        else
            nspd=spd-20*runtime;
        end;
        nang=ang;
        
        kiks_arena_subball(id,floor(xp),floor(yp));  
        
        % detect collision
        minx = floor(nxp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % xpos - robot radius
        miny = floor(nyp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % ypos - robot radius
        maxx = floor(nxp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
        maxy = floor(nyp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
        
        if cylinder
            map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_SMALLBALL_MASK;
        else
            map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_BALL_MASK;
        end;
        res = max(max(map));
        
        if res>1
            coll=1;
            
            bst=0;
            while(res>1 & bst<dist)
                bst=bst+1;
                ores=res;
                omap=map;
                oxp=nxp;
                oyp=nyp;
                nxp=nxp-cos(ang);
                nyp=nyp+sin(ang);
                minx = floor(nxp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % xpos - robot radius
                miny = floor(nyp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % ypos - robot radius
                maxx = floor(nxp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
                maxy = floor(nyp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
                if cylinder
                    map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_SMALLBALL_MASK;
                else
                    map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_BALL_MASK;
                end;
                res = max(max(map));
            end;
            
            res=ores;
            nxp=oxp;
            nyp=oyp;
            map=omap;
            
            % check for collision against other balls
            objs=max(KIKS_BALLARRAY);
            [rows,cols]=size(KIKS_BALLARRAY);
            if(objs>1)
                for i=1:cols,
                    if KIKS_BALLARRAY(i)~=id & KIKS_BALLARRAY(i)~=notid
                        x = [KIKS_BALLDATA(KIKS_BALLARRAY(i),1)-nxp KIKS_BALLDATA(KIKS_BALLARRAY(i),2)-nyp];
                        otherRadius=KIKS_OBJECT_BALL_RADIUS;
                        if KIKS_BALLDATA(KIKS_BALLARRAY(i),5) otherRadius=KIKS_OBJECT_BALL_RADIUS*KIKS_OBJECT_BALL_SMALLRATIO; end;
                        if norm(x)<=theRadius+otherRadius+1
                            kspd1=KIKS_BALLDATA(id,3);
                            kvec1=[cos(KIKS_BALLDATA(id,4))*kspd1 -sin(KIKS_BALLDATA(id,4))*kspd1];
                            kspd2=KIKS_BALLDATA(KIKS_BALLARRAY(i),3);
                            kvec2=[cos(KIKS_BALLDATA(KIKS_BALLARRAY(i),4))*kspd2 -sin(KIKS_BALLDATA(KIKS_BALLARRAY(i),4))*kspd2];
                            kiks_calculate_ballspd(KIKS_BALLARRAY(i),kvec1,kspd1,x/norm(x));
                            kiks_calculate_ballspd(id,kvec2,kspd2,x/norm(x));
                            nspd=KIKS_BALLDATA(id,3);
                            nang=KIKS_BALLDATA(id,4);          
                        end;
                    end;
                end;
            end;         
            
            % check for collision against remote robots
            if ~isempty(KIKS_REMOTE_ARRAY)
                entries=8; % entries per object
                nr = size(KIKS_REMOTE_ARRAY,1)/entries;
                for i=0:nr-1
                    rkxp=floor(KIKS_REMOTE_ARRAY(3+i*entries));
                    rkyp=floor(KIKS_REMOTE_ARRAY(4+i*entries));
                    lv=floor(KIKS_REMOTE_ARRAY(7+i*entries));
                    rv=floor(KIKS_REMOTE_ARRAY(8+i*entries));
                    x = [rkxp-nxp rkyp-nyp];
                    if norm(x)<=theRadius+KIKS_REMOTE_ARRAY(6+i*entries)+1
                        kspd=kiks_p2mm(mean(lv,rv))*100;
                        kvec=[cos(KIKS_REMOTE_ARRAY(5+i*entries))*kspd -sin(KIKS_REMOTE_ARRAY(5+i*entries))*kspd];
                        kiks_calculate_ballspd(id,kvec,kspd,x/norm(x));
                        nspd=KIKS_BALLDATA(id,3);
                        nang=KIKS_BALLDATA(id,4);
                    end;
                end;
            end;
            
            minx = floor(nxp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % xpos - robot radius
            miny = floor(nyp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % ypos - robot radius
            maxx = floor(nxp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
            maxy = floor(nyp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
            if cylinder
                map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_SMALLBALL_MASK;
            else
                map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_BALL_MASK;
            end;
            res = max(max(map));
            
            if (res>1)
                % collided - find angle
                [row,col]=find(map==res);
                row=-(row-floor(theRadius/KIKS_MMPERPIXEL));
                col=col-floor(theRadius/KIKS_MMPERPIXEL);
                d=sqrt(row.^2+col.^2);
                d=d+1;
                md=min(d);
                ps=find(d==md);
                
                ptx=mean(col(ps));
                pty=mean(row(ps));
                
                if (abs(pty)<abs(ptx)) 
                    cang=asin(abs(pty)/md);
                else
                    cang=acos(abs(ptx)/md);
                end;
                if pty<0  & ptx>=0 cang=(2*pi)-cang; end;
                if pty>=0 & ptx<0  cang=pi-cang; end;
                if pty<0  & ptx<0  cang=pi+cang; end;
                nrm=mod(cang+pi,2*pi);
                nang=mod(nrm-((ang+pi)-nrm),2*pi);
                nspd=spd*sqrt((sin(nrm-ang))^2+e^2*(cos(nrm-ang))^2);
                nxp=xp;
                nyp=yp;
                
            end;
        end;
        
        
        KIKS_BALLDATA(id,1)=nxp;
        KIKS_BALLDATA(id,2)=nyp;
        KIKS_BALLDATA(id,3)=nspd;
        KIKS_BALLDATA(id,4)=nang;
        kiks_arena_addball(id,floor(nxp),floor(nyp));
    end;
    
    kiks_draw_ball(id);
end;
% check for collision against remote robots
if ~isempty(KIKS_REMOTE_ARRAY)
    xp=KIKS_BALLDATA(id,1);
    yp=KIKS_BALLDATA(id,2);      
    entries=6; % entries per object
    nr = size(KIKS_REMOTE_ARRAY,1)/entries;
    for i=0:nr-1
        rkxp=floor(KIKS_REMOTE_ARRAY(3+i*entries));
        rkyp=floor(KIKS_REMOTE_ARRAY(4+i*entries));
        x = [xp-rkxp yp-rkyp];
        if norm(x)<=theRadius+KIKS_REMOTE_ARRAY(6+i*entries)+1
            kspd=200;
            kvec=[cos(KIKS_REMOTE_ARRAY(5+i*entries))*kspd -sin(KIKS_REMOTE_ARRAY(5+i*entries))*kspd];
            kiks_calculate_ballspd(id,kvec,kspd,x/norm(x));           
        end;
    end;
end;

