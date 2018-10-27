% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_update_remote
global KIKS_REMOTEKHEP_MTRX KIKS_COLOR_ROBOT KIKS_REMOTEKHEP_HDL KIKS_2DVISUALIZE KIKS_MMPERPIXEL KIKS_REMOTE_ARRAY KIKS_REMOTE_ARRAY_NEW;
entries=8; % entries per object

KIKS_REMOTEKHEP_MTRX=[];
if ~isempty(KIKS_REMOTE_ARRAY)
    nr = size(KIKS_REMOTE_ARRAY,1)/entries;
    for i=0:nr-1
        id=KIKS_REMOTE_ARRAY(1+i*entries);
        type=KIKS_REMOTE_ARRAY(2+i*entries);
        x=KIKS_REMOTE_ARRAY(3+i*entries);
        y=KIKS_REMOTE_ARRAY(4+i*entries);
        ang=KIKS_REMOTE_ARRAY(5+i*entries);
        r=floor(KIKS_REMOTE_ARRAY(6+i*entries)); % radius
        KIKS_REMOTEKHEP_MTRX(id,1)=x;
        KIKS_REMOTEKHEP_MTRX(id,2)=y;
        KIKS_REMOTEKHEP_MTRX(id,3)=1; % mark this as an "old" remote Khepera
        KIKS_REMOTEKHEP_MTRX(id,4)=r;
        KIKS_REMOTEKHEP_MTRX(id,5)=ang;
    end;
end;

[rows,cols]=size(KIKS_REMOTEKHEP_MTRX);
createhdl=[];
if isempty(KIKS_REMOTEKHEP_HDL) createhdl=1; end;

if ~isempty(KIKS_REMOTE_ARRAY_NEW)
    %   KIKS_REMOTE_ARRAY_NEW
    nr = size(KIKS_REMOTE_ARRAY_NEW,1)/entries;
    for i=0:nr-1
        id=KIKS_REMOTE_ARRAY_NEW(1+i*entries);
        type=KIKS_REMOTE_ARRAY_NEW(2+i*entries);
        x=KIKS_REMOTE_ARRAY_NEW(3+i*entries);
        y=KIKS_REMOTE_ARRAY_NEW(4+i*entries);
        ang=KIKS_REMOTE_ARRAY_NEW(5+i*entries);
        r=KIKS_REMOTE_ARRAY_NEW(6+i*entries);
        if id<=rows
            isnew = (KIKS_REMOTEKHEP_MTRX(id,3)==0);
        else
            isnew=1;
        end;
        
        if (isnew)
            %kiks_arena_addremoterobot(x,y);
            kiks_arena_add_mask(floor(x),floor(y),KIKS_COLOR_ROBOT,r);
            if (KIKS_2DVISUALIZE>0) kiks_draw_remoterobot(id,x,y,ang,1,r); end;     
        else
            if (KIKS_REMOTEKHEP_MTRX(id,1)~=x | KIKS_REMOTEKHEP_MTRX(id,2)~=y | KIKS_REMOTEKHEP_MTRX(id,5)~=ang)
                %kiks_arena_subremoterobot(KIKS_REMOTEKHEP_MTRX(id,1),KIKS_REMOTEKHEP_MTRX(id,2));
                kiks_arena_sub_mask(floor(KIKS_REMOTEKHEP_MTRX(id,1)),floor(KIKS_REMOTEKHEP_MTRX(id,2)),KIKS_COLOR_ROBOT,r);
                %kiks_arena_addremoterobot(x,y);
                kiks_arena_add_mask(floor(x),floor(y),KIKS_COLOR_ROBOT,r);
                if (KIKS_2DVISUALIZE>0) kiks_draw_remoterobot(id,x,y,ang,createhdl,r); end;     
            end;
        end;
        KIKS_REMOTEKHEP_MTRX(id,:)=[0 0 0 0 0]; % this id is in new array too
    end;
end;

if ~isempty(KIKS_REMOTEKHEP_MTRX)
    ix=find(KIKS_REMOTEKHEP_MTRX(:,3)); % ix contains all id's that should be removed from world
    [sz,tmp]=size(ix);
    for i=1:sz
        id=ix(i);
        %kiks_arena_subremoterobot(KIKS_REMOTEKHEP_MTRX(id,1),KIKS_REMOTEKHEP_MTRX(id,2));
        kiks_arena_sub_mask(floor(KIKS_REMOTEKHEP_MTRX(id,1)),floor(KIKS_REMOTEKHEP_MTRX(id,2)),KIKS_COLOR_ROBOT,KIKS_REMOTEKHEP_MTRX(id,4));
        a=findobj('Tag',sprintf('remoteKhep %d',id));
        delete(a);
    end;
end;

KIKS_REMOTE_ARRAY=KIKS_REMOTE_ARRAY_NEW;