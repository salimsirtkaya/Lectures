% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res=kiks_sim_prox(id,sample)
global KIKS_SIM_PROX_NOISE KIKS_SIM_PROX_EMAX KIKS_SIM_PROX_EMIN KIKS_SIM_PROX_EEXP KIKS_SIMPROX_STEPS KIKS_SIM_PROX_SCALE KIKS_MMPERPIXEL KIKS_SIM_PROX_STEP KIKS_SIM_PROX_DIST KIKS_1250 KIKS_ARENA_COLORMASK KIKS_PROX_DIR KIKS_PROX_ANG KIKS_ROBOT_MATRIX KIKS_PROX_POS KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_MONITOR_WIN KIKS_MONITOR_ON KIKS_RBT_TIME KIKS_MAXMOVLIMIT KIKS_sensdelay KIKS_SIMPROX_MAXDIST KIKS_PROX_ACCURACY KIKS_PROX_MINRAND KIKS_PROX_MAXRAND KIKS_PROX_NNET1 KIKS_PROX_NNET2 KIKS_PROX_NNET3 KIKS_PROX_NNET4 KIKS_PROX_NNET5 KIKS_PROX_NNET6 KIKS_PROX_NNET7 KIKS_PROX_NNET8 KIKS_PROX_NNET_ARRAY KIKS_PROX_USEARRAY;

if isempty(KIKS_PROX_USEARRAY) KIKS_PROX_USEARRAY=0; end;
sincelast=KIKS_RBT_TIME(abs(id))-KIKS_sensdelay(id);
if(sincelast<KIKS_MAXMOVLIMIT | sincelast<0.02)
    % According to the Khepera manual, proximity sensors update each 20 msec.
    return;
end;

prox_xvals = ((KIKS_ROBOT_MATRIX(id,2,2)+1)*cos(KIKS_PROX_ANG-KIKS_ROBOT_MATRIX(id,1,3))+KIKS_ROBOT_MATRIX(id,1,1))/KIKS_MMPERPIXEL;
prox_yvals = ((KIKS_ROBOT_MATRIX(id,2,2)+1)*sin(KIKS_PROX_ANG-KIKS_ROBOT_MATRIX(id,1,3))+KIKS_ROBOT_MATRIX(id,1,2))/KIKS_MMPERPIXEL;
prox_dirs  = KIKS_PROX_DIR+KIKS_ROBOT_MATRIX(id,1,3);
[tmp,sensors]=size(prox_xvals);

if nargin<2 sample=[]; end;
res=[];

proxval=[0 0 0 0 0 0 0 0];

dirs=[-pi/3:pi/9:pi/3];
for sens=1:sensors,
    num=0;
    proxangval=[0 0 0 0 0 0 0];
    
    proxstep=KIKS_PROX_ACCURACY;
    sumres(sens)=0;
    
    [ysz,xsz]=size(KIKS_ARENA_COLORMASK);
    for dir=-pi/3:pi/9:pi/3,
        num=num+1;
        % rotate ray_xvals and ray_yvals to get sensor relative coordinates
        
        cosdir=cos(prox_dirs(sens)-dir);
        sindir=sin(prox_dirs(sens)-dir);
        
        ray_xvals = round(KIKS_1250*cosdir+prox_xvals(sens));
        ray_yvals = round(-KIKS_1250*sindir+prox_yvals(sens));

        idx=((ray_xvals-1)*ysz+ray_yvals); % calculate index values for these points
        idx(find(idx>ysz*xsz))=ysz*xsz;
        idx(find(idx<1))=1;
        
        obst=find(KIKS_ARENA_COLORMASK(idx)); % get all non-zero entries

        if ~isempty(obst)
            dist=min(obst);
            xp=ray_xvals(dist);
            yp=ray_yvals(dist);
            c=KIKS_ARENA_COLORMASK(floor(yp),floor(xp));
            
            oldc=c;
            back=0;
            while (c>0 & back<KIKS_SIM_PROX_STEP)
                back=back+1;
                oldc=c;
                xp=xp-cosdir;
                yp=yp+sindir;
                c=KIKS_ARENA_COLORMASK(floor(yp),floor(xp));
            end;
            c=oldc;
            
            proxangval(num)=KIKS_SIM_PROX_DIST-((dist*KIKS_MMPERPIXEL)*ceil(KIKS_SIM_PROX_STEP/KIKS_MMPERPIXEL))+back;
            % Color sensitive falloff
            proxangval(num)=proxangval(num)-((proxangval(num)*0.5)*((255-c)/255));
        end;
        
        sumres(sens)=sumres(sens)+proxangval(num);
    end;
    res(sens,:)=proxangval;
