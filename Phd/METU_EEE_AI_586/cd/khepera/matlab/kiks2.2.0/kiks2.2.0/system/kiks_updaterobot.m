% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_updaterobot(port,v_time)
global KIKS_2DVISUALIZE KIKS_lastupdate KIKS_updatefreq KIKS_updatefreqtime KIKS_MONITOR_WIN KIKS_MONITOR_ON KIKS_RBT_TIME;

if (v_time>=0.01) 
    kiks_moverobot(port,v_time); 
end;

if (KIKS_2DVISUALIZE>0) kiks_draw_robot(port); end;   

KIKS_lastupdate(port)=KIKS_RBT_TIME(abs(port));
updtime=KIKS_lastupdate(port)-KIKS_updatefreqtime(port);

if(updtime>=1)
    if(KIKS_MONITOR_ON(port)==1)
        h=findobj(KIKS_MONITOR_WIN(port),'Tag','time');
        mins=floor(KIKS_lastupdate(port)/60);
        secs=floor(KIKS_lastupdate(port)-(mins*60));
        timestr=sprintf('%2.0f:%2.0f',mins,secs);
        [rows,cols]=size(timestr);
        for i=1:cols,
            if(timestr(i)==' ') timestr(i)='0'; end;
        end;   
        set(h,'string',timestr);
    end;
else  
    KIKS_updatefreq(port)=KIKS_updatefreq(port)+1;
end;