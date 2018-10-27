% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function coordinates = kiks_blob2polygon(m,c,num)

[ro,co]=find(m==num);
all_cont = c(min(ro):max(ro),min(co):max(co));
matr = m(min(ro):max(ro),min(co):max(co));
[rws,cls]=size(matr);
cont = (matr==num & all_cont == 1);
coordinates=[];
if size(cont)>1
    clear matr all_cont;
    [cont_rows,cont_cols]=find(cont==1);
    cont_coords=[cont_rows,cont_cols];
    [rows,cols]=size(cont_coords);
    oldpc=0;
    cont_coords=sortrows(cont_coords);
    % sort cont_coords so distance between the points is minimized
    kiks_status(sprintf('Generating coordinates from %d*%d blob (%d points)...\n<KiKS> ',rws,cls,rows));
    for i=1:rows-1
        pc = round((i/rows)*10);
        if (pc>oldpc)
            kiks_status(sprintf('%d%%',pc*10));
            oldpc=pc;
        end;
        coords = cont_coords(i,:);
        mindist=Inf;
        ix=0;
        substcoords=ones(rows-i,2);
        substcoords(:,1)=coords(1);
        substcoords(:,2)=coords(2);
        distcoords=(abs(cont_coords(i+1:end,:)-substcoords))';
        sdist=sum(distcoords);
        minpos=find(sdist==min(sdist));
        ix=minpos(1)+i;
        
        temp_pos=cont_coords(ix,:);
        cont_coords(ix,:)=cont_coords(i+1,:);
        cont_coords(i+1,:)=temp_pos;
    end;
    
    [rows,cols]=size(cont_coords);
    addmx=ones(rows,cols);
    addmx(:,1)=addmx(:,1)+min(ro);
    addmx(:,2)=addmx(:,2)+min(co);
    coordinates=cont_coords+addmx;
    %coordinates=cont_coords(1,:);
    %for i=2:rows-1
    %    last=cont_coords(i-1,:);
    %    next=cont_coords(i+1,:);
    %    lastdiff=last-cont_coords(i,:);
    %    nextdiff=cont_coords(i,:)-next;
    %    if (lastdiff ~= nextdiff)
    %        coordinates = [coordinates; cont_coords(i,:)];    
    %    end;
    %end;
    %coordinates=[coordinates; cont_coords(end,:)];
    kiks_status('done.\n');
end;