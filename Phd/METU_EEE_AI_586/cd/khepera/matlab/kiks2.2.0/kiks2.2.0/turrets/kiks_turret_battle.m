% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% The incredible nuclear powered Battle Turret
%
% Supported commands:
% 
%    B: returns version.
%    F: fires cannon and returns [id,distance] of target hit.
%    S: returns [X,Y,angle,distance_to_target,energy_percent,energy_points,times_hit] sensor values.
function response=kiks_turret_battle(tcommand,targs)
global KIKS_FIRE_HDL KIKS_2DVISUALIZE KIKS_WALL_RENDER KIKS_WALL_WIDTH KIKS_MMPERPIXEL KIKS_ARENA_COLORMASK KIKS_FID KIKS_ROBOT_MATRIX KIKS_WALL_WIDTH KIKS_KIKSNET_REPLY;

if nargin<2
    % return the turret id
    response=99;
    return;
end;

switch tcommand
    case 'B'
        response=[sprintf('t,99,b,1,0')];    
    case 'F' % fire cannon - this is handled by server
        target=-1;
        distance=-1;
        if ~isempty(KIKS_KIKSNET_REPLY)
            vec=sscanf(KIKS_KIKSNET_REPLY,'%d');
            target=vec(1);
            distance=vec(2);
            if distance>0 & KIKS_2DVISUALIZE>0
                kx=KIKS_ROBOT_MATRIX(1,1,1);
                ky=KIKS_ROBOT_MATRIX(1,1,2);
                ang=KIKS_ROBOT_MATRIX(1,1,3);
                shot_xcoord = [  0  4  3  8  5 distance distance  5   8   3   4  0]/KIKS_MMPERPIXEL;
                shot_ycoord = [  3 11  4  9  2        1       -1 -2  -9  -4 -11 -3]/KIKS_MMPERPIXEL;
                shot_xcoord=shot_xcoord+KIKS_ROBOT_MATRIX(1,2,2)/KIKS_MMPERPIXEL;
                KIKS_WALL_WIDTH_SCALED=KIKS_WALL_WIDTH/KIKS_MMPERPIXEL;
                KIKS_WALL_RENDER_SCALED=KIKS_WALL_RENDER/KIKS_MMPERPIXEL;
                xdata=(shot_xcoord*cos(-ang)-shot_ycoord*sin(-ang))+floor(kx/KIKS_MMPERPIXEL)-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED);
                ydata=(shot_xcoord*sin(-ang)+shot_ycoord*cos(-ang))+floor(ky/KIKS_MMPERPIXEL)-floor(KIKS_WALL_WIDTH_SCALED)+floor(KIKS_WALL_RENDER_SCALED);
                set(KIKS_FIRE_HDL(1),'Visible','on','xdata',xdata,'ydata',ydata);
                drawnow;
            end;
        else
            if KIKS_FID~=-1
                disp('<KiKS warning> KiKSnet server did not reply to FIRE command!');
            end;
        end;
        response=[sprintf('t,99,f,%d,%d',target,distance)];
    case 'S' % Return sensor values:
        %      x,y position of robot (in mm, from top left corner)
        %      angle robot is facing
        %      distance (in mm) to whatever the turret is aiming at
        %      energy level (in percent)
        %      energy level (in points)
        distance = -1; % distance to target (from edge of Khepera)
        [ys,xs]=size(KIKS_ARENA_COLORMASK);
        start_dist = ceil(KIKS_ROBOT_MATRIX(1,2,2)/KIKS_MMPERPIXEL)+1;
        end_dist = max(ys,xs);
        coord_vector=(start_dist:end_dist);
        ray_xvals = round(coord_vector*cos(KIKS_ROBOT_MATRIX(1,1,3))+(KIKS_ROBOT_MATRIX(1,1,1)/KIKS_MMPERPIXEL));
        ray_yvals = round(-coord_vector*sin(KIKS_ROBOT_MATRIX(1,1,3))+(KIKS_ROBOT_MATRIX(1,1,2)/KIKS_MMPERPIXEL));
        
        idx=((ray_xvals-1)*ys+ray_yvals); % calculate index values for these points
        idx(find(idx>ys*xs))=ys*xs;
        idx(find(idx<1))=1;
        
        distance=min(find(KIKS_ARENA_COLORMASK(idx))-1);
        
        energy_points=-1;
        energy_percent=-1;
        hits=-1;
        if ~isempty(KIKS_KIKSNET_REPLY)
            envals=sscanf(KIKS_KIKSNET_REPLY,'%d');
            energy_percent=envals(1);
            energy_points=envals(2);
            hits=envals(3);
        else
            if KIKS_FID~=-1
                disp('<KiKS warning> KiKSnet server did not reply to SENSORS command!');
            end;
        end;    
        
        x=floor(KIKS_ROBOT_MATRIX(1,1,1)-KIKS_WALL_WIDTH);
        y=floor(KIKS_ROBOT_MATRIX(1,1,2)-KIKS_WALL_WIDTH);
        ang=mod(round(KIKS_ROBOT_MATRIX(1,1,3)/(pi/180)),360);
        
        response=[sprintf('t,99,s,%d,%d,%d,%d,%d,%d,%d',x,y,ang,round(distance*KIKS_MMPERPIXEL),energy_percent,energy_points,hits)];
    otherwise
        response=['z,Protocol error'];              
end;
KIKS_KIKSNET_REPLY='';
