function kiks_arena_edit(cancel)
global KIKS_ARENA_EDITING_MODE KIKS_WALL_RENDER KIKS_ARENA_EDITING_OBJECTNO KIKS_ARENA_EDITING_STATE KIKS_2D_GRID KIKS_2D_GRID_OLD KIKS_GUI_HDL KIKS_GUI_ENABLED KIKS_ARENA_EDITING KIKS_BALLARRAY KIKS_LIGHTARRAY KIKS_RBTARRAY KIKS_MMPERPIXEL KIKS_ARENA_MASK_ORIG KIKS_ARENA_COLORMASK_ORIG KIKS_MMPERPIXEL_OLD;

if isempty(KIKS_ARENA_EDITING)
    KIKS_ARENA_EDITING=1;
    KIKS_ARENA_EDITING_MODE=0;
    KIKS_ARENA_EDITING_STATE=0;
    KIKS_ARENA_EDITING_OBJECTNO=0;
    h=findobj(KIKS_GUI_HDL,'Type','uicontrol');
    KIKS_GUI_ENABLED=get(h,'Enable');
    set(h,'Enable','off');
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_edit');
    p=get(h,'Position');
    set(h,'String','done');
    set(h,'Enable','on');    
    h=findobj(KIKS_GUI_HDL,'tag','arena_new');
    set(h,'String','cancel');
    set(h,'Callback','kiks_arena_edit(1);');
    set(h,'Enable','on');
    set(findobj(KIKS_GUI_HDL,'tag','StaticText_arena'),'enable','on');
    set(findobj(KIKS_GUI_HDL,'tag','status'),'enable','on');
    h=findobj(KIKS_GUI_HDL,'tag','arena_edit_mode');
    set(h,'String','mode: draw');
    set(h,'visible','on');
    set(h,'Enable','on');
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_load');
    set(h,'visible','off');
    h=findobj(KIKS_GUI_HDL,'tag','arena_save');
    set(h,'visible','off');
    h=findobj(KIKS_GUI_HDL,'tag','arena_checkpoint');
    set(h,'visible','off');    
    h=findobj(KIKS_GUI_HDL,'tag','arena_reset');
    set(h,'visible','off');
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_color_slider');
    set(h,'visible','on');
    set(h,'enable','on');
    v=get(h,'Value'); set(h,'BackgroundColor',[v/255 v/255 v/255]);
    
    KIKS_MMPERPIXEL_OLD=KIKS_MMPERPIXEL;
    KIKS_2D_GRID_OLD=KIKS_2D_GRID;
    KIKS_2D_GRID=1;
    % delete robots
    while size(KIKS_RBTARRAY>0)
        kiks_delete_robot(KIKS_RBTARRAY(1));
    end;
    
    % delete lights
    while size(KIKS_LIGHTARRAY>0)
        kiks_delete_object(KIKS_LIGHTARRAY(1),1);
    end;
    
    % delete balls
    while size(KIKS_BALLARRAY>0)
        kiks_delete_object(KIKS_BALLARRAY(1),2+KIKS_BALLDATA(KIKS_BALLARRAY(1),5));
    end;
    
    KIKS_MMPERPIXEL=1;
    kiks_arena(KIKS_ARENA_MASK_ORIG,KIKS_ARENA_COLORMASK_ORIG,1);
    h=findobj(KIKS_GUI_HDL,'tag','arena_grid');
    set(h,'enable','off');
    h=findobj(KIKS_GUI_HDL,'tag','arena_redraw');
    set(h,'enable','off');
else
    KIKS_ARENA_EDITING=[];
    KIKS_ARENA_EDITING_STATE=0;
    KIKS_ARENA_EDITING_OBJECTNO=0;
    KIKS_MMPERPIXEL=KIKS_MMPERPIXEL_OLD;
    KIKS_2D_GRID=KIKS_2D_GRID_OLD;
    
    polys=sort(findobj(KIKS_GUI_HDL,'tag','WALL_POLYGON'));
    if nargin==0
        kiks_status('Rendering arena...');
        for i=1:length(polys)
            col=get(polys(i),'Edgecolor');
            x=get(polys(i),'xdata')-KIKS_WALL_RENDER;
            y=get(polys(i),'ydata')-KIKS_WALL_RENDER;
            x=[x; x(1)]; y=[y; y(1)];
            minx=min(x); maxx=max(x);
            miny=min(y); maxy=max(y);
            for j=miny:maxy
                xp=[minx:maxx];
                yp=[ones(1,maxx-minx+1)*j];
                in=inpolygon(xp,yp,x,y);
                KIKS_ARENA_MASK_ORIG(j,xp(in))=(col(1)>0);
                KIKS_ARENA_COLORMASK_ORIG(j,xp(in))=ceil(col(1)*255);
            end;
            kiks_status(sprintf('Rendering arena... %.0f%%\n',(i/length(polys))*100));
        end;
    end;
    delete(polys);
    
    h=findobj(KIKS_GUI_HDL,'type','uicontrol');
    for i=1:length(h)
        set(h(i),'Enable',char(KIKS_GUI_ENABLED(i)));
    end;
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_edit');
    set(h,'String','edit');
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_new');
    set(h,'String','new');
    set(h,'Callback','kiks_arena_new');
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_color_slider');
    set(h,'visible','off');
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_edit_mode');
    set(h,'visible','off');    
    
    h=findobj(KIKS_GUI_HDL,'tag','arena_load');
    set(h,'visible','on');
    h=findobj(KIKS_GUI_HDL,'tag','arena_save');
    set(h,'visible','on');
    h=findobj(KIKS_GUI_HDL,'tag','arena_checkpoint');
    set(h,'visible','on');    
    h=findobj(KIKS_GUI_HDL,'tag','arena_reset');
    set(h,'visible','on');
    
    kiks_arena(KIKS_ARENA_MASK_ORIG,KIKS_ARENA_COLORMASK_ORIG);
end;