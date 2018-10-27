% kiks_arena(arena)
%
% Reinitializes the arena; works as kiks(arena) but does
% not restart the simulator.
%
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function kiks_arena(arena,colormask,nokhep)
global KIKS_ARENA_WALLS KIKS_ARENA_DEFAULT_COLOR KIKS_TOOLBOX_IMAGES KIKS_ARENA_CONTOUR KIKS_BALLDATA KIKS_FID KIKS_ARENA_MASK_ORIG KIKS_ARENA_COLORMASK_ORIG KIKS_MMPERPIXEL KIKS_SIM_LINVIS_2DMODE KIKS_tracestep KIKS_BALL_TRACE_IX KIKS_2DVISUALIZE KIKS_ARENA_MX KIKS_ARENA_MASK KIKS_ARENA_COLORMASK KIKS_ARENA_HEIGHT KIKS_SESSIONACTIVE KIKS_WALL_WIDTH KIKS_RBTARRAY KIKS_BALLARRAY KIKS_ROUNDOBJARRAY KIKS_LIGHTARRAY KIKS_WALL_RENDER;

KIKS_ARENA_WALLS=[];

oldvis=KIKS_2DVISUALIZE;
if (KIKS_2DVISUALIZE>0)
    kiks_arena_window_close;
end;

if nargin<3
    nokhep=[];
end;

if nargin<2
    colormask=[];
end;

if (ischar(arena))
    arenaloaded=[];
    if ~isempty(findstr(lower(arena),'.tif'))
        kiks_status('Loading arena from TIF file...');
        [arena,colormask]=kiks_tif2arena(arena);
%        [arena,colormask]=kiks_kad2arena(KIKS_ARENA_WALLS);
    elseif ~isempty(findstr(lower(arena),'.kad'))
        kiks_status('Loading arena from KiKS Arena Data file...');
        load(arena,'-MAT');
        KIKS_ARENA_WALLS=walls;
        [arena,colormask]=kiks_kad2arena(KIKS_ARENA_WALLS);
    end;
end;

if isempty(KIKS_SESSIONACTIVE)
    kiks(arena,colormask);
    return;
end;

%xs = 695; ys = 498; % size of UmU's 'Khepera pens'
xs = 500; ys = 650;

if ~isempty(arena)
    [ys,xs]=size(arena);
    
    if (ys<100) | (xs<100)
        arena=[];
        if (xs<100) xs=100; end;
        if (ys<100) ys=100; end;
        kiks_status('Warning: arena width or height cannot be less than 100mm.');
    end;
end;

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


KIKS_BALL_TRACE_IX=[];
KIKS_tracestep=[];

if isempty(arena)
    %arena = zeros(ys, xs);
    kiks_arena_new_create(ys,xs,1,KIKS_ARENA_DEFAULT_COLOR);
    return;
end;

if isempty(colormask)
    colormask=uint8(double(arena)*255);
end;

[ys,xs]=size(arena);

