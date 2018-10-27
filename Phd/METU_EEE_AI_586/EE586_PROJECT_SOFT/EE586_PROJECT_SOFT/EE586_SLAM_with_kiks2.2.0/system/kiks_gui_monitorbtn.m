% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_monitorbtn
global KIKS_SIM_LINVIS_2DMODE KIKS_MONITOR_WIN KIKS_MONITOR_ON KIKS_ROBOT_MATRIX;

id = 1;

if(KIKS_MONITOR_ON(id)==1) 	% turn off monitor
    KIKS_MONITOR_ON(id)=0;
    delete(KIKS_MONITOR_WIN(id));
else								% turn on monitor	
    h=findobj('Name','KiKS');
    kikspos=get(h,'Position');
    
    mainpos=kikspos;
    hp=6;
    vp=0;
    
    scrnsz=get(0,'screensize');   
    KIKS_MONITOR_WIN(id)=kiks_gui_monitor;
    set(KIKS_MONITOR_WIN(id),'Name',sprintf('Port -%d',id));
    monpos=get(KIKS_MONITOR_WIN(id),'Position');
    nr=0;
    [tmp,sz]=size(KIKS_MONITOR_ON);
    for i=1:sz
        if KIKS_MONITOR_ON(i)==1
            nr=nr+1;
        end;
    end;
    
    %monpos(1)=mainpos(1)+nr*(monpos(3)+6);
    %monpos(2)=mainpos(2)+mainpos(4)+25;
    %monpos(1)=mainpos(1)+mainpos(3)+8;
    monpos(1)=mainpos(1)+147+5;
    monpos(2)=mainpos(2);
    if KIKS_SIM_LINVIS_2DMODE
        monpos(4)=monpos(4)+128;
        h=findobj(KIKS_MONITOR_WIN(id),'tag','Axes2');
        ap=get(h,'position');
        ap(4)=128;
        set(h,'position',ap);
        set(h,'ylim',[1 KIKS_SIM_LINVIS_2DMODE]);
        set(h,'xlim',[1 KIKS_SIM_LINVIS_2DMODE]);
        h=findobj(KIKS_MONITOR_WIN(id),'tag','Axes2Image1');
        set(h,'Ydata',[1 KIKS_SIM_LINVIS_2DMODE]);
        set(h,'Xdata',[1 KIKS_SIM_LINVIS_2DMODE]);
        set(h,'CData',zeros(KIKS_SIM_LINVIS_2DMODE,KIKS_SIM_LINVIS_2DMODE));
    end;
    if monpos(2)+monpos(4)>scrnsz(4)
        monpos(2)=mainpos(2)-monpos(4)-25;
    end;
    
    KIKS_MONITOR_ON(id)=1;
    set(KIKS_MONITOR_WIN(id),'Position',monpos);
    h=findobj(KIKS_MONITOR_WIN(id),'tag','angle');
    set(h,'string',sprintf('%d°',mod(round(KIKS_ROBOT_MATRIX(id,1,3)/(pi/180)),360)));
    kiks_monitor_update(1);
end;