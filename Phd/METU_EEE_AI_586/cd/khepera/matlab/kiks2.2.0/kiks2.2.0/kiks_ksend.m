% kiks_ksend(CMD, port, timeout)
% sends the command CMD to the KIKS_ROBOT and returns response.
% CMD is of the form 'command,arg1,arg2,...,argn' and must end with 
% a linefeed (char(10)).
%
% Also main simulator function.
%
% -----------------------------------------------
%  (c) 2000 Theodor Storm (theodor@tstorm.se)
%  http://www.tstorm.se
% -----------------------------------------------

function response = kiks_ksend(CMD, ref, timeout)
global KIKS_KIKSNET_COMMAND KIKS_TURRETS KIKS_MONITOR_ON KIKS_ILLEGAL_KEYS KIKS_ILLEGAL_KEYS_CHK KIKS_GLOBALTIME_LASTSHOT KIKS_MOVIE KIKS_MOVIENAME KIKS_ILLEGAL_KEYS KIKS_AVIMOVIE KIKS_FID KIKS_COLOR_BACKGROUND KIKS_ARENA_HDL KIKS_GUI_HDL KIKS_DIST_FWD KIKS_DIST_BWK KIKS_DIST_STR KIKS_ANNOY_REMIND_MSG_CLOCK KIKS_ANNOY_REMIND_MSG_TIME KIKS_REGCODE KIKS_BALLDATA KIKS_SIM_PAUSE KIKS_SIM_STEP KIKS_SIM_LINVIS_2DMODE KIKS_BALL_TRACE_TIME KIKS_WALL_CLOCK KIKS_GLOBALTIME KIKS_GLOBALTIME_OLD KIKS_COMPUTER_SPEED KIKS_COMPUTER_SPEED_SIM KIKS_BALLARRAY KIKS_SIM_LINVIS_RP KIKS_ARENA_MX KIKS_TIMESCALE KIKS_ROBOT_MATRIX KIKS_PROX_POS KIKS_LIGHT_POS KIKS_SESSIONACTIVE KIKS_VERSION KIKS_MAXMOVLIMIT KIKS_RBTARRAY KIKS_PORT KIKS_GUI_HDL KIKS_HALT_BOOL KIKS_ACC_TIME KIKS_LINKTIME KIKS_OTHERTIME KIKS_PAUSETIME KIKS_SIMTIME KIKS_KSEND_CONSTANT KIKS_KSEND_VARIATION KIKS_LIC_CDE KIKS_LIC_VFK KIKS_LIC_LIC;

if isempty(ref) | length(ref)<4
    error('KIKS_KSEND read/write error');
    return;
end;