end;

% Error settings
Emax = KIKS_SIM_PROX_EMAX; % Max relative error caused by noise when sensor reading is 1
Emin = KIKS_SIM_PROX_EMIN; % Max relative error caused by noise when sensor reading is 1000
Eexp = KIKS_SIM_PROX_EEXP; % The larger Eexp, the less frequent large errors are. 
% Eexp=1 ==> Errors are evenly distributed across the error range,
% Eexp=Inf ==> No errors,
% Eexp>1 ==> Large errors are less common than small errors,
% Eexp<1 ==> Large errors are more common than small errors.
for sens=1:sensors
    if sumres(sens)>0
        if(KIKS_PROX_USEARRAY==0) % calculate neural network
            switch (mod(sens-1,8))
                case 0
                    simsens=sim(KIKS_PROX_NNET1,res(sens,:)');
                case 1
                    simsens=sim(KIKS_PROX_NNET2,res(sens,:)');
                case 2
                    simsens=sim(KIKS_PROX_NNET3,res(sens,:)');
                case 3
                    simsens=sim(KIKS_PROX_NNET4,res(sens,:)');
                case 4
                    simsens=sim(KIKS_PROX_NNET5,res(sens,:)');
                case 5
                    smsens=sim(KIKS_PROX_NNET6,res(sens,:)');
                case 6
                    simsens=sim(KIKS_PROX_NNET7,res(sens,:)');
                case 7
                    simsens=sim(KIKS_PROX_NNET8,res(sens,:)');
            end;
        else % find values in array
            ix=round(res(sens,:)/KIKS_SIM_PROX_SCALE);
            if sum(ix)>0
                ix=ix+1;
                ix(find(ix>KIKS_SIMPROX_STEPS))=KIKS_SIMPROX_STEPS;
                ix(find(ix<1))=1;
                simsens=KIKS_PROX_NNET_ARRAY(ix(1),ix(2),ix(3),ix(4),ix(5),ix(6),ix(7))*(1023/255);
            else
                simsens=0;
            end;
        end;
        
        errQ=Emax-(simsens/1000)*(Emax-Emin);
        %      randQ=KIKS_PROX_MINRAND/KIKS_PROX_MAXRAND;
        minrand=-KIKS_PROX_MINRAND*errQ;
        maxrand=KIKS_PROX_MAXRAND*errQ;
        if rand<0.5 rdir=maxrand; else rdir=minrand; end;
        randval=1+((rdir)*rand^Eexp);
        proxval(sens)=min(1023,round(simsens*randval)); 
    end;
end;
KIKS_sensdelay(id)=KIKS_RBT_TIME(abs(id));
%if KIKS_ROBOTTYPE==2
%    baseval=90+rand(1,8)*20;
%    proxval=round(baseval+proxval);
%    proxval(find(proxval>1023))=1023;
%end;
[rows,cols]=size(proxval);
noiseval=rand(rows,cols)*1023;

KIKS_ROBOT_MATRIX(id,KIKS_PROX_POS,:)=min(1023,round(proxval*((100-KIKS_SIM_PROX_NOISE)/100)+noiseval*(KIKS_SIM_PROX_NOISE/100)));