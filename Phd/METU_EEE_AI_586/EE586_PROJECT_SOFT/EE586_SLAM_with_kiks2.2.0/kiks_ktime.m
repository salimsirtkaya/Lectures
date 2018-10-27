% kiks_ktime(ref)
%
% returns elapsed time in seconds since kiks_kopen was called for referenced robot
%
% -----------------------------------------------
%  (c) 2000 Theodor Storm (theodor@tstorm.se)
%  http://www.tstorm.se
% -----------------------------------------------
%function secs=kiks_ktime(port)
function secs=kiks_ktime(port)
global KIKS_KTIME_VEC KIKS_RBT_TIME KIKS_OTHERTIME KIKS_PAUSETIME KIKS_LINKTIME;
secs=[];
if (port<0)
    [tmp,sz]=size(KIKS_RBT_TIME);
    if abs(port)<=sz & KIKS_RBT_TIME(abs(port))>=0
        if etime(clock,KIKS_OTHERTIME)>0
            kiks_ksend([],[port port port port]);
        end;      
        secs=KIKS_RBT_TIME(abs(port));
    end;
else
    [sz,tmp]=size(KIKS_KTIME_VEC);
    if port+1<=sz & ~isempty(KIKS_KTIME_VEC(port+1,:))
        secs=etime(clock,KIKS_KTIME_VEC(port+1,:));
    end;
end;

return;