% function bm=kiks_generate_maze(xs,ys,path_width,wall_width)
%
% Simple random maze generator.
% xs,ys defines the size of the matrix.
% path_width is how wide the path should be, and
% wall_width is how wide the walls should be.
% If omitted, default values are used.
%
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function bm=kiks_generate_maze(xs,ys,path_width,wall_width)

TLIMIT=8;

if nargin<4
    wall_width=10;
end;
if nargin<3
    path_width=120;
end;
if nargin<2
    ys=4;
end;
if nargin<1
    xs=4;
end;

% creates a maze of size xs,ys
% 1=wall, 0=no wall
ys=ys+2; % 2 rows will be left unused
xs=xs+2; % 2 columns are not really used
kiks_status('generating maze');
ops=TLIMIT;
while ops>=TLIMIT
    maze=zeros((ys*2)-1,(xs*2)-1);
    y=ceil((ys/4)+rand*(ys-ys/2));
    x=2;
    ops=0;
    xstart=[];
    ystart=[];
    while(x<xs & ops<TLIMIT)
        maze((y*2)-1,(x*2)-1)=1;
        if isempty(xstart)
            %         xstart=x;
            %         ystart=y;
            xstart=1; % start at top left
            ystart=2;
            dir=2;
        else
            dir=ceil(rand*4);
        end;
        
        oldx=x;
        oldy=y;
        switch dir
            case 1 % move up or right
                if(y>2)
                    dx=(x*2)-1;
                    y=y-1;
                    dy=(y*2);
                end;
            case 2 % move right
                dx=(x*2);
                dy=(y*2)-1;
                x=x+1;
            case 3 % move down or right
                if(y<ys-1)
                    dx=(x*2)-1;
                    y=y+1;
                    dy=(y*2)-2;
                end;
            case 4 % move left
                if(x>2)
                    x=x-1;
                    dy=(y*2)-1;
                    dx=(x*2);
                end;
        end;
        
        if maze((y*2)-1,(x*2)-1)==1 % already been here!
            ops=ops+1;
            x=oldx;
            y=oldy;
        else
            ops=0;
            if (x<xs) maze(dy,dx)=1; end;
        end;
    end;
    x=xs;  
    y=ys-1; % stop at bottom right
    
    maze((y*2)-1,(x*2)-1)=1;
    xstop=x;
    ystop=y;
    maze((ystart*2)-1,(xstart*2)-1)=1;
end;

for x=2:xs-1
    for y=2:ys-1
        maze((y*2)-1,(x*2)-1)=-1;
        if (maze((y*2)-2,(x*2)-1)==0) & (maze((y*2),(x*2)-1)==0) & (maze((y*2)-1,(x*2)-2)==0) & (maze((y*2)-1,(x*2))==0) 
            % all walls closed!
            tx=x;
            ty=y;
            while (maze((ty*2)-2,(tx*2)-1)~=1) & (maze((ty*2),(tx*2)-1)~=1) & (maze((ty*2)-1,(tx*2)-2)~=1) & (maze((ty*2)-1,(tx*2))~=1)
                dist=ceil(rand*4);
                oldx=tx;
                oldy=ty;
                switch dist
                    case 1 % try right
                        if tx<xs-1
                            tx=tx+1;
                            dy=(ty*2)-1;
                            dx=(tx*2)-2;
                        end;
                    case 2 % try left
                        if tx>2
                            tx=tx-1;
                            dy=(ty*2)-1;
                            dx=(tx*2);
                        end;
                    case 3 % try down
                        if ty<ys-1
                            ty=ty+1;
                            dy=(ty*2)-2;
                            dx=(tx*2)-1;
                        end;
                    case 4 % try up
                        if ty>2
                            ty=ty-1;
                            dy=(ty*2);
                            dx=(tx*2)-1;
                        end;
                end;
                if maze((ty*2)-1,(tx*2)-1)~=-1
                    maze((ty*2)-1,(tx*2)-1)=-1;
                    maze(dy,dx)=-1;
                end;           
            end;
        end;
        maze=abs(maze);
    end;
end;
maze((ystop*2)-1,(xstop*2)-2)=1;
maze((ystart*2)-1,(xstart*2))=1;

%maze

bm=ones(ys*path_width+(ys-1)*wall_width,xs*path_width+(xs-1)*wall_width);

for x=1:xs
    for y=1:ys
        if maze((y*2)-1,(x*2)-1)==1
            bm(1+(y-1)*(path_width+wall_width):(y-1)*(path_width+wall_width)+path_width,1+(x-1)*(path_width+wall_width):(x-1)*(path_width+wall_width)+path_width)=0;
        end;
        if (x>1) & maze((y*2)-1,(x*2)-2)==1 % left wall
            bm(1+(y-1)*(path_width+wall_width):(y-1)*(path_width+wall_width)+path_width,1+(x-1)*(path_width+wall_width)-wall_width:(x-1)*(path_width+wall_width))=0;
        end;
        if (y>1) & maze((y*2)-2,(x*2)-1)==1 % top wall
            bm(1+(y-1)*(path_width+wall_width)-wall_width:(y-1)*(path_width+wall_width),1+(x-1)*(path_width+wall_width):(x-1)*(path_width+wall_width)+path_width)=0;
        end;         
    end;
end;
bm(round(path_width/2)+(ystart-1)*(path_width+wall_width),round(wall_width/2+path_width/2)+(xstart-1)*(path_width+wall_width))=-360;
bm(round(path_width/2)+(ystop-1)*(path_width+wall_width),round(path_width/2)+(xstop-1)*(path_width+wall_width))=2;
[ys,xs]=size(bm);
bm=bm(path_width+wall_width+1:ys-path_width-wall_width,wall_width+1:xs-wall_width);
[ys,xs]=size(bm);
bm(1:10,:)=1;
bm(:,1:10)=1;
bm(ys-10:ys,:)=1;
bm(:,xs-10:xs)=1;

%bm(1:path_width+wall_width:end,path_width+1:end-path_width)=0;
%bm(1+path_width:path_width+wall_width:end,path_width+1:end-path_width)=0;
%bm(:,path_width:path_width+wall_width:end-path_width)=0;
%bm(:,2*path_width:path_width+wall_width:end-path_width)=0;
%bm(:,1+path_width:path_width+wall_width:end)=0;

kiks_status('maze generation successful.');