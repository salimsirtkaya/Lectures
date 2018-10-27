% kiks_kclose (ref)
% quits KiKS 
%
% -----------------------------------------------
%  (c) 2000 Theodor Storm (theodor@tstorm.se)
%  http://www.tstorm.se
% -----------------------------------------------

function kiks_kclose(ref)
global KIKS_FID KIKS_MOVLOCK KIKS_MOVIE KIKS_MOVIENAME KIKS_MMPERPIXEL KIKS_ARENA_HDL KIKS_FID KIKS_BALLARRAY KIKS_PORT KIKS_WALL_CLOCK KIKS_GLOBALTIME KIKS_RBTARRAY KIKS_GUI_HDL KIKS_SESSIONACTIVE KIKS_PORT KIKS_PHYS_PORT KIKS_trace KIKS_tracestep KIKS_2DVISUALIZE KIKS_KTIME_VEC KIKS_RBT_TIME;
if (KIKS_FID>=0)
    KIKS_MOVLOCK=KIKS_MOVLOCK-1;
end;

col(1)='w'; col(2)='y'; col(3)='c';
if isempty(ref) | (ref(1)==ref(2) & ref(2)==ref(3) & ref(3)==ref(4) & ref(1)<0)
    try
        if KIKS_PORT(1)~=1
            return;
        end;
    catch
        return;
    end;
    
    if isempty(KIKS_SESSIONACTIVE) fprintf('[KiKS Error] No KiKS session found.\n'); return; end;
    id=1;
    KIKS_PORT(id) = 0;
    KIKS_RBT_TIME(id)=-1;
    
    if (KIKS_2DVISUALIZE>0)
        [x,cols,y]=size(KIKS_trace);
        %      h=findobj('Name','KiKS arena');
        %      figure(h);
        %      hold on;
        axes(KIKS_ARENA_HDL);
        try
            plot(KIKS_trace(id,1:ceil(KIKS_tracestep(id)),1)/KIKS_MMPERPIXEL,KIKS_trace(id,1:ceil(KIKS_tracestep(id)),2)/KIKS_MMPERPIXEL,sprintf('%s.-',col(mod(id,4)+1)));  
            a=findobj('Tag','deleteme'); % clean up leftovers
            delete(a);
        end;
    end;
    
    openports=max(KIKS_PORT);
    if (openports==0)
        %KIKS_AVIMOVIE = close(KIKS_AVIMOVIE);
        if ~isempty(KIKS_MOVIENAME)
            F=getframe(KIKS_ARENA_HDL);
            KIKS_MOVIE = addframe(KIKS_MOVIE,F);          
            KIKS_MOVIE = close(KIKS_MOVIE);
            KIKS_MOVIENAME = [];
        end;
        KIKS_GLOBALTIME=[];
        KIKS_WALL_CLOCK=[];
        h=findobj(KIKS_GUI_HDL,'tag','haltsim');
        set(h,'Enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','pausesim');
        set(h,'Enable','off');      
        if (KIKS_FID==-1)
            % safe to manipulate project space
            h=findobj(KIKS_GUI_HDL,'tag','simulate_popup');
            set(h,'Enable','on');
            h=findobj(KIKS_GUI_HDL,'tag','addobj');
            set(h,'Enable','on');
            h=findobj(KIKS_GUI_HDL,'tag','deleteobj');
            set(h,'Enable','on');
            h=findobj(KIKS_GUI_HDL,'tag','kiksnet_server_btn');
            set(h,'Enable','on'); 
        end;
        h=findobj(KIKS_GUI_HDL,'tag','stepsim');
        set(h,'enable','off');
        h=findobj(KIKS_GUI_HDL,'tag','kiksnet_btn');
        set(h,'Enable','on');      
    end;
    
else % Redirect to kclose()
    kclose(ref);
    [ports,tmp]=size(KIKS_PHYS_PORT);
    for i=1:ports
        if KIKS_PHYS_PORT(i,:)==ref
            KIKS_KTIME_VEC(i,:)=[];
            KIKS_PHYS_PORT(i,:)=[];
        end;
    end;
end;
