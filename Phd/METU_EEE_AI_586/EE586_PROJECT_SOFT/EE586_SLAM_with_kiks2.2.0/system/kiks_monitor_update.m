% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_monitor_update(id)
global KIKS_MONITOR_UPD KIKS_DIST_FWD KIKS_DIST_BWD KIKS_DIST_STR KIKS_SIM_LINVIS_2DMODE KIKS_GUI_HDL KIKS_GLOBALTIME KIKS_SIM_LINVIS_IMG KIKS_LIGHT_POS KIKS_PROX_POS KIKS_ROBOT_MATRIX KIKS_MONITOR_ON KIKS_MONITOR_WIN

if (KIKS_MONITOR_ON(id)==1)
    if isempty(KIKS_MONITOR_UPD) KIKS_MONITOR_UPD=clock; end;
    if etime(clock,KIKS_MONITOR_UPD)<0.1 return; end;
    KIKS_MONITOR_UPD=clock;
    h=findobj(KIKS_MONITOR_WIN(id),'tag','l');
    set(h,'string',sprintf('%d',round(KIKS_ROBOT_MATRIX(id,1,5))));
    h=findobj(KIKS_MONITOR_WIN(id),'tag','r');
    set(h,'string',sprintf('%d',round(KIKS_ROBOT_MATRIX(id,1,6))));
    h=findobj(KIKS_MONITOR_WIN(id),'tag','angle');
    set(h,'string',sprintf('%d°',mod(round(KIKS_ROBOT_MATRIX(id,1,3)/(pi/180)),360)));
    h=findobj(KIKS_MONITOR_WIN(id),'tag','dist_fwd');
    set(h,'string',sprintf('%3.1f cm',KIKS_DIST_FWD/10));
    h=findobj(KIKS_MONITOR_WIN(id),'tag','dist_bwd');
    set(h,'string',sprintf('%3.1f cm',KIKS_DIST_BWD/10));
    h=findobj(KIKS_MONITOR_WIN(id),'tag','dist_straight');
    set(h,'string',sprintf('%3.1f cm',KIKS_DIST_STR/10));
    h=findobj(KIKS_MONITOR_WIN(id),'tag','dist_total');
    set(h,'string',sprintf('%3.1f cm',(KIKS_DIST_FWD+KIKS_DIST_BWD)/10));
    
    for sens=1:8
        h=findobj(KIKS_MONITOR_WIN(id),'tag',sprintf('L%d',sens));
        set(h,'string',sprintf('%d',KIKS_ROBOT_MATRIX(id,KIKS_LIGHT_POS,sens)));
        h=findobj(KIKS_MONITOR_WIN(id),'tag',sprintf('%d',sens));
        set(h,'string',sprintf('%d',KIKS_ROBOT_MATRIX(id,KIKS_PROX_POS,sens)));
    end;
    
    h=findobj(KIKS_MONITOR_WIN(id),'tag','Axes2Image1');
    if KIKS_SIM_LINVIS_2DMODE
        img(:,:)=KIKS_SIM_LINVIS_IMG(id,:,:);
        set(h,'CData',img);
    else
        set(h,'CData',KIKS_SIM_LINVIS_IMG(id,:));
    end;
end;

