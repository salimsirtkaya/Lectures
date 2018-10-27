function kiks_progress(prc,str,len)
persistent last;
if isempty(last)
    last=Inf;
end;

if nargin<3, len=30; end;
if nargin<2, str=''; end;
if nargin<1, return; end;

stars=round((prc*100)/(100/len));

progress=ones(1,len)*' ';
progress(1:stars)='-';

if (stars~=last | prc==1)
    replace=1;
    if last>stars
        replace=[];
    end;
    kiks_status(sprintf(['%s[' progress '] %.1f%%\n'],str,prc*100),[],replace);
    last=stars;
    pause(0.001);
end;
