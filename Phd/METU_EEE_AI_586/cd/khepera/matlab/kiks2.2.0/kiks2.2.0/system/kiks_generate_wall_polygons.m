% -----------------------------------------------------
%  (c) 2000-2003 Theodor Storm (Theodor.Storm@home.se)
%  http://www.kiks.net
% -----------------------------------------------------

function o=kiks_generate_wall_polygons(arena)

[ys,xs]=size(arena);
res=[];
o=[xs ys];

bits=length(find(arena));
sum=0;

while max(max(arena))>0
    [ix_y,ix_x] = find(arena);
    tl_x = ix_x(1);
    tl_y = ix_y(1);
    col=arena(tl_y,tl_x);
    
    restofcol = arena(tl_y:ys,tl_x);
    indexes = find(restofcol~=col);
    if isempty(indexes)
        bl_y = ys;
    else
        bl_y = tl_y+indexes(1)-2;
    end;
    tr_y = tl_y;
    
    bl_x = tl_x;
    br_y = bl_y;
    
    searchspace=arena(tl_y:bl_y,tl_x:xs);    
    [ix_y,ix_x] = find(searchspace~=col);
    if isempty(ix_x)
        br_x = xs;
    else
        br_x=bl_x+ix_x(1)-2;
    end;
    tr_x = br_x; 
    
    arena(tl_y:br_y,tl_x:br_x)=0;
    res = [res; tl_x tr_x br_x bl_x tl_y tr_y br_y bl_y col];
    sum=sum+(bl_y-tl_y+1)*(tr_x-tl_x+1);
    kiks_progress(sum/bits,'generating polygons ');
end;

[polys,tmp]=size(res);
kiks_status(sprintf('%d polygons generated.',polys));
for i=1:polys
    kiks_progress(i/polys,'optimizing polygons ');
    p=double(res(i,:));
    o=[o 4 p(1) p(2) p(3) p(4) p(5) p(6) p(7) p(8) p(9)];
end;
o=uint16(o);