if(ref(1)==ref(2) & ref(2)==ref(3) & ref(3)==ref(4) & ref(1)<0)   
    mattime=etime(clock,KIKS_OTHERTIME);
    
    command=''; args=[];
    
    if ~isempty(CMD)
        [command, args] = kiks_decode(CMD);
    end;
    
    port = abs(ref(1));
    
    if KIKS_PORT(abs(ref(1)))~=1
        error('KIKS_KSEND read/write error');
        return;
    end;
    
    KIKS_KIKSNET_COMMAND='';
    
    switch command
    case 'D' % new motor speeds - we send them to the server to improve client prediction.
        if length(args)~=2
            % protocol error
            response=['z,Protocol error'];
        else
            KIKS_ROBOT_MATRIX(port,6,7)=args(1);
            KIKS_ROBOT_MATRIX(port,6,8)=args(2);
        end;
    case 'T' % some battle turret commands are handled by the KiKSnet server.
        tnum=args(1);
        if args(1)<10
            [tcommand,targs]=kiks_decode(CMD(5:end));
        else
            [tcommand,targs]=kiks_decode(CMD(6:end));
        end;                
        if tnum==4 % Radio turret
            switch tcommand
            case 'F' % Read status
                KIKS_KIKSNET_COMMAND='RADIO_STATUS';
            case 'R' % Read buffer
                KIKS_KIKSNET_COMMAND='RADIO_READ';
            case 'S' % Send buffer
                KIKS_KIKSNET_COMMAND=sprintf('RADIO_SEND %s',CMD(7:end));
            end;
        end;
        if tnum==99 % Battle turret
            switch tcommand
            case 'F' % fire cannon
                KIKS_KIKSNET_COMMAND='FIRE';
            case 'S' % read sensors
                KIKS_KIKSNET_COMMAND='SENSORS';
            end;
        end;
    end;
    
    % pause the simulation?
    blink=0;
    paused=0;
    forcepause=0;
    p0=clock;
    while((KIKS_SIM_PAUSE~=0 & KIKS_SIM_STEP==0) | (forcepause>0 & etime(clock,p0)<forcepause)) 
        if etime(clock,p0)>=forcepause & forcepause>0
            h=findobj(KIKS_GUI_HDL,'tag','pausesim');
            set(h,'enable','on'); 
            h=findobj(KIKS_GUI_HDL,'tag','haltsim');
            set(h,'enable','on');      
        end;
        
        paused=1;
        h=findobj(KIKS_GUI_HDL,'tag','time');
        pause(0.1); 
        blink=blink+1;
        if(blink==5)
            set(h,'Visible','off');
        end; 
        if(blink==10)
            set(h,'Visible','on');
            blink=0;
        end;
    end;
    if (paused~=0) set(h,'Visible','on'); end;
    
    % continue the simulation 
    t0=clock;       
    
    if(~isempty(KIKS_HALT_BOOL) & KIKS_HALT_BOOL==1)
        KIKS_HALT_BOOL=0;
        [rows,cols]=size(KIKS_RBTARRAY);
        for i=1:cols
            kiks_ksend(['D,0,0' 10],[-KIKS_RBTARRAY(i) -KIKS_RBTARRAY(i) -KIKS_RBTARRAY(i) -KIKS_RBTARRAY(i)]); % stop movement
            kiks_kclose([-KIKS_RBTARRAY(i) -KIKS_RBTARRAY(i) -KIKS_RBTARRAY(i) -KIKS_RBTARRAY(i)]); % close connection
        end;
        error('Simulation halted.');
    end;  
    
    if isempty(KIKS_PAUSETIME) KIKS_PAUSETIME=0; end;
    if isempty(KIKS_SESSIONACTIVE) error('<KiKS error> No KiKS session found.'); return; end;
    if isempty(KIKS_SIMTIME) KIKS_SIMTIME=0; end;
    if KIKS_COMPUTER_SPEED>0
        compacc=KIKS_COMPUTER_SPEED_SIM/KIKS_COMPUTER_SPEED;
    else
        compacc=1;
    end;
    
    if (KIKS_TIMESCALE<0)
        runtime=(compacc*mattime)+KIKS_PAUSETIME+KIKS_LINKTIME; % time spent in main program since last call to kiks_ksend + time for last ksend call
    else
        if ~isempty(KIKS_WALL_CLOCK)
            runtime=etime(clock,KIKS_WALL_CLOCK)*compacc;
        else
            runtime=0;
            KIKS_WALL_CLOCK=clock;
        end;
        if runtime>0
            KIKS_WALL_CLOCK=clock;
        end;
    end;
    
    KIKS_GLOBALTIME=KIKS_GLOBALTIME+runtime;
    KIKS_ACC_TIME(1)=KIKS_ACC_TIME(1)+runtime;
    if(KIKS_TIMESCALE<0) % high precision time mode
        if(KIKS_SIM_STEP~=0 | KIKS_ACC_TIME(1)>KIKS_MAXMOVLIMIT)
            kiks_updaterobot(1,KIKS_ACC_TIME(1));
            KIKS_ACC_TIME(1)=0;
            if (KIKS_MONITOR_ON(1)==1) kiks_monitor_update(1); end;
        end;
    elseif(KIKS_SIMTIME>=0) % wall clock mode - update position as often as possible
        kiks_updaterobot(1,KIKS_ACC_TIME(1));
        KIKS_ACC_TIME(1)=0;
        kiks_monitor_update(1);
    end;
    drawnow;
    
    % move ze bôlls
    if ~isempty(KIKS_BALLDATA)
        if (KIKS_TIMESCALE<0 | KIKS_SIMTIME>=0) & max(KIKS_BALLDATA(:,3))~=0
            b=find(KIKS_BALLDATA(:,3));
            [nr,tmp]=size(b);
            for i=1:nr
                kiks_update_ball(KIKS_BALLARRAY(b(i)),runtime,KIKS_BALLARRAY(b(i)));
            end;
        end;
    end;
    
    switch command
    case 'T' % external turret - these modules are located in kiks/turrets/.
        response=['z,Turret order not supported'];
        [tmp,turrets]=size(KIKS_TURRETS);
        if (tnum<=turrets & ~isempty(KIKS_TURRETS{tnum}))
            response = feval(KIKS_TURRETS{tnum},tcommand,targs);
        end;
    case 'B'
        response=[sprintf('b,%s,%s',KIKS_VERSION,KIKS_VERSION)];
    case 'C'
        if length(args)~=2
            response=['z,Protocol error'];
        else
            response=['c'];
            KIKS_ROBOT_MATRIX(port,1,4) = 1;
            KIKS_ROBOT_MATRIX(port,2,3)=0; % lT = 0
            KIKS_ROBOT_MATRIX(port,2,4)=1; % lM = 1
            KIKS_ROBOT_MATRIX(port,2,5)=0; % lE = 0 (always reset)
            KIKS_ROBOT_MATRIX(port,2,6)=0; % rT = 0
            KIKS_ROBOT_MATRIX(port,2,7)=1; % rM = 1
            KIKS_ROBOT_MATRIX(port,2,8)=0; % rE = 0 (always reset)
            
            KIKS_ROBOT_MATRIX(port,5,5) = args(1); % left wheel target
            KIKS_ROBOT_MATRIX(port,5,6) = args(2); % right wheel target
            KIKS_ROBOT_MATRIX(port,5,7) = 0;
            lprf=kiks_calculate_speed_profile(KIKS_ROBOT_MATRIX(port,5,1),KIKS_ROBOT_MATRIX(port,5,2),KIKS_ROBOT_MATRIX(port,1,7),KIKS_ROBOT_MATRIX(port,5,5));
            rprf=kiks_calculate_speed_profile(KIKS_ROBOT_MATRIX(port,5,3),KIKS_ROBOT_MATRIX(port,5,4),KIKS_ROBOT_MATRIX(port,1,8),KIKS_ROBOT_MATRIX(port,5,6));
            KIKS_ROBOT_MATRIX(port,6,1)=lprf(1);
            KIKS_ROBOT_MATRIX(port,6,2)=lprf(2);
            KIKS_ROBOT_MATRIX(port,6,3)=lprf(3);
            KIKS_ROBOT_MATRIX(port,6,4)=lprf(4);
            KIKS_ROBOT_MATRIX(port,6,5)=lprf(5);
            KIKS_ROBOT_MATRIX(port,6,6)=lprf(6);   
            KIKS_ROBOT_MATRIX(port,7,1)=rprf(1);
            KIKS_ROBOT_MATRIX(port,7,2)=rprf(2);
            KIKS_ROBOT_MATRIX(port,7,3)=rprf(3);
            KIKS_ROBOT_MATRIX(port,7,4)=rprf(4);
            KIKS_ROBOT_MATRIX(port,7,5)=rprf(5);
            KIKS_ROBOT_MATRIX(port,7,6)=rprf(6);
        end;
    case 'D'
        if length(args)~=2
            response=['z,Protocol error'];
        else
            KIKS_ROBOT_MATRIX(port,1,5) = args(1); % left wheel speed in pulses
            KIKS_ROBOT_MATRIX(port,1,6) = args(2); % right wheel speed in pulses
            if KIKS_ROBOT_MATRIX(port,2,4)==1 & KIKS_ROBOT_MATRIX(port,2,7)==1
                KIKS_ROBOT_MATRIX(port,2,5)=0; % lE = 0 - don't reset these unless changing mode
                KIKS_ROBOT_MATRIX(port,2,8)=0; % rE = 0 
            end;
            KIKS_ROBOT_MATRIX(port,2,3)=0; % lT = 0
            KIKS_ROBOT_MATRIX(port,2,6)=0; % rT = 0
            KIKS_ROBOT_MATRIX(port,2,4)=0; % lM = 0
            KIKS_ROBOT_MATRIX(port,2,7)=0; % rM = 0
            KIKS_ROBOT_MATRIX(port,1,4) = 0;
            
            response=['d'];
        end;
    case 'E'
        response=[sprintf('e,%d,%d',KIKS_ROBOT_MATRIX(port,1,5),KIKS_ROBOT_MATRIX(port,1,6))];
    case 'G'
        if length(args)~=2
            response=['z,Protocol error'];
        else
            KIKS_ROBOT_MATRIX(port,1,7)=args(1);
            KIKS_ROBOT_MATRIX(port,1,8)=args(2);
        end;
        response=['g'];
    case 'H'
        response=[sprintf('h,%d,%d',round(KIKS_ROBOT_MATRIX(port,1,7)),round(KIKS_ROBOT_MATRIX(port,1,8)))];
    case  'J'
        if length(args)~=2
            response=['z,Protocol error'];
        else
            KIKS_ROBOT_MATRIX(port,5,1)=args(1);
            KIKS_ROBOT_MATRIX(port,5,2)=args(2);
            KIKS_ROBOT_MATRIX(port,5,3)=args(1);
            KIKS_ROBOT_MATRIX(port,5,4)=args(2);
            response=['j'];
        end;    
    case 'K'
        response=[sprintf('k,%d,%d,%d,%d,%d,%d',round(KIKS_ROBOT_MATRIX(port,2,3)),round(KIKS_ROBOT_MATRIX(port,2,4)),round(KIKS_ROBOT_MATRIX(port,2,5)),round(KIKS_ROBOT_MATRIX(port,2,6)),round(KIKS_ROBOT_MATRIX(port,2,7)),round(KIKS_ROBOT_MATRIX(port,2,8)))];
    case 'L'
        if length(args)~=2
            response=['z,Protocol error'];
        else
            
            kiks_setdiod(port,args(1),args(2));
            response=['l'];
        end;
    case 'N' % proximity sensors
        kiks_sim_prox(port);
        proxvector=KIKS_ROBOT_MATRIX(port,KIKS_PROX_POS,:);
        response=[sprintf('n,%d,%d,%d,%d,%d,%d,%d,%d',proxvector(1),proxvector(2),proxvector(3),proxvector(4),proxvector(5),proxvector(6),proxvector(7),proxvector(8))];
    case 'O' % light sensors
        kiks_sim_light(port);
        lightvector=KIKS_ROBOT_MATRIX(port,KIKS_LIGHT_POS,:);
        response=[sprintf('o,%d,%d,%d,%d,%d,%d,%d,%d',lightvector(1),lightvector(2),lightvector(3),lightvector(4),lightvector(5),lightvector(6),lightvector(7),lightvector(8))];
    case '' % do nothing
        response=[''];
    otherwise
        response=['Command not found'];
    end;
    serlen = length(CMD) + length(response);
    
    if ~isempty(KIKS_MOVIENAME) & abs(KIKS_GLOBALTIME_LASTSHOT-KIKS_GLOBALTIME)>1/15
        F=getframe(KIKS_ARENA_HDL);
        KIKS_MOVIE = addframe(KIKS_MOVIE,F);
        KIKS_GLOBALTIME_LASTSHOT=KIKS_GLOBALTIME;
    end;
    
    if ~isempty(KIKS_GLOBALTIME) & floor(KIKS_GLOBALTIME)~=floor(KIKS_GLOBALTIME_OLD)       
        KIKS_GLOBALTIME_OLD=KIKS_GLOBALTIME;
        h=findobj(KIKS_GUI_HDL,'tag','time');
        mins=floor(KIKS_GLOBALTIME/60);
        secs=floor(KIKS_GLOBALTIME-(mins*60));
        timestr=sprintf('%2.0f:%2.0f',mins,secs);
        [rows,cols]=size(timestr);
        for i=1:cols,
            if(timestr(i)==' ') timestr(i)='0'; end;
        end;   
        set(h,'string',timestr);
        h=findobj(KIKS_GUI_HDL,'tag','speedup');
        spdup=kiks_siminfo_speed;
        set(h,'string',sprintf('%.0f%% (%.0f%%)',spdup(1),spdup(2)));
    end;
    
    KIKS_LINKTIME = (serlen*11)/KIKS_ROBOT_MATRIX(port,4,1)+(((KIKS_KSEND_CONSTANT+rand*KIKS_KSEND_VARIATION-KIKS_KSEND_VARIATION/2)/KIKS_ROBOT_MATRIX(port,4,1))*compacc); % time for this command to pass over serial link
    KIKS_PAUSETIME=0;
    KIKS_OTHERTIME=clock;
    KIKS_SIM_STEP=0;   
    return;
else % redirect to ksend
    if (nargin<3 | timeout==0)
        response = eval('ksend(CMD,ref)','ksends(CMD,ref)');        
        % use static buffer if the dynamic buffer is not supported
    else
        response = eval('ksend(CMD,ref,timeout)','ksends(CMD,ref,timeout)');
    end;  
end;