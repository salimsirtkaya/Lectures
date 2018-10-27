% function res = kiks_siminfo_setobject(row,x,y,spd,ang)
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function res=kiks_siminfo_setobject(row,x,y,spd,ang)
global KIKS_2DVISUALIZE KIKS_OBJECT_BALL_RADIUS KIKS_OBJECT_BALL_SMALLRATIO KIKS_ARENA_MASK KIKS_OBJECT_SMALLBALL_MASK KIKS_OBJECT_BALL_MASK KIKS_MMPERPIXEL KIKS_WALL_RENDER KIKS_WALL_WIDTH KIKS_LIGHTARRAY KIKS_LIGHTDATA KIKS_BALLARRAY KIKS_BALLDATA

[lrows,lcols]=size(KIKS_LIGHTDATA);
[brows,bcols]=size(KIKS_BALLDATA);

res = 1;

try
    if (row<=lrows) % we're manipulating a light source
        id=row;
        if ~isempty(x), KIKS_LIGHTDATA(id,1)=x+KIKS_WALL_WIDTH; end;
        if ~isempty(y), KIKS_LIGHTDATA(id,2)=y+KIKS_WALL_WIDTH; end;
        if (KIKS_2DVISUALIZE>0)
            kiks_draw_light(id);
        end;
    else % we're manipulating a ball or cylinder
        id=row-lrows; 
        oldx = KIKS_BALLDATA(id,1);
        nxp = oldx;
        oldy = KIKS_BALLDATA(id,2);
        nyp = oldy;
        cylinder=KIKS_BALLDATA(id,5);
        theRadius=KIKS_OBJECT_BALL_RADIUS;
        if cylinder theRadius=theRadius*KIKS_OBJECT_BALL_SMALLRATIO; end;        
        if ~isempty(x), nxp=x+KIKS_WALL_WIDTH; end;
        if ~isempty(y), nyp=y+KIKS_WALL_WIDTH; end;
        
        % detect collision
        minx = floor(nxp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % xpos - robot radius
        miny = floor(nyp/KIKS_MMPERPIXEL)-floor(theRadius/KIKS_MMPERPIXEL); % ypos - robot radius
        maxx = floor(nxp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
        maxy = floor(nyp/KIKS_MMPERPIXEL)+floor(theRadius/KIKS_MMPERPIXEL);
        
        if cylinder
            map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_SMALLBALL_MASK;
        else
            map = KIKS_ARENA_MASK(miny:maxy, minx:maxx)+KIKS_OBJECT_BALL_MASK;
        end;
        coll = max(max(map));
        
        if coll==1
            kiks_arena_subball(id,floor(oldx),floor(oldy));
            KIKS_BALLDATA(id,1) = nxp;
            KIKS_BALLDATA(id,2) = nyp;
            kiks_arena_addball(id,floor(KIKS_BALLDATA(id,1)),floor(KIKS_BALLDATA(id,2)));
            if (KIKS_2DVISUALIZE>0)
                kiks_draw_ball(id);
            end;
        else
            res = 0;
        end;
        
        if ~isempty(spd), KIKS_BALLDATA(id,3)=spd; end; % speed (in mm/seconds)
        if ~isempty(ang), KIKS_BALLDATA(id,4)=ang; end; % angle (in radians)
    end;
catch
    res = 0;
end;