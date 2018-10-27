% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_status(buffer,dual,replace)
global KIKS_LOG_HISTORY KIKS_HISTORY_HDL KIKS_GUI_HDL KIKS_STATUS_BUFFER KIKS_STATUS_BUFFER_CNT;
if nargin<2
    dual=[];
end;
if nargin<3
    replace=[];
end;

buffer=strrep(buffer,sprintf('\n\n'),sprintf('\n'));
if length(buffer)<1
    return;
end;
if buffer(1)==10
    buffer=buffer(2:end);
end;
if buffer(end)~=10
    buffer=[buffer sprintf('\n')];
end;
nostrs=findstr(buffer,sprintf('\n'));
if length(nostrs)>=KIKS_LOG_HISTORY
    kiks_status('<buffer too large for log window>');
    return;
end;

if isempty(KIKS_STATUS_BUFFER)
    kiks_preferences;
    KIKS_STATUS_BUFFER = cell(KIKS_LOG_HISTORY,1);
    KIKS_STATUS_BUFFER_CNT=0;
end;

if isempty(replace)
    KIKS_STATUS_BUFFER(1:KIKS_LOG_HISTORY-length(nostrs))=KIKS_STATUS_BUFFER(1+length(nostrs):KIKS_LOG_HISTORY);
end;

while ~isempty(nostrs)
    str = buffer(1:nostrs(1)-1);
    str = ['[' datestr(now,13) '] ' str];
    buffer=buffer(nostrs(1)+1:end);
    nostrs=findstr(buffer,sprintf('\n'));
    KIKS_STATUS_BUFFER(KIKS_LOG_HISTORY-length(nostrs))={str};
    if isempty(replace)
        KIKS_STATUS_BUFFER_CNT=min(KIKS_LOG_HISTORY,KIKS_STATUS_BUFFER_CNT+1);
    end;
    if isempty(KIKS_GUI_HDL) | ~isempty(dual)
        disp(['<KiKS> ' str]);
    end;
end;
if ~isempty(KIKS_GUI_HDL)
    s=findobj(KIKS_GUI_HDL,'tag','status');
    set(s,'String',KIKS_STATUS_BUFFER(KIKS_LOG_HISTORY));
    if (KIKS_HISTORY_HDL)
        s=findobj(KIKS_HISTORY_HDL,'tag','loghistory');
        set(s,'String',KIKS_STATUS_BUFFER(KIKS_LOG_HISTORY+1-KIKS_STATUS_BUFFER_CNT:end));
        set(s,'Value',KIKS_STATUS_BUFFER_CNT);
        drawnow;
    end;
end;