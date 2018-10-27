% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_mouse_moveobj(state);
global KIKS_COLOR_BACKGROUND KIKS_ARENA_EDITING_OBJECTNO KIKS_ARENA_EDITING_MODE KIKS_ARENA_EDITING_OUTLINE KIKS_ARENA_EDITING_STATE KIKS_ARENA_EDITING_CORNER KIKS_ARENA_EDITING KIKS_COLOR_ROBOT KIKS_MMPERPIXEL KIKS_ARENA_MASK KIKS_MOVLOCK KIKS_FID KIKS_MMPERPIXEL KIKS_2DVISUALIZE KIKS_ROBOT_MATRIX KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_BALLDATA KIKS_ROUNDOBJDATA KIKS_LIGHTDATA KIKS_GUI_HDL KIKS_SELECTED_OBJ KIKS_MONITOR_ON KIKS_MONITOR_WIN;
KIKS_MOVLOCK=KIKS_MOVLOCK+1;
if KIKS_MOVLOCK>1 KIKS_MOVLOCK=KIKS_MOVLOCK-1; return; end;

if nargin == 0 | strcmp(state,'on') % Set the WindowButtonDownFcn
    set(gcf,'WindowButtonDownFcn','kiks_mouse_moveobj down')
elseif strcmp(state,'down') % Execute the WindowButtonDownFcn
    if KIKS_ARENA_EDITING
        cp = get(gca,'CurrentPoint');
        pt = cp(1,[1 2]);
        pt=floor(pt)-KIKS_WALL_RENDER;
        pt=round(pt/10)*10;
        pt(find(pt<1))=1;
        sz=size(KIKS_ARENA_MASK);
        pt(1)=min(pt(1),sz(2)-KIKS_WALL_WIDTH*2);
        pt(2)=min(pt(2),sz(1)-KIKS_WALL_WIDTH*2);
        switch KIKS_ARENA_EDITING_STATE
            case 0 % placing first corner
                KIKS_ARENA_EDITING_STATE=1;
                KIKS_ARENA_EDITING_CORNER=pt;
                KIKS_ARENA_EDITING_OBJECTNO=KIKS_ARENA_EDITING_OBJECTNO+1;
                set(gcf,'WindowButtonMotionFcn','kiks_mouse_moveobj move','WindowButtonUpFcn','');
                KIKS_ARENA_EDITING_OUTLINE=patch('Erase','xor','Facecolor',[1 1 1],'EdgeColor',[1 1 1]);
            case 1
                if KIKS_ARENA_EDITING_MODE==0
                    col=get(findobj(KIKS_GUI_HDL,'tag','arena_color_slider'),'Value');
                    ptch=patch('Facecolor',[col/255 col/255 col/255],'EdgeColor',[col/255 col/255 col/255],'tag','WALL_POLYGON');
                else
                    ptch=patch('Facecolor',KIKS_COLOR_BACKGROUND,'EdgeColor',[0 0 0],'tag','WALL_POLYGON');
                end;
                xcoord = [KIKS_ARENA_EDITING_CORNER(1) pt(1) pt(1) KIKS_ARENA_EDITING_CORNER(1)];
                ycoord = [KIKS_ARENA_EDITING_CORNER(2) KIKS_ARENA_EDITING_CORNER(2) pt(2) pt(2)];
                delete(KIKS_ARENA_EDITING_OUTLINE);
                set(ptch,'xdata',xcoord+KIKS_WALL_RENDER,'ydata',ycoord+KIKS_WALL_RENDER);
                KIKS_ARENA_EDITING_STATE=0;
                set(gcf,'WindowButtonMotionFcn','','WindowButtonUpFcn','kiks_mouse_moveobj up');
                drawnow;
        end;
    else
        htype = get(gco,'Type');
        if strcmp(htype,'patch') | strcmp(htype,'text')
            tagline = get(gco,'tag');
            if tagline(1)=='@' % @ means that this patch is movable
                set(gcf,'WindowButtonMotionFcn','kiks_mouse_moveobj move', ...
                    'WindowButtonUpFcn','kiks_mouse_moveobj up');
                if tagline(2)=='r' | tagline(2)=='l' | tagline(2)=='b'
                    objtype=1;
                    num=sscanf(tagline,'@lightobj %f');
                    if isempty(num)
                        objtype=2;
                        num=sscanf(tagline,'@ballobj %f');
                    end;
                    if isempty(KIKS_SELECTED_OBJ) KIKS_SELECTED_OBJ=num;
                    else
                        h=findobj(KIKS_GUI_HDL,'tag',sprintf('@roundobj %d',KIKS_SELECTED_OBJ));
                        set(h,'Selected','off');
                        h=findobj(KIKS_GUI_HDL,'tag',sprintf('@lightobj %d',KIKS_SELECTED_OBJ));
                        set(h,'Selected','off');               
                        h=findobj(KIKS_GUI_HDL,'tag',sprintf('@ballobj %d',KIKS_SELECTED_OBJ));
                        set(h,'Selected','off');                              
                    end;
                    KIKS_SELECTED_OBJ=num;
                    set(gco,'Selected','on');
                    h=findobj(KIKS_GUI_HDL,'Tag','deleteobj');
                    set(h,'Callback',sprintf('kiks_delete_object(%d,%d)',num,objtype));
                    set(h,'Enable','on');
                end;
            end;
        elseif KIKS_2DVISUALIZE>0
            h=findobj(KIKS_GUI_HDL,'tag',sprintf('@roundobj %d',KIKS_SELECTED_OBJ));
            set(h,'Selected','off');
            h=findobj(KIKS_GUI_HDL,'tag',sprintf('@lightobj %d',KIKS_SELECTED_OBJ));
            set(h,'Selected','off');               
            h=findobj(KIKS_GUI_HDL,'tag',sprintf('@ballobj %d',KIKS_SELECTED_OBJ));
            set(h,'Selected','off');                              
            h=findobj(KIKS_GUI_HDL,'Tag','deleteobj');
            set(h,'Enable','off');
        end
    end;