if ys>1 & xs>1
    if isempty(colormask)
        colormask=uint8(double(arena)*255);
    end;
    
    kiks_status(sprintf('Setting up arena (%d x %d mm)\n',xs,ys));
    pos=[];
    rot=[];
    kheps=0;
    while min(min(arena))<0 % robot start position included
        kheps=kheps+1;
        rot(kheps)=abs(min(min(arena)))*pi/180;
        [y,x]=find(arena==min(min(arena)));
        arena(y,x)=0;
        xpos(kheps)=x;
        ypos(kheps)=y;
    end;
    [py,px]=find(arena==3);
    [ly,lx]=find(arena==2);
    [cy,cx]=find(arena==4);
    
    arena(py,px)=0;
    arena(ly,lx)=0;
    arena(cy,cx)=0;
    
    KIKS_ARENA_MASK_ORIG = arena;
    KIKS_ARENA_COLORMASK_ORIG = colormask;
    %max(max(KIKS_ARENA_COLORMASK_ORIG))
    [ys,xs]=size(arena);
    
    KIKS_ARENA_MX = zeros(ys+floor(KIKS_WALL_WIDTH)*2, xs+floor(KIKS_WALL_WIDTH)*2); 
    KIKS_ARENA_MX(1:floor(KIKS_WALL_WIDTH),:) = 1;
    KIKS_ARENA_MX(ys+floor(KIKS_WALL_WIDTH):ys+floor(KIKS_WALL_WIDTH)*2,:) = 1;
    KIKS_ARENA_MX(:,1:floor(KIKS_WALL_WIDTH)) = 1;
    KIKS_ARENA_MX(:,xs+floor(KIKS_WALL_WIDTH):xs+floor(KIKS_WALL_WIDTH)*2) = 1;   
    KIKS_ARENA_MX(floor(KIKS_WALL_WIDTH)+1:floor(KIKS_WALL_WIDTH)+ys,floor(KIKS_WALL_WIDTH)+1:floor(KIKS_WALL_WIDTH)+xs)=arena;
    
    wall_color = min(255,max(KIKS_ARENA_DEFAULT_COLOR,1));
    
    KIKS_ARENA_COLORMASK = zeros(ys+floor(KIKS_WALL_WIDTH)*2, xs+floor(KIKS_WALL_WIDTH)*2);
    KIKS_ARENA_COLORMASK(1:floor(KIKS_WALL_WIDTH),:) = wall_color;
    KIKS_ARENA_COLORMASK(ys+floor(KIKS_WALL_WIDTH):ys+floor(KIKS_WALL_WIDTH)*2,:) = wall_color;
    KIKS_ARENA_COLORMASK(:,1:floor(KIKS_WALL_WIDTH)) = wall_color;
    KIKS_ARENA_COLORMASK(:,xs+floor(KIKS_WALL_WIDTH):xs+floor(KIKS_WALL_WIDTH)*2) = wall_color;   
    KIKS_ARENA_COLORMASK(floor(KIKS_WALL_WIDTH)+1:floor(KIKS_WALL_WIDTH)+ys,floor(KIKS_WALL_WIDTH)+1:floor(KIKS_WALL_WIDTH)+xs)=colormask;
    
    [rows,cols]=size(KIKS_ARENA_MX);
    if KIKS_MMPERPIXEL>1
        kiks_status(sprintf('Downsampling arena (%dx)... \n',floor(KIKS_MMPERPIXEL)));
        KIKS_ARENA_MX=kiks_scale(KIKS_ARENA_MX,rows/KIKS_MMPERPIXEL,cols/KIKS_MMPERPIXEL);
        [rows,cols]=size(KIKS_ARENA_COLORMASK);
        KIKS_ARENA_COLORMASK=kiks_scale(KIKS_ARENA_COLORMASK,rows/KIKS_MMPERPIXEL,cols/KIKS_MMPERPIXEL);
        kiks_status(sprintf('Downsampling arena (%dx)... done.\n',floor(KIKS_MMPERPIXEL)));
    end;
    KIKS_ARENA_MASK = KIKS_ARENA_MX;
    
    if kheps>0
        for k=1:kheps
            kiks_spawn_robot([xpos(k) ypos(k)]+KIKS_WALL_WIDTH-KIKS_WALL_RENDER,rot(k));
        end;
    else
        if isempty(nokhep) kiks_spawn_robot; end;
    end;
    
    lights=size(lx);
    for l=1:lights
        kiks_spawn_object([lx(l) ly(l)],1);
    end;
    
    objs=size(px);
    for p=1:objs
        kiks_spawn_object([px(p) py(p)],2);
    end;   
    
    objs=size(cx);
    for p=1:objs
        kiks_spawn_object([cx(p) cy(p)],3);
    end;   
end;

KIKS_2DVISUALIZE=oldvis;
if (KIKS_2DVISUALIZE>0)
    kiks_arena_window_open;
end;