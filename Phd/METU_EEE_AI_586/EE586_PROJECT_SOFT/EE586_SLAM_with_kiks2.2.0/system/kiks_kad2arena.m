function [arena,colormask]=kiks_kad2arena(a)

a=double(a);
arena=[];
colormask=[];

xs=double(a(1));
ys=double(a(2));
colormask=zeros(ys,xs);
i=3;
while i<length(a)
    no_vert = a(i);
    i=i+1;
    x=a(i:i+no_vert-1);
    i=i+no_vert;
    y=a(i:i+no_vert-1);
    i=i+no_vert;
    col=a(i);
    i=i+1;
    mask = zeros(max(y)-min(y)+1,max(x)-min(x)+1);
    [yix,xix]=find(mask==0);
    in=inpolygon(xix,yix,x-min(x)+1,y-min(y)+1);
    mask(yix(find(in>0)),xix(find(in>0)))=1;
    colormask(min(y):max(y),min(x):max(x))=mask*col;
%    colormask(min(y):max(y),min(x):max(x))=mask*round(rand*100); % visible polygons
    kiks_progress(i/length(a),'rendering arena ');
end;
arena=(colormask>0);