elseif strcmp(state,'move') % Execute the WindowButtonMotionFcn
    if KIKS_ARENA_EDITING
        cp = get(gca,'CurrentPoint');
        pt = cp(1,[1 2]);
        pt=floor(pt)-KIKS_WALL_RENDER;
        pt(find(pt<1))=1;
        sz=size(KIKS_ARENA_MASK);
        pt(1)=min(pt(1),sz(2)-KIKS_WALL_WIDTH*2);
        pt(2)=min(pt(2),sz(1)-KIKS_WALL_WIDTH*2);
        pt=round(pt/10)*10;
        xcoord = [KIKS_ARENA_EDITING_CORNER(1) pt(1) pt(1) KIKS_ARENA_EDITING_CORNER(1)];
        ycoord = [KIKS_ARENA_EDITING_CORNER(2) KIKS_ARENA_EDITING_CORNER(2) pt(2) pt(2)];
        set(KIKS_ARENA_EDITING_OUTLINE,'xdata',xcoord+KIKS_WALL_RENDER,'ydata',ycoord+KIKS_WALL_RENDER);        
    else
        cp = get(gca,'CurrentPoint');
        pt = cp(1,[1 2]);
        pt=pt*KIKS_MMPERPIXEL;
        tagline = get(gco,'tag');
        if tagline(2)=='k' % (k)heppatch
            num=sscanf(tagline,'@kheppatch %f');
            %        kiks_arena_subrobot(num,floor(KIKS_ROBOT_MATRIX(num,1,1)),floor(KIKS_ROBOT_MATRIX(num,1,2)));
            kiks_arena_sub_mask(floor(KIKS_ROBOT_MATRIX(num,1,1)),floor(KIKS_ROBOT_MATRIX(num,1,2)),KIKS_COLOR_ROBOT,KIKS_ROBOT_MATRIX(num,2,2));
            oldX = KIKS_ROBOT_MATRIX(num,1,1);
            oldY = KIKS_ROBOT_MATRIX(num,1,2);
            KIKS_ROBOT_MATRIX(num,1,1) = pt(1)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            KIKS_ROBOT_MATRIX(num,1,2) = pt(2)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            coll=kiks_detect_collision(num);
            if coll(1)==1 & size(coll,1)>1
                KIKS_ROBOT_MATRIX(num,1,1)=coll(2);
                KIKS_ROBOT_MATRIX(num,1,2)=coll(3);
            end;
            
            if coll(1)>1
                targetX = KIKS_ROBOT_MATRIX(num,1,1);
                targetY = KIKS_ROBOT_MATRIX(num,1,2);
                KIKS_ROBOT_MATRIX(num,1,1) = oldX;
                KIKS_ROBOT_MATRIX(num,1,2) = oldY;
                KIKS_ROBOT_MATRIX(num,1,1)=oldX;
                KIKS_ROBOT_MATRIX(num,1,2)=oldY;       
                diffX=targetX-oldX;
                diffY=targetY-oldY;
                dist=sqrt(diffX*diffX+diffY*diffY);
                if dist>0
                    dX=diffX/dist;
                    dY=diffY/dist;
                    coll=kiks_detect_collision(num);
                    while(coll(1)<=1)
                        oldX=KIKS_ROBOT_MATRIX(num,1,1);
                        oldY=KIKS_ROBOT_MATRIX(num,1,2);
                        KIKS_ROBOT_MATRIX(num,1,1)=KIKS_ROBOT_MATRIX(num,1,1)+dX/2;
                        KIKS_ROBOT_MATRIX(num,1,2)=KIKS_ROBOT_MATRIX(num,1,2)+dY/2;
                        coll=kiks_detect_collision(num);        
                    end;
                end;
                KIKS_ROBOT_MATRIX(num,1,1)=oldX;
                KIKS_ROBOT_MATRIX(num,1,2)=oldY;
                % try moving along X or Y axis
                KIKS_ROBOT_MATRIX(num,1,1)=KIKS_ROBOT_MATRIX(num,1,1)+diffX;
                coll=kiks_detect_collision(num);
                if coll(1)>1
                    KIKS_ROBOT_MATRIX(num,1,1)=oldX;
                    KIKS_ROBOT_MATRIX(num,1,2)=KIKS_ROBOT_MATRIX(num,1,2)+diffY;
                    coll=kiks_detect_collision(num);
                    if coll(1)>1
                        KIKS_ROBOT_MATRIX(num,1,2)=oldY;
                    end;
                end;
            end;
            %        kiks_arena_addrobot(num,floor(KIKS_ROBOT_MATRIX(num,1,1)),floor(KIKS_ROBOT_MATRIX(num,1,2)));  
            kiks_arena_add_mask(floor(KIKS_ROBOT_MATRIX(num,1,1)),floor(KIKS_ROBOT_MATRIX(num,1,2)),KIKS_COLOR_ROBOT,KIKS_ROBOT_MATRIX(num,2,2));
            kiks_draw_robot(num);
        elseif tagline(2)=='r' % (r)ound object
            num=sscanf(tagline,'@roundobj %f');
            kiks_arena_subroundobj(num,floor(KIKS_ROUNDOBJDATA(num,1)),floor(KIKS_ROUNDOBJDATA(num,2)));
            newxp = pt(1)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            newyp = pt(2)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            [mapy,mapx]=size(KIKS_ARENA_MASK);
            if (newxp<KIKS_WALL_WIDTH) newxp=KIKS_ROUNDOBJDATA(num,1); end;
            if (newyp<KIKS_WALL_WIDTH) newyp=KIKS_ROUNDOBJDATA(num,2); end;
            if (newxp>(mapx*KIKS_MMPERPIXEL)-KIKS_WALL_WIDTH) newxp=KIKS_ROUNDOBJDATA(num,1); end;
            if (newyp>(mapy*KIKS_MMPERPIXEL)-KIKS_WALL_WIDTH) newyp=KIKS_ROUNDOBJDATA(num,2); end;
            KIKS_ROUNDOBJDATA(num,1)=newxp;
            KIKS_ROUNDOBJDATA(num,2)=newyp;    
            kiks_arena_addroundobj(num,floor(KIKS_ROUNDOBJDATA(num,1)),floor(KIKS_ROUNDOBJDATA(num,2)));
            kiks_draw_roundobj(num);
        elseif tagline(2)=='b' % (b)all
            num=sscanf(tagline,'@ballobj %f');
            kiks_arena_subball(num,floor(KIKS_BALLDATA(num,1)),floor(KIKS_BALLDATA(num,2)));            
            newxp = pt(1)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            newyp = pt(2)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            [mapy,mapx]=size(KIKS_ARENA_MASK);
            if (newxp<KIKS_WALL_WIDTH) newxp=KIKS_BALLDATA(num,1); end;
            if (newyp<KIKS_WALL_WIDTH) newyp=KIKS_BALLDATA(num,2); end;
            if (newxp>(mapx*KIKS_MMPERPIXEL)-KIKS_WALL_WIDTH) newxp=KIKS_BALLDATA(num,1); end;
            if (newyp>(mapy*KIKS_MMPERPIXEL)-KIKS_WALL_WIDTH) newyp=KIKS_BALLDATA(num,2); end;
            KIKS_BALLDATA(num,1)=newxp;
            KIKS_BALLDATA(num,2)=newyp;    
            kiks_arena_addball(num,floor(KIKS_BALLDATA(num,1)),floor(KIKS_BALLDATA(num,2)));
            kiks_draw_ball(num);
        elseif tagline(2)=='l' % (l)ight source
            num=sscanf(tagline,'@lightobj %f');
            newxp = pt(1)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            newyp = pt(2)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER;
            [mapy,mapx]=size(KIKS_ARENA_MASK);
            if (newxp<KIKS_WALL_WIDTH) newxp=KIKS_LIGHTDATA(num,1); end;
            if (newyp<KIKS_WALL_WIDTH) newyp=KIKS_LIGHTDATA(num,2); end;
            if (newxp>(mapx*KIKS_MMPERPIXEL)-KIKS_WALL_WIDTH) newxp=KIKS_LIGHTDATA(num,1); end;
            if (newyp>(mapy*KIKS_MMPERPIXEL)-KIKS_WALL_WIDTH) newyp=KIKS_LIGHTDATA(num,2); end;
            KIKS_LIGHTDATA(num,1)=newxp;
            KIKS_LIGHTDATA(num,2)=newyp;    
            %     kiks_arena_addroundobj(num,floor(KIKS_ROUNDOBJDATA(num,1)),floor(KIKS_ROUNDOBJDATA(num,2)));
            kiks_draw_light(num);     
        elseif tagline(2)=='h' % robot (h)andle
            num=sscanf(tagline,'@handle %f');
            kx=KIKS_ROBOT_MATRIX(num,1,1);
            ky=KIKS_ROBOT_MATRIX(num,1,2);
            mx=pt(1)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER-kx;
            my=pt(2)+KIKS_WALL_WIDTH-KIKS_WALL_RENDER-ky;
            d=sqrt(mx*mx+my*my);
            ang=asin(my/d);
            if mx>0
                deg=round((-ang/(pi/180))/5)*5;
                rad=deg*(pi/180);
                KIKS_ROBOT_MATRIX(num,1,3)=rad;        
            else
                deg=round(((pi+ang)/(pi/180))/5)*5;
                rad=deg*(pi/180);
                KIKS_ROBOT_MATRIX(num,1,3)=rad;
            end;
            if KIKS_MONITOR_ON(num)==1
                h=findobj(KIKS_MONITOR_WIN(num),'tag','angle');
                set(h,'string',sprintf('%d°',mod(round(KIKS_ROBOT_MATRIX(num,1,3)/(pi/180)),360)));
            end;
            kiks_draw_robot(num);
        end;
    end;
elseif strcmp(state,'up') % Execute the WindowButtonUpFcn
    set(gcf,'WindowButtonMotionFcn','')
elseif strcmp(state,'off') % Unset the WindowButton...Fcns
    set(gcf,'WindowButtonDownFcn','','WindowButtonUpFcn','')
end

KIKS_MOVLOCK=KIKS_MOVLOCK-1;