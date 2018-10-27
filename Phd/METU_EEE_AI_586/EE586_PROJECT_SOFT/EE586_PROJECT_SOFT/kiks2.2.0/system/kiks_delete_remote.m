% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function res = kiks_delete_remote
global KIKS_2DVISUALIZE KIKS_REMOTE_ARRAY KIKS_COLOR_ROBOT;
entries=8; % entries per object

if ~isempty(KIKS_REMOTE_ARRAY)
    nr = size(KIKS_REMOTE_ARRAY,1)/entries;
    for i=0:nr-1
        id=KIKS_REMOTE_ARRAY(1+i*entries);
        type=KIKS_REMOTE_ARRAY(2+i*entries);
        x=KIKS_REMOTE_ARRAY(3+i*entries);
        y=KIKS_REMOTE_ARRAY(4+i*entries);
        r=floor(KIKS_REMOTE_ARRAY(6+i*entries));
        
        kiks_arena_sub_mask(floor(x),floor(y),KIKS_COLOR_ROBOT,r);
        a=findobj('Tag',sprintf('remoteKhep %d',id));
        delete(a);                
    end;
end;


