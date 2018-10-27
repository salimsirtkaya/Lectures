% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% Simulation of the K-team radio turret
function response = kiks_turret_radio(tcommand,targs);
global KIKS_FID KIKS_KIKSNET_REPLY;

if nargin<2
    % return the turret id
    response=4;
    return;
end;

switch tcommand
    case 'B' % read version
        response=['b,1,0'];
    case 'F' % read status
        status = 0;
        if ~isempty(KIKS_KIKSNET_REPLY)
            status=sscanf(KIKS_KIKSNET_REPLY,'%d');
        else
            if KIKS_FID~=-1
                disp('<KiKS warning> KiKSnet server did not reply to RADIO_STATUS command!');
            end;
        end;    
        response=[sprintf('t,4,f,%d',status)];        
    case 'R' % read reception buffer
        message = '0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0';
        if ~isempty(KIKS_KIKSNET_REPLY)
            message=KIKS_KIKSNET_REPLY;
        else
            if KIKS_FID~=-1
                disp('<KiKS warning> KiKSnet server did not reply to RADIO_READ command!');
            end;
        end;            
        response=[sprintf('t,4,r,%s',message)];        
    case 'S' % send buffer - already handled by kiks_ksend.m
        response=['t,4,s'];
        if isempty(KIKS_KIKSNET_REPLY) & KIKS_FID~=-1
            disp('<KiKS warning> KiKSnet server did not reply to RADIO_SEND command!');
            response=['z,Protocol error'];
        end;            
    otherwise
        response=['z,Protocol error'];
end;
