% -----------------------------------------------
%  (c) 2000 Theodor Storm (theodor@tstorm.se)
%  http://www.tstorm.se
% -----------------------------------------------
function ret=kiks_kopen(args)
global KIKS_MOVIE_QUALITY KIKS_MOVIE_COMPRESSION KIKS_RBTARRAY KIKS_FID KIKS_MOVLOCK KIKS_GLOBALTIME_LASTSHOT KIKS_MOVIENAME KIKS_MOVIE KIKS_RBT_TIME_MOM KIKS_RBT_RTIME_MOM KIKS_RBT_RTIME KIKS_AVIMOVIE KIKS_DIST_FWD KIKS_DIST_BWD KIKS_DIST_STR KIKS_DIST_STR_COORD KIKS_FID KIKS_SIM_LINVIS_2DMODE KIKS_TRACE_MAX KIKS_BALLARRAY KIKS_GLOBALTIME KIKS_GLOBALTIME_OLD KIKS_SIM_LINVIS_LL KIKS_SIM_LINVIS_LINT KIKS_SIM_LINVIS_LMIN KIKS_SIM_LINVIS_LMAX KIKS_SIM_LINVIS_LU KIKS_SIM_LINVIS_IMG KIKS_SESSIONACTIVE KIKS_ROBOT_MATRIX KIKS_PORT KIKS_PHYS_PORT KIKS_RBT_TIME KIKS_lastupdate KIKS_trace KIKS_updatefreq KIKS_updatefreqtime KIKS_tracestep KIKS_sensdelay KIKS_ACC_TIME KIKS_OTHERTIME KIKS_PAUSETIME KIKS_KTIME_VEC KIKS_GUI_HDL;
ret=[];
if (KIKS_FID>=0)
    KIKS_MOVLOCK=KIKS_MOVLOCK+1;
end;
if(args(1)<0)
    id=abs(args(1));
    if (id<-1)
        error('KiKS no longer supports multiple Kheperas in a single session. Use several instances of Matlab and KiKSnet instead.');
        return;
    end;
    status=0;
    try 
        status=KIKS_PORT(id);
    end;
    if(status~=0)
        error('Simulated serial port was already in use. Use kiks_kclose([]) to force the port to close.');
        return;
    end;
    
    baud=args(2);
    ret=0;
    KIKS_DIST_FWD=0;
    KIKS_DIST_BWD=0;
    KIKS_DIST_STR=0;
    KIKS_DIST_STR_COORD=[];
    if isempty(KIKS_SESSIONACTIVE) 
        kiks;
        pause(0.2);
    end;
    if isempty(KIKS_RBTARRAY)
        kiks_spawn_robot;
    end;
    openports=max(KIKS_PORT);
    if ~isempty(KIKS_MOVIENAME) 
        kiks_status(sprintf('Recording movie %s\n',KIKS_MOVIENAME));
        KIKS_MOVIE = avifile(KIKS_MOVIENAME,'compression',KIKS_MOVIE_COMPRESSION,'quality',KIKS_MOVIE_QUALITY);
        KIKS_GLOBALTIME_LASTSHOT = 0;
    end;
    %   KIKS_AVIMOVIE = avifile('kiks.avi')
    if openports==0        
        h=findobj(KIKS_GUI_HDL,'tag','haltsim');
        set(h,'Enable','on');
        if (KIKS_FID==-1)
            h=findobj(KIKS_GUI_HDL,'tag','pausesim');
            set(h,'Enable','on');
        end;
        h=findobj(KIKS_GUI_HDL,'tag','kiksnet_server_btn');
        set(h,'Enable','off'); 
        h=findobj(KIKS_GUI_HDL,'Tag','kiksnet_btn');
        set(h,'Enable','off'); 
        h=findobj(KIKS_GUI_HDL,'tag','simulate_popup');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','loadarena');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','savearena');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','addobj');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','deleteobj');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','addkhep');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','deletekhep');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','loadarena');
        set(h,'Enable','off');
        if isempty(KIKS_GLOBALTIME) KIKS_GLOBALTIME=0; KIKS_GLOBALTIME_OLD=-1; end;
    end;
    
    %   if(status==0)
    
    KIKS_ACC_TIME(id) = 0;
    %   KIKS_PAUSETIME(id) = 0;
    KIKS_OTHERTIME = clock;
    KIKS_RBT_TIME(id)=0;
    KIKS_RBT_RTIME(id,:)=clock;
    KIKS_RBT_TIME_MOM(id)=0;
    KIKS_RBT_RTIME_MOM(id,:)=clock;
    KIKS_PORT(id) = 1;
    KIKS_lastupdate(id)=0;
    KIKS_trackupdate(id)=0;
    KIKS_updatefreq(id)=0; 
    KIKS_updatefreqtime(id)=0;
    KIKS_tracestep(id)=0;
    KIKS_sensdelay(id)=0;
    KIKS_ROBOT_MATRIX(id,4,1)=baud;
    KIKS_SIM_LINVIS_LU(id)=-10;
    if KIKS_SIM_LINVIS_2DMODE
        KIKS_SIM_LINVIS_IMG(id,KIKS_SIM_LINVIS_2DMODE,KIKS_SIM_LINVIS_2DMODE)=0;
    else
        KIKS_SIM_LINVIS_IMG(id,:)=zeros(1,64);
    end;
    
    KIKS_SIM_LINVIS_LMIN(id)=64;
    KIKS_SIM_LINVIS_LMAX(id)=1;
    KIKS_SIM_LINVIS_LINT(id)=64;
    KIKS_SIM_LINVIS_LL(id)=0;
    KIKS_trace(id,KIKS_TRACE_MAX,:)=[0 0];
    ret = double([-id, -id, -id, -id]);
    kiks_ksend(['B' 13],ret);
else % redirect to kopen
    % Test here if port hasn't been closed to get rid of annoying problems
    try
        if ~isempty(KIKS_PHYS_PORT(args(1)+1,:))
            try
                kclose(KIKS_PHYS_PORT(args(1)+1,:));
            end;         
            kiks_status('Warning: Serial port was already in use.');
        end;
    end;   
    ret=kopen(args);
    KIKS_KTIME_VEC(args(1)+1,:)=clock;
    KIKS_PHYS_PORT(args(1)+1,:)=ret;
end;
