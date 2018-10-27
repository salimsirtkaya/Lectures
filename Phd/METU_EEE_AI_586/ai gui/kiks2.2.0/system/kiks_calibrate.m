% -----------------------------------------------
%  (c) 2000 Theodor Storm (theodor@tstorm.se)
%  http://www.tstorm.se
% -----------------------------------------------
% kiks_calibrate(port,baud): Calibrate KiKS
%
% Measures how many flops/second this computer can handle and,
% optionally, calculates how much execution time each KSEND call to a 
% real robot requires. You need a robot connected to a serial port
% in order to perform this operation.
%
% If you have a robot connected to your computer,
% port is the # of the serial port a real robot is connected to.
% baud is the baud rate to run the calibration process at - choose the baud
% rate that you will usually run the real robot at for best results.
%
% If you do not have a robot connected to the computer,
% do not specify port and baud rate and only computer speed will be measured.
%
% NOTE: kiks_calibrate will restart KiKS.
function kiks_calibrate(port,baud,forceul)

global KIKS_GUI_HDL KIKS_COMPUTER_SPEED KIKS_VISUALIZE KIKS_KSEND_CONSTANT KIKS_MAX_SPEED KIKS_WALL_TIME KIKS_CALIBRATE_BAUD KIKS_KSEND_VARIATION;

getksend=1;
if nargin<3
    forceul=[];
end;
if nargin<2
    baud=9600;
end;
if nargin<1
    port=-1;
end;

if port == -1
    getksend=0;
end;

arena=zeros(100,100);
arena(50,50)=-360;
kiks_arena(arena);
kiks_gui_setstatlistbox(7);

pause(0.25);
if KIKS_VISUALIZE>0
    kiks_arena_window_close;
end;

pause(0.25);
kiks_status(sprintf('Calibrating KiKS, please wait. This will take a few moments.\n'),1);
KIKS_COMPUTER_SPEED=0;

if getksend==1
    KIKS_KSEND_CONSTANT=0;
    KIKS_KSEND_VARIATION=0;
    kiks_settimescale(KIKS_MAX_SPEED);
    maxksend=baud/64;
    KIKS_CALIBRATE_BAUD=baud;
    constarray=[];
    flops_total=0;
    flops_time=0;
    
    for i=1:10
        %   loops=0;
        ref=kiks_kopen([port,baud,0]);
        nrksend=0;
        while (nrksend<maxksend)
            kiks_ksend([sprintf('G,%d,%d',nrksend,nrksend),10],ref);
            nrksend=nrksend+1;
            kiks_ksend(['H',10],ref);
            nrksend=nrksend+1;  
            kiks_ksend(['D,0,0',10],ref);
            nrksend=nrksend+1;    
        end;
        realruntime=kiks_ktime(port);
        kiks_kclose(ref);
        realksend=nrksend;
        
        %  loops=0;
        ref=kiks_kopen([-1,baud,0]);
        flops_before=flops;
        t0=clock;
        nrksend=0;
        while (nrksend<maxksend)
            kiks_ksend([sprintf('G,%d,%d',nrksend,nrksend),10],ref);
            nrksend=nrksend+1;
            kiks_ksend(['H',10],ref);
            nrksend=nrksend+1;  
            kiks_ksend(['D,0,0',10],ref);
            nrksend=nrksend+1;     
        end;
        simruntime=kiks_ktime(-1);
        flops_total=flops_total+(flops-flops_before);
        flops_time=flops_time+etime(clock,t0);
        kiks_kclose(ref);
        simksend=nrksend;
        
        constarray(i)=((realruntime-simruntime)/nrksend)*baud;
        calibration_progress=sprintf('%d%%',i*10);
        kiks_status(sprintf('%s...',calibration_progress),1);
    end;
    
    constarray=sort(constarray);
    KIKS_KSEND_CONSTANT=mean(constarray(2:9)); % ignore lowest and highest values
    KIKS_KSEND_VARIATION=constarray(9)-constarray(2);
end;

%KIKS_COMPUTER_SPEED=flops_total/flops_time;
%KIKS_COMPUTER_SPEED=flops_time;
KIKS_COMPUTER_SPEED=kiks_speedtest(3);
kiks_status(sprintf('Computer speed index: %1.2f\n',KIKS_COMPUTER_SPEED),1);
kiks_save_settings;
kiks_status('Calibration finished.');
kiks_quit(1);