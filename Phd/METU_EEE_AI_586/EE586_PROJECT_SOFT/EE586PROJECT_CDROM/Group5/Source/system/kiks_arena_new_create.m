function kiks_arena_new_create(hg,wd,r,c);

if nargin<4
    h=findobj(gcf,'tag','width');
    wd=str2num(get(h,'String'));
    h=findobj(gcf,'tag','height');
    hg=str2num(get(h,'String'));
    h=findobj(gcf,'tag','rounded');
    r=get(h,'Value');
    h=findobj(gcf,'tag','color');
    c=min(255,ceil(get(h,'Value')));
    close(gcf);
end;

if ~isempty(wd) & ~isempty(hg)
    hg=hg-20;
    wd=wd-20;
    arena=ones(hg+20,wd+20);
    arena(10:hg+10,10:wd+10)=0;
    if (r==1)
        max_radius=min(100,min(hg,wd)/2);
        MX=floor(max_radius)*2+1;
        MY=floor(max_radius)*2+1;
        ROUND_MASK=zeros(MX,MY);
        for x=1:MX,
            for y=1:MY,
                if sqrt((x-(MX+1)/2)*(x-(MX+1)/2)+(y-(MY+1)/2)*(y-(MY+1)/2))<=max_radius ROUND_MASK(x,y)=1; end;
            end;   
        end;
        
        [xs,ys]=size(ROUND_MASK);
        x=floor((xs-1)/2);
        y=floor((ys-1)/2);
        arena(1+10:x-1+10,1+10:y-1+10)=abs(ROUND_MASK(2:x,2:y)-1);
        arena(hg-x+10:hg+10,1+10:y-1+10)=abs(ROUND_MASK(x+1:xs,2:y)-1);
        arena(hg-x+10:hg+10,wd-y+10:wd+10)=abs(ROUND_MASK(x+1:xs,y+1:ys)-1);
        arena(1+10:x-1+10,wd-y+10:wd+10)=abs(ROUND_MASK(2:x,y+1:ys)-1);
    end;
    colormask=arena*c;
    kiks_arena(arena,colormask);
end;