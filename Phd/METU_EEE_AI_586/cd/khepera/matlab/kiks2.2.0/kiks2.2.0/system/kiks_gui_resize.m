% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_resize(xs)
global KIKS_KIKSNET_MONITORING KIKS_ARENA_OLDXS KIKS_ARENA_IMG_XS KIKS_ARENA_IMG_YS KIKS_ARENA_HDL KIKS_GUI_HDL KIKS_2DVISUALIZE KIKS_MMPERPIXEL;

mainpos=get(KIKS_GUI_HDL,'Position');
pos=[148 49];

h=findobj(KIKS_GUI_HDL,'tag','kiks_matlab_command');
sp=get(h,'Position');
sp(3)=mainpos(3)-76;
set(h,'Position',sp);

if KIKS_2DVISUALIZE==0
    mainpos(3)=147;
    set(KIKS_GUI_HDL,'Position',mainpos);
    return;
end;
if mainpos(3)<247
    mainpos(3)=247;
end;
pys=KIKS_ARENA_IMG_YS;
pxs=KIKS_ARENA_IMG_XS;
if nargin==1
    if isempty(KIKS_ARENA_OLDXS)
        mainpos(3)=xs;
    else
        mainpos(3)=KIKS_ARENA_OLDXS;
    end;
end;
%mainpos(3)=pos(1)+KIKS_ARENA_IMG_XS*KIKS_MMPERPIXEL;
scrn=get(findobj('type','root'),'screensize');
mainpos(3)=min(mainpos(3),scrn(3)-mainpos(1));
KIKS_ARENA_OLDXS=mainpos(3);
set(KIKS_GUI_HDL,'Position',mainpos);

xpixels=mainpos(3)-pos(1);
ypixels=mainpos(4)-pos(2);
%[pys pxs]=[KIKS_ARENA_IMG_YS KIKS_ARENA_IMG_XS];
winratio=xpixels/ypixels;
imgratio=pxs/pys;
if imgratio>=winratio
    pos=[pos(1) pos(2)+(ypixels-(xpixels/pxs)*pys)/2 xpixels (xpixels/pxs)*pys];
else
    pos=[pos(1)+(xpixels-(ypixels/pys)*pxs)/2 pos(2) (ypixels/pys)*pxs ypixels];
end;
pos(find(pos<1))=1;
set(KIKS_ARENA_HDL,'position',pos);
h=findobj(KIKS_GUI_HDL,'tag','status');
sp=get(h,'Position');
sp(1)=148;
sp(3)=mainpos(3)-145;
sp(find(sp<1))=1;
set(h,'Position',sp);
h=findobj(KIKS_GUI_HDL,'tag','status_dummy');
sp=get(h,'Position');
sp(3)=mainpos(3)+2;
set(h,'Position',sp);